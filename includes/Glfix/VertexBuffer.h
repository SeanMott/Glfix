//defines a Vertex Buffer

#ifndef VertexBuffer_h
#define VertexBuffer_h

#ifdef __cplusplus

extern "C" {
#endif

#include <Glfix\DrawTypePrimitives.h>
#include <Glfix\VertexLayout.h>
#include <stdint.h>

	//defines a Vertex Buffer
	typedef struct
	{
		//ids
		uint32_t vertexBuffer, vertexArray;

		//vertex data
		float* vertices;
		uint32_t size;

		//layout
		//Glfix_VertexLayout_Layout* layout;

	} Glfix_VertexBuffer;

	//creates a static buffer
	Glfix_VertexBuffer* Glfix_VertexBuffer_CreateStatic(float* vertices, uint32_t size);
	//creates a dynamic buffer
	Glfix_VertexBuffer* Glfix_VertexBuffer_CreateDynamic(uint32_t size);
	//destroys a buffer
	void Glfix_VertexBuffer_Destroy(Glfix_VertexBuffer* buffer);

	//sets the layout || assumes it's already been bound
	void Glfix_VertexBuffer_Layout(Glfix_VertexBuffer* buffer, Glfix_VertexLayout_Layout* layout);

	//binds a buffer
	void Glfix_VertexBuffer_Bind(Glfix_VertexBuffer* buffer);
	//unbinds a buffer
	void Glfix_VertexBuffer_Unbind();

	//sends data to the GPU via the buffer || assumes it's bound already
	void Glfix_VertexBuffer_SendData(const void* data, uint32_t dataSize);

	//draws a buffer || assumes it's already been bound
	void Glfix_VertexBuffer_Draw(Glfix_DrawType primitiveType, uint32_t startIndex, uint32_t vertexSize);

#ifdef __cplusplus

}
#endif

#endif