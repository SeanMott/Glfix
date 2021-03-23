//defines formates used through out Opengl

#ifndef Formate_h
#define Formate_h

#include <stdint.h>

#ifdef __cplusplus

extern "C" {
#endif

	//defines data formates
	typedef enum
	{
		Glfix_Formate_RGB = 0,
		Glfix_Formate_RGBA,
		Glfix_Formate_RGBA8,

		Glfix_Formate_UByte

	} Glfix_Formate;

	//converts a type to it's GL equivilant
	int32_t Glfix_Formate_GetNative(Glfix_Formate type);

#ifdef __cplusplus

}
#endif

#endif