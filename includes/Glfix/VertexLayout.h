//allows a vertex buffer layout to be defined

#ifndef BufferLayout_h
#define BufferLayout_h

#ifdef __cplusplus

extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <Logger.h>

	//defines a Layout Element
	typedef enum
	{
		Glfix_LayoutType_None,

		Glfix_LayoutType_Bool,

		Glfix_LayoutType_Int1,
		Glfix_LayoutType_Int2,
		Glfix_LayoutType_Int3,
		Glfix_LayoutType_Int4,

		Glfix_LayoutType_Float1,
		Glfix_LayoutType_Float2,
		Glfix_LayoutType_Float3,
		Glfix_LayoutType_Float4,

		//there if used
		Glfix_LayoutType_Vec2,
		Glfix_LayoutType_Vec3,
		Glfix_LayoutType_Vec4,

		Glfix_LayoutType_Mat2,
		Glfix_LayoutType_Mat3,
		Glfix_LayoutType_Mat4,

	} Glfix_VertexLayout_Element;

	//defines a Layout
	typedef struct
	{
		Glfix_VertexLayout_Element* elements;
		bool* normalize;
		uint32_t elementCount;

	} Glfix_VertexLayout_Layout;

	//gets the size of a data type
	inline uint32_t Glfix_VertexLayout_GetDataTypeSize(Glfix_VertexLayout_Element type)
	{
		switch (type)
		{
		case Glfix_LayoutType_None:
			return 0;
		case Glfix_LayoutType_Float1:
			return 4;
		case Glfix_LayoutType_Float2:
			return 8;
		case Glfix_LayoutType_Float3:
			return 12;
		case Glfix_LayoutType_Float4:
			return 16;
		case Glfix_LayoutType_Mat3:
			return 36;
		case Glfix_LayoutType_Mat4:
			return 64;
		case Glfix_LayoutType_Int1:
			return 4;
		case Glfix_LayoutType_Int2:
			return 8;
		case Glfix_LayoutType_Int3:
			return 12;
		case Glfix_LayoutType_Int4:
			return 16;
		case Glfix_LayoutType_Bool:
			return 1;
		}

		LogError("Layout Type", "Unknown shader data type.\n");
		return 0;
	}

	//gets the count of a data type || float3 = 3
	inline uint32_t Glfix_VertexLayout_GetComponentCount(Glfix_VertexLayout_Element type)
	{
		switch (type)
		{
		case Glfix_LayoutType_None:
			return 0;
		case Glfix_LayoutType_Float1:
			return 1;
		case Glfix_LayoutType_Float2:
			return 2;
		case Glfix_LayoutType_Float3:
			return 3;
		case Glfix_LayoutType_Float4:
			return 4;
		case Glfix_LayoutType_Mat3:
			return 9;
		case Glfix_LayoutType_Mat4:
			return 16;
		case Glfix_LayoutType_Int1:
			return 1;
		case Glfix_LayoutType_Int2:
			return 2;
		case Glfix_LayoutType_Int3:
			return 3;
		case Glfix_LayoutType_Int4:
			return 4;
		case Glfix_LayoutType_Bool:
			return 1;
		default:
			LogError("Layout Type", "Unknown shader data type.\n");
			return 0;
		}
	}

	//converts the element to the native Render API data type
	uint32_t Glfix_VertexLayout_GetNativeAPIType(Glfix_VertexLayout_Element type);

#ifdef __cplusplus
}
#endif

#endif