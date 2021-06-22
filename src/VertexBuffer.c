#include <gpch.h>
#include <Glfix\VertexBuffer.h>

#include <glad\glad.h>

Glfix_VertexBuffer* Glfix_VertexBuffer_CreateStatic(float* vertices, uint32_t size)
{
	if (!vertices)
	{
		LogError("Vertex Buffer vertices NULL", "The vertices give to a static Vertex Buffer were NULL, can not make buffer.");
		return NULL;
	}

	//gens vertex and array buffer
	Glfix_VertexBuffer* buffer = malloc(sizeof(Glfix_VertexBuffer));
	glGenVertexArrays(1, &buffer->vertexArray);
	glGenBuffers(1, &buffer->vertexBuffer);
	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);

	//sets static data
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	buffer->size = size;
	buffer->vertices = vertices;

	return buffer;
}

Glfix_VertexBuffer* Glfix_VertexBuffer_CreateDynamic(uint32_t size)
{
	//gens vertex and array buffer
	Glfix_VertexBuffer* buffer = malloc(sizeof(Glfix_VertexBuffer));
	glGenVertexArrays(1, &buffer->vertexArray);
	glGenBuffers(1, &buffer->vertexBuffer);
	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);

	//sets static data
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	buffer->size = size;
	buffer->vertices = NULL;

	return buffer;
}

void Glfix_VertexBuffer_Destroy(Glfix_VertexBuffer* buffer)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer", "Buffer is NULL can not destroy!");
		return;
	}

	glDeleteBuffers(1, &buffer->vertexArray);
	glDeleteVertexArrays(1, &buffer->vertexBuffer);
	buffer->vertices = NULL;
	free(buffer);
	buffer = NULL;
}

void Glfix_VertexBuffer_Layout(Glfix_VertexBuffer* buffer, Glfix_VertexLayout_Layout* layout)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer (Opengl)", "Buffer is NULL can not add layout!");
		return;
	}

	if (!layout)
	{
		LogError("NULL Buffer Layout (Opengl)", "Layout is NULL can not add layout!");
		return;
	}

	if (!layout->normalize || !layout->elements)
	{
		LogError("Buffer Layout (Opengl)", "Layout elements or normalize is NULL, can not add layout!");
		return;
	}

	uint32_t offset = 0, totalCompCount = 0;
	uint32_t currentCompCount = 0, currentCompDatatype = 0;

	//gets total component count
	for (uint32_t i = 0; i < layout->elementCount; i++)
		totalCompCount += Glfix_VertexLayout_GetComponentCount(layout->elements[i]);

	//sets attrib pointer
	for (uint32_t pointer = 0; pointer < layout->elementCount; pointer++)
	{
		currentCompCount = Glfix_VertexLayout_GetComponentCount(layout->elements[pointer]);
		currentCompDatatype = Glfix_VertexLayout_GetNativeAPIType(layout->elements[pointer]);

		glVertexAttribPointer(pointer, currentCompCount, currentCompDatatype,
			layout->normalize[pointer], totalCompCount * sizeof(float), (void*)offset);
		glEnableVertexAttribArray(pointer);

		offset += (currentCompCount * sizeof(currentCompDatatype));
	}
}

void Glfix_VertexBuffer_Bind(Glfix_VertexBuffer* buffer)
{
	if (!buffer)
	{
		LogError("NULL Vertex Buffer", "Buffer is NULL can not bind!");
		return;
	}

	glBindVertexArray(buffer->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->vertexBuffer);
}

void Glfix_VertexBuffer_Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Glfix_VertexBuffer_SendData(const void* data, uint32_t dataSize)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, data);
}

void Glfix_VertexBuffer_Draw(Glfix_DrawType primitiveType, uint32_t startIndex, uint32_t vertexSize)
{
	if (primitiveType == Glfix_DrawType_Triangles)
		glDrawArrays(GL_TRIANGLES, startIndex, vertexSize);
	else if (primitiveType == Glfix_DrawType_Points)
		glDrawArrays(GL_POINTS, startIndex, vertexSize);
}

void Glfix_VertexBuffer_InstanceDraw(Glfix_DrawType primitiveType, uint32_t startIndex, uint32_t vertexSize, uint32_t instCount)
{
	if (primitiveType == Glfix_DrawType_Triangles)
		glDrawArraysInstanced(GL_TRIANGLES, startIndex, vertexSize, instCount);
	else if (primitiveType == Glfix_DrawType_Points)
		glDrawArraysInstanced(GL_POINTS, startIndex, vertexSize, instCount);
}
