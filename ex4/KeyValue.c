#include "KeyValue.h"
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

int createKeyValue(KeyValue* keyValue, char* key, char* value) {
	char* copiedKey;

	if (copyString(&copiedKey, key) == SUCCESS && copiedKey != NULL) {
		keyValue->key = copiedKey;
	} else {
		return FAILURE;
	}

	char* copiedValue;
	
	if (copyString(&copiedValue, value) == SUCCESS && copiedValue != NULL) {
		keyValue->value = copiedValue;
	} else {
		return FAILURE;
	}

	return SUCCESS;
}

int copyString(char** dst, char* src) {
	int size = strlen(src) + 1;
	char* copiedString = (char*)malloc(size * sizeof(char));

	if (copiedString != NULL && strcpy_s(copiedString, size, src) == 0) {
		*dst = copiedString;
		return SUCCESS;
	}
	
	return FAILURE;
}

