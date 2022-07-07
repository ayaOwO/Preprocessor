#pragma once

typedef struct KeyValue {
	char* key;
	char* value;
} KeyValue;

int createKeyValue(KeyValue* keyValue, char* key, char* value);
int copyString(char** dst, char* src);

