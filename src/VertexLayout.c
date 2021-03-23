#include <gpch.h>
#include <Glfix\VertexLayout.h>

#include <glad\glad.h>

uint32_t Glfix_VertexLayout_GetNativeAPIType(Glfix_VertexLayout_Element type)
{
	switch (type)
	{
	case Glfix_LayoutType_Float1:
		return GL_FLOAT;
	case Glfix_LayoutType_Float2:
		return GL_FLOAT;
	case Glfix_LayoutType_Float3:
		return GL_FLOAT;
	case Glfix_LayoutType_Float4:
		return GL_FLOAT;
	case Glfix_LayoutType_Mat3:
		return GL_FLOAT;
	case Glfix_LayoutType_Mat4:
		return GL_FLOAT;
	case Glfix_LayoutType_Int1:
		return GL_INT;
	case Glfix_LayoutType_Int2:
		return GL_INT;
	case Glfix_LayoutType_Int3:
		return GL_INT;
	case Glfix_LayoutType_Int4:
		return GL_INT;
	case Glfix_LayoutType_Bool:
		return GL_BOOL;
	}

	LogError("Layout Type", "Unknown shader data type.\n");
	return 0;
}