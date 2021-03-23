//the windows implementation of the File Handler

#include <gpch.h>
#include <Util\FileHandler.h>

#include <string.h>
#include <stdio.h>

	//gets the contents of a file
	const char* Glfix_FileHandler_ReadFile(const char* filepath)
	{
		FILE* file;
		char* text = 0;
		long length;

		file = fopen(filepath, "rb");
		if (!file)
		{
			LogData("Glfix Error: File Handler || Failed to open file at: %s\n", filepath);
			return NULL;
		}

		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		text = calloc(length, length);
		if (text)
			fread(text, 1, length, file);

		fclose(file);

		return text;
	}

	//checks if two strings match
	bool Glfix_FileHandler_StringMatch(const char* string1, const char* string2)
	{
		return (strcmp(string1, string2) == 0 ? true : false);
	}