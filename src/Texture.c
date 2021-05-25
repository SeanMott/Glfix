#include <gpch.h>
#include <Glfix\Texture.h>

#include <Util\FileHandler.h>

#include <string.h>
#include <glad\glad.h>
#include <stb_image.h>

#define EXTENTION_LENGTH_CAP 20

void Glfix_Texture_InitCreateInfo(Glfix_Texture_CreateInfo* info)
{
	if (!info)
	{
		LogError("NULL Texture Create Info", "Create Info could not be inited, info pointer was NULL!\n");
		return;
	}

	info->type = Glfix_TextureType_2D;

	//wrapping
	info->xWrapMode = Glfix_Texture_WrapMode_Repeat; //the X axis of the texture for wrapping
	info->yWrapMode = Glfix_Texture_WrapMode_Repeat; //the Y axis of the texture for wrapping
	info->zWrapMode = Glfix_Texture_WrapMode_Repeat; //the Z axis of the texture for wrapping, only used if 3D
	info->borderColor = calloc(4, sizeof(float)); //a 4 element float array that defines the boarder color, if a wrap mode is ClampBorder.
	info->borderColor[0] = 0.0f;
	info->borderColor[1] = 0.0f;
	info->borderColor[2] = 0.0f;
	info->borderColor[3] = 1.0f;

	//filtering data
	info->minFilterMode = Glfix_Texture_FilterMode_Linear; //ovverided if mip map is used
	info->magFilterMode = Glfix_Texture_FilterMode_Linear;

	//mip map data
	info->mipMapLevel = 0;
	info->mipmapMode = Glfix_Texture_MipMapMode_LinearLinear;

	//image data
	info->width = 0;
	info->height = 0;
	info->border = 0;

	info->internalFormate = Glfix_Formate_RGBA;
	info->externalFormate = Glfix_Formate_RGBA;
	info->pixelDatatype = Glfix_Formate_UByte;

	info->extraData = NULL;
}

Glfix_Texture* Glfix_Texture_Create2D(const char* path, Glfix_Texture_CreateInfo* info, bool flipTexture)
{
	if (!path)
	{
		LogError("Texture Path NULL", "Can not create a path from a NULL path.");
		return NULL;
	}

	//get extention
	uint32_t length = strlen(path);
	char* flippedExtention = calloc(EXTENTION_LENGTH_CAP, sizeof(char));
	uint32_t exPos = 0;
	for (int32_t i = length - 1; i > -1; i--)
	{
		if (exPos == EXTENTION_LENGTH_CAP)
		{
			LogData("Glfix Error: Extention Length Cap || What ever extention your trying to load as a Texture. It's extention is greater then %u, check Github for updates and maybe help expand the lib to support this extension. Thanks :).\n Path: \"%s\"\n", EXTENTION_LENGTH_CAP, path);
			return NULL;
		}

		//found extention
		if (path[i] == '.')
			break;

		flippedExtention[exPos] = path[i];
		exPos++;
	}

	//flip extention
	length = strlen(flippedExtention);
	char* extention = calloc(length + 1, sizeof(char));
	exPos = 0;
	for (int32_t i = length - 1; i > -1; i--)
	{
		extention[exPos] = flippedExtention[i];
		exPos++;
	}

	//settings based on file type
	int32_t numChannels = 0;
	info->extraData = stbi_load(path, &info->width, &info->height, &numChannels, 0);
	if (info->extraData)
	{
		//JPEG
		if (Glfix_FileHandler_StringMatch(extention, "jpg"))
		{
			info->internalFormate = Glfix_Formate_RGBA;
			info->externalFormate = Glfix_Formate_RGB;
			info->pixelDatatype = Glfix_Formate_UByte;
		}

		//PNG
		else if (Glfix_FileHandler_StringMatch(extention, "png"))
		{
			info->internalFormate = Glfix_Formate_RGBA;
			info->externalFormate = Glfix_Formate_RGBA;
			info->pixelDatatype = Glfix_Formate_UByte;
		}

		//if not supported
		else
		{
			LogData("Glfix Error: Unsupported Texture formate || The Texture formate is not supported. Check Github for updates or help add support to Glfix. Thanks :).\nFormate: \"%s\" Path: \"%s\"", extention, path);
			free(extention);
			free(flippedExtention);
			return NULL;
		}
	}
	else
	{
		LogData("Glfix Error: Invalid Texture Path || Failed to load a Texture from the give path, check that it is there.\nPath: \"%s\"\n", path);
		free(extention);
		free(flippedExtention);
		return NULL;
	}

	Glfix_Texture* tex = Glfix_Texture_Create(info);
	free(extention);
	free(flippedExtention);
	stbi_image_free(info->extraData);
	return tex;
}

Glfix_Texture* Glfix_Texture_Create(Glfix_Texture_CreateInfo* info)
{
	if (!info)
	{
		LogError("NULL Texture Create Info", "Create Info is NULL can not make texture!");
		return NULL;
	}

	Glfix_Texture* texture = malloc(sizeof(Glfix_Texture));
	texture->type = info->type;

	//if making a 2D texture
	if (info->type == Glfix_TextureType_2D)
	{
		texture->type = Glfix_TextureType_2D;
		glGenTextures(1, &texture->id);
		glBindTexture(GL_TEXTURE_2D, texture->id);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Glfix_Texture_GetNativeWrapMode(info->xWrapMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Glfix_Texture_GetNativeWrapMode(info->yWrapMode));

		//sets boarder color if needed
		if (info->xWrapMode == Glfix_Texture_WrapMode_ClampBorder || info->yWrapMode == Glfix_Texture_WrapMode_ClampBorder)
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, info->borderColor);

		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Glfix_Texture_GetNativeFilterMode(info->minFilterMode));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Glfix_Texture_GetNativeFilterMode(info->magFilterMode));

		//genarate texture
		glTexImage2D(GL_TEXTURE_2D, info->mipMapLevel, Glfix_Formate_GetNative(info->internalFormate), info->width, info->height, info->border,
			Glfix_Formate_GetNative(info->externalFormate), Glfix_Formate_GetNative(info->pixelDatatype), info->extraData);

		//genarate mip maps
		if (info->mipMapLevel > 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Glfix_Texture_GetNativeMipmapMode(info->mipmapMode));
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		return texture;
	}

	//others

	return texture;
}

void Glfix_Texture_Destroy(Glfix_Texture* texture)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is Null, can not destroy");
		return;
	}

	glDeleteTextures(1, &texture->id);
	free(texture);
	texture = NULL;
}

void Glfix_Texture_Bind(Glfix_Texture* texture, uint32_t slot)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is NULL can not bind.");
		return;
	}

	//sets slot
	glActiveTexture(GL_TEXTURE0 + slot);

	if (texture->type == Glfix_TextureType_2D)
		glBindTexture(GL_TEXTURE_2D, texture->id);

	//other types
}

void Glfix_Texture_Unbind(Glfix_Texture* texture, uint32_t slot)
{
	if (!texture)
	{
		LogError("NULL Texture", "Texture is NULL can not unbind.");
		return;
	}

	//sets slot
	glActiveTexture(GL_TEXTURE0 + slot);

	if (texture->type == Glfix_TextureType_2D)
		glBindTexture(GL_TEXTURE_2D, texture->id);

	//other types
}

int32_t Glfix_Texture_GetNativeWrapMode(Glfix_Texture_Wrapmode mode)
{
	switch (mode)
	{
	case Glfix_Texture_WrapMode_ClampBorder:
		return GL_CLAMP_TO_BORDER;
	case Glfix_Texture_WrapMode_ClampEdge:
		return GL_CLAMP_TO_EDGE;
	case Glfix_Texture_WrapMode_MirrorRepeat:
		return GL_MIRRORED_REPEAT;
	case Glfix_Texture_WrapMode_Repeat:
		return GL_REPEAT;

	default:
		return 0;
	}
}

int32_t Glfix_Texture_GetNativeFilterMode(Glfix_Texture_Filtermode mode)
{
	switch (mode)
	{
	case Glfix_Texture_FilterMode_Linear:
		return GL_LINEAR;
	case Glfix_Texture_FilterMode_Nearest:
		return GL_NEAREST;

	default:
		return 0;
	}
}

int32_t Glfix_Texture_GetNativeMipmapMode(Glfix_Texture_Mipmapmode mode)
{
	switch (mode)
	{
	case Glfix_Texture_MipMapMode_NearestNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case Glfix_Texture_MipMapMode_LinearLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	case Glfix_Texture_MipMapMode_LinearNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case Glfix_Texture_MipMapMode_NearestLinear:
		return GL_NEAREST_MIPMAP_LINEAR;

	default:
		return 0;
	}
}

int32_t Glfix_Texture_GetNativeTextureType(Glfix_Texture_Type type)
{
	switch (type)
	{
	case Glfix_TextureType_2D:
		return GL_TEXTURE_2D;

	default:
		return 0;
	}
}
