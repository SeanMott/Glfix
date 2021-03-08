#include <gpch.h>
#include <Glfix\Formate.h>

#include <glad\glad.h>

int32_t Glfix_Formate_GetNative(Glfix_Formate_Data type)
{
	switch (type)
	{
	case Glfix_Formate_Data_RGB:
		return GL_RGB;
		break;

	case Glfix_Formate_Data_RGBA:
		return GL_RGBA;
		break;

	case Glfix_Formate_Data_RGBA8:
		return GL_RGBA8;
		break;

	case Glfix_Formate_Data_UByte:
		return GL_UNSIGNED_BYTE;
		break;

	default:
		LogError("Formate Type Undefined", "When making a formate type native make sure it's valid. If the type your looking for isn't on a Github updates, please help expand the library.");
		return -1;

		break;
	}
}