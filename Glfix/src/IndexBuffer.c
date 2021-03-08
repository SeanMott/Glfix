#include <gpch.h>
#include <Glfix\IndexBuffer.h>

#include <glad\glad.h>

//creates a static buffer
Glfix_IndexBuffer_Buffer* Glfix_IndexBuffer_CreateStatic(uint32_t* indices, uint32_t count)
{
	if (!indices)
	{
		LogError("Index Buffer indices NULL", "The indices given to a static Index Buffer were NULL, can not make buffer.");
		return NULL;
	}

	Glfix_IndexBuffer_Buffer* buffer = malloc(sizeof(Glfix_IndexBuffer_Buffer));
	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	buffer->count = count;
	buffer->indices = indices;
	return buffer;
}

//creates a dynamic buffer
Glfix_IndexBuffer_Buffer* Glfix_IndexBuffer_CreateDynamic(uint32_t count)
{
	Glfix_IndexBuffer_Buffer* buffer = malloc(sizeof(Glfix_IndexBuffer_Buffer));
	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), NULL, GL_DYNAMIC_DRAW);
	buffer->count = count;
	buffer->indices = NULL;
	return buffer;
}

//destroys a buffer
void Glfix_IndexBuffer_Destroy(Glfix_IndexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogWarning("Index Buffer NULL", "The Index Buffer was NULL, can not destroy buffer.");
	}

	glDeleteBuffers(1, &buffer->id);
	buffer->indices = NULL;
	free(buffer);
	buffer = NULL;
}

//binds a buffer
void Glfix_IndexBuffer_Bind(Glfix_IndexBuffer_Buffer* buffer)
{
	if (!buffer)
	{
		LogWarning("Index Buffer NULL", "The Index Buffer was NULL, can not bind buffer.");
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
}

//unbinds a buffer
void Glfix_IndexBuffer_Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//draws a buffer || assumes it's already been bound
void Glfix_IndexBuffer_Draw(Glfix_DrawType_Type primitiveType, uint32_t startIndex, uint32_t indexCount)
{
	//triangles
	if (primitiveType == Glfix_PrimitiveType_Triangles)
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, startIndex);
	//points
	else if (primitiveType == Glfix_PrimitiveType_Points)
		glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, startIndex);
}