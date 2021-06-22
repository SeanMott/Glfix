//defines a Index Buffer

#ifndef IndexBuffer_h
#define IndexBuffer_h

#include <stdint.h>
#include <Glfix\DrawTypePrimitives.h>

#ifdef __cplusplus
extern "C" {
#endif

	//defines the Index Buffer
	typedef struct
	{
		uint32_t id;
		uint32_t* indices;
		uint32_t count;

	}Glfix_IndexBuffer;

	//creates a static buffer || multiplies the size * sizeof(uint32_t);
	Glfix_IndexBuffer* Glfix_IndexBuffer_CreateStatic(uint32_t* indices, uint32_t count);
	//creates a dynamic buffer || multiplies the size * sizeof(uint32_t);
	Glfix_IndexBuffer* Glfix_IndexBuffer_CreateDynamic(uint32_t count);
	//destroys a buffer
	void Glfix_IndexBuffer_Destroy(Glfix_IndexBuffer* buffer);

	//binds a buffer
	void Glfix_IndexBuffer_Bind(Glfix_IndexBuffer* buffer);
	//unbinds a buffer
	void Glfix_IndexBuffer_Unbind();

	//draws a buffer || assumes it's already been bound
	void Glfix_IndexBuffer_Draw(Glfix_DrawType primitiveType, uint32_t startIndex, uint32_t indexCount);
	//instance draws a buffer || assumes it's already been bound
	void Glfix_IndexBuffer_InstanceDraw(Glfix_DrawType primitiveType, uint32_t startIndex, uint32_t indexCount, uint32_t instCount);

#ifdef __cplusplus

}
#endif

#endif