//defines Textures

#ifndef Texture_h
#define Texture_h

#ifdef __cplusplus

extern "C" {
#endif

#include <Glfix\Formate.h>

#include <stdint.h>
#include <stdbool.h>

	//defines a Texture type
	typedef enum
	{
		Glfix_TextureType_2D = 0x01,
		//other types

	} Glfix_TextureType;

	//defines a Texture
	typedef struct
	{
		//identity data
		uint32_t id;
		uint8_t type : 1; //stores the type of texture 2D or other types
		uint8_t extention : 2; //stores the type of texture JPEG, PNG, ect

		//the dimentions and channels of the texture
		uint32_t width, height, numChannels;

	} Glfix_Texture;

	//defines create info for defining a texture
	typedef struct
	{
		Glfix_TextureType type;
		int32_t mipMapLevel;
		Glfix_Formate internalFormate;
		int32_t width, height;
		int32_t border; //is ignored when making 2D textures
		Glfix_Formate externalFormate;
		Glfix_Formate pixelDatatype;
		void* extraData;

	} Glfix_Texture_CreateInfo;

	//creates a Texture 2D
	Glfix_Texture* Glfix_Texture_Create2D(const char* path, bool flipImage, bool makeBackgroundTrans);
	//add create methods for other Texture types

	//creates a texture based on create info
	Glfix_Texture* Glfix_Texture_Create(Glfix_Texture_CreateInfo* info);

	//destroys a Texture
	void Glfix_Texture_Destroy(Glfix_Texture* texture);

	//binds a Texture
	void Glfix_Texture_Bind(Glfix_Texture* texture, uint32_t slot);
	//unbinds a Texture
	void Glfix_Texture_Unbind(Glfix_Texture* texture, uint32_t slot);

#ifdef __cplusplus
}
#endif

#endif