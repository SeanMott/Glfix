#include <gpch.h>
#include <Glfix\Texture.h>

#include <Util\FileHandler.h>

#include <string.h>
#include <glad\glad.h>
#include <stb_image.h>

#define EXTENTION_LENGTH_CAP 20

Glfix_Texture* Glfix_Texture_Create2D(const char* path, bool flipImage, bool makeBackgroundTrans)
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

	//load based on extension
	Glfix_Texture* texture = malloc(sizeof(Glfix_Texture));
	texture->type = Glfix_TextureType_2D;

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//flips image
	stbi_set_flip_vertically_on_load(flipImage);

	//load image, create texture and generate mipmaps

	unsigned char* data = stbi_load(path, &texture->width, &texture->height, &texture->numChannels, 0);
	if (data)
	{
		//JPEG
		if (Glfix_FileHandler_StringMatch(extention, "jpg"))
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}

		//PNG
		else if (Glfix_FileHandler_StringMatch(extention, "png"))
		{
			glTexImage2D(GL_TEXTURE_2D, 0, (makeBackgroundTrans == true ? GL_RGBA : GL_RGB),
				texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		//if not supported
		else
		{
			LogData("Glfix Error: Unsupported Texture formate || The Texture formate is not supported. Check Github for updates or help add support to Glfix. Thanks :).\nFormate: \"%s\" Path: \"%s\"", extention, path);
			free(texture);
			free(extention);
			free(flippedExtention);
			stbi_image_free(data);
			return NULL;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LogData("Glfix Error: Invalid Texture Path || Failed to load a Texture from the give path, check that it is there.\nPath: \"%s\"\n", path);
		free(texture);
		free(extention);
		free(flippedExtention);
		stbi_image_free(data);
		return NULL;
	}

	free(extention);
	free(flippedExtention);
	stbi_image_free(data);
	return texture;
}

Glfix_Texture* Glfix_Texture_Create(Glfix_Texture_CreateInfo* info)
{
	if (!info)
	{
		LogError("NULL Texture Create Info", "Create Info is NULL can not make texture!");
		return NULL;
	}

	Glfix_Texture* texture = malloc(sizeof(Glfix_Texture));

	//if making a 2D texture
	if (info->type == Glfix_TextureType_2D)
	{
		texture->type = Glfix_TextureType_2D;
		glGenTextures(1, &texture->id);
		glBindTexture(GL_TEXTURE_2D, texture->id);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, info->mipMapLevel, Glfix_Formate_GetNative(info->internalFormate), info->width, info->height, 0,
			Glfix_Formate_GetNative(info->externalFormate), Glfix_Formate_GetNative(info->pixelDatatype), info->extraData);
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