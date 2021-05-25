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

	} Glfix_Texture_Type;

	//defines a Texture wrapping mode
	typedef enum
	{
		Glfix_Texture_WrapMode_Repeat = 0,
		Glfix_Texture_WrapMode_MirrorRepeat = 1,
		Glfix_Texture_WrapMode_ClampEdge = 2,
		Glfix_Texture_WrapMode_ClampBorder = 3,
		//other types

	} Glfix_Texture_Wrapmode;

	//defines a Texture filtering mode
	typedef enum
	{
		Glfix_Texture_FilterMode_Nearest = 0,
		Glfix_Texture_FilterMode_Linear = 1,
		//other types

	} Glfix_Texture_Filtermode;

	//defines a Texture mip map mode
	typedef enum
	{
		Glfix_Texture_MipMapMode_NearestNearest = 0,
		Glfix_Texture_MipMapMode_LinearNearest = 1,
		Glfix_Texture_MipMapMode_NearestLinear = 2,
		Glfix_Texture_MipMapMode_LinearLinear = 3,
		//other types

	} Glfix_Texture_Mipmapmode;

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
		Glfix_Texture_Type type;
		
		//wrapping
		Glfix_Texture_Wrapmode xWrapMode; //the X axis of the texture for wrapping
		Glfix_Texture_Wrapmode yWrapMode; //the Y axis of the texture for wrapping
		Glfix_Texture_Wrapmode zWrapMode; //the Z axis of the texture for wrapping, only used if 3D
		float* borderColor; //a 4 element float array that defines the boarder color, if a wrap mode is ClampBorder.

		//filtering data
		Glfix_Texture_Filtermode minFilterMode; //ovverided if mip map is used
		Glfix_Texture_Filtermode magFilterMode;

		//mip map data
		int32_t mipMapLevel;
		Glfix_Texture_Mipmapmode mipmapMode;
		
		//image data
		int32_t width, height;
		int32_t border;
		
		Glfix_Formate internalFormate;
		Glfix_Formate externalFormate;
		Glfix_Formate pixelDatatype;

		unsigned char* extraData;

	} Glfix_Texture_CreateInfo;

	//inits create info data
	void Glfix_Texture_InitCreateInfo(Glfix_Texture_CreateInfo* info);

	//creates a Texture 2D
	Glfix_Texture* Glfix_Texture_Create2D(const char* path, Glfix_Texture_CreateInfo* info, bool flipTexture);
	//add create methods for other Texture types

	//creates a texture based on create info
	Glfix_Texture* Glfix_Texture_Create(Glfix_Texture_CreateInfo* info);

	//destroys a Texture
	void Glfix_Texture_Destroy(Glfix_Texture* texture);

	//binds a Texture
	void Glfix_Texture_Bind(Glfix_Texture* texture, uint32_t slot);
	//unbinds a Texture
	void Glfix_Texture_Unbind(Glfix_Texture* texture, uint32_t slot);

	//get native wrap mode
	int32_t Glfix_Texture_GetNativeWrapMode(Glfix_Texture_Wrapmode mode);
	//get native filter mode
	int32_t Glfix_Texture_GetNativeFilterMode(Glfix_Texture_Filtermode mode);
	//get native mipmap mode
	int32_t Glfix_Texture_GetNativeMipmapMode(Glfix_Texture_Mipmapmode mode);
	//get native texture type
	int32_t Glfix_Texture_GetNativeTextureType(Glfix_Texture_Type type);

#ifdef __cplusplus
}
#endif

#endif