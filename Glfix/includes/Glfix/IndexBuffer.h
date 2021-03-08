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

	}Glfix_IndexBuffer_Buffer;

	//creates a static buffer
	Glfix_IndexBuffer_Buffer* Glfix_IndexBuffer_CreateStatic(uint32_t* indices, uint32_t count);
	//creates a dynamic buffer
	Glfix_IndexBuffer_Buffer* Glfix_IndexBuffer_CreateDynamic(uint32_t count);
	//destroys a buffer
	void Glfix_IndexBuffer_Destroy(Glfix_IndexBuffer_Buffer* buffer);

	//binds a buffer
	void Glfix_IndexBuffer_Bind(Glfix_IndexBuffer_Buffer* buffer);
	//unbinds a buffer
	void Glfix_IndexBuffer_Unbind();

	//draws a buffer || assumes it's already been bound
	void Glfix_IndexBuffer_Draw(Glfix_DrawType_Type primitiveType, uint32_t startIndex, uint32_t indexCount);

#ifdef __cplusplus

}
#endif

#endif