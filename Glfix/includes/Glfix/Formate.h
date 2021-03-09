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
		Glfix_Formate_Data_RGB = 0,
		Glfix_Formate_Data_RGBA,
		Glfix_Formate_Data_RGBA8,

		Glfix_Formate_Data_UByte

	} Glfix_Formate_Data;

	//converts a type to it's GL equivilant
	int32_t Glfix_Formate_GetNative(Glfix_Formate_Data type);

#ifdef __cplusplus

}
#endif

#endif