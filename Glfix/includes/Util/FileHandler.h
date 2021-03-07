//defines a genaric File Handler

#ifndef FileHandler_h
#define FileHandler_h

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

	//gets the contents of a file
	const char* Glfix_FileHandler_OpenFile(const char* filepath);
	//checks if two strings match
	const char* Glfix_FileHandler_StringMatch(const char* string1, const char* string2);

#ifdef __cplusplus
}
#endif

#endif