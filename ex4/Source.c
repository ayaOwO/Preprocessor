#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define BUFFER_SIZE 100
#define FAILURE 0
#define SUCCESS 1

char** split(const char* str, int* outputCount);
int addString(char*** stringArray, int size, char* toAdd, int toAddSize);
char* parseCommand(char* line, Dictionary* variables);
int preprocess(FILE* dst);

int main(void) {
	preprocess("dst.c");


	return 0;
}


int preprocess(FILE* dst) {
	char buffer[BUFFER_SIZE];
	FILE* mainFile;
	Dictionary* variables = createDictionary(0);
	errno_t u = fopen_s(&mainFile, "main.c", "r");

	if (fopen_s(&mainFile, "main.c", "r") == 0) {

		while (fgets(buffer, BUFFER_SIZE, mainFile) != NULL) {
			parseCommand(buffer, variables);
		}
	}

	printDictionary(variables);
	freeDictionary(variables);

	return SUCCESS;
}

char* parseCommand(char* line, Dictionary* variables) {
	int size;
	line[strcspn(line,"\n")] = '\0';
	char** splittedLine = split(line, &size);
	char* command = splittedLine[0];

	if (strcmp("#define", command) == 0) {
		addValue(variables, splittedLine[1], splittedLine[2]);
	}

	for (int i = 0; i < size; i++) {
		free(splittedLine[i]);
	}

	free(splittedLine);

	return line;
}

char** split(const char* str, int* outputCount) {
	*outputCount = 0;
	int partitionSize = 0;
	char** splittedString = (char**)malloc(sizeof(char*));
	int i;
	
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') {
			char* splitStringStart = str + i - partitionSize;
			int t = addString(&splittedString, *outputCount, splitStringStart, partitionSize);
			partitionSize = 0;
			(*outputCount)++;
		}
		else {
			partitionSize++;
		}

	}
	
	char* splitStringStart = str + i - partitionSize;
	addString(&splittedString, *outputCount, splitStringStart, partitionSize);
	(*outputCount)++;

	return splittedString;
}


int addString(char*** stringArray, int size, char* toAdd, int toAddSize) {
	if (stringArray == NULL || toAdd == NULL) {
		return FAILURE;
	}

	char** holder = (char**)realloc(*stringArray, (size + 1) * sizeof(char*));

	if (holder != NULL) {
		(*stringArray) = holder;
		(*stringArray)[size] = (char*)malloc((toAddSize + 1) * sizeof(char));

		if ((*stringArray)[size] != NULL) {
			for (int j = 0; j < toAddSize; j++) {
				(*stringArray)[size][j] = toAdd[j];
			}

			(*stringArray)[size][toAddSize] = '\0';

			return SUCCESS;
		}
	}

	return FAILURE;
}
