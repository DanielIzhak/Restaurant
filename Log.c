#define _CRT_SECURE_NO_WARNINGS
#include "Log.h"

void open_Log()
{
	FILE* file = fopen(FILE_NAME, "w");
	if (file == NULL)
	{
		printf("Could not open file");
		return NULL;
	}
	fclose(file);
}

void Write_Log(char* text)
{
	FILE* file = fopen(FILE_NAME, "a");
	if (file == NULL)
	{
		printf("Could not open file");
		return NULL;
	}
	fprintf(file, "%s", text);
	fclose(file);
}