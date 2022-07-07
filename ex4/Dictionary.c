#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "KeyValue.h"

#define SUCCESS 1
#define FAILURE 0

Dictionary* createDictionary(int capacity) {
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary));

	if (dictionary != NULL) {
		dictionary->resizedFactor = 2;
		dictionary->capacity = getClosestPower(dictionary->resizedFactor, capacity);
		dictionary->size = 0;
		dictionary->data = (KeyValue*)malloc(dictionary->capacity * sizeof(KeyValue));
	}

	return dictionary;
}

int getClosestPower(int n, int wantedValue) {
	int powerOf = n;
	
	while (n < wantedValue) {
		n *= powerOf;
	}

	return n;
}

int getValue(Dictionary* dictionary, char* key, char** value) {
	for (int i = 0; i < dictionary->size; i++) {
		if (strcmp(key, dictionary->data[i].key) == 0) {
			return copyString(value, dictionary->data[i].value);
		}
	}

	return FAILURE;
}

int addValue(Dictionary* dictionary, char* key, char* value) {
	if (dictionary->size >= dictionary->capacity) {
		if (resizeArray(dictionary, dictionary->capacity * dictionary->resizedFactor) == FAILURE) {
			return FAILURE;
		}
	}

	KeyValue keyValue;

	if (createKeyValue(&keyValue, key, value) == SUCCESS) {
		dictionary->data[dictionary->size] = keyValue;
		dictionary->size++;

		return SUCCESS;
	} else {
		return FAILURE;
	}
}

int resizeArray(Dictionary* dictionary, int newSize) {
	if (newSize >= dictionary->size) {
		dictionary->capacity = newSize;
		KeyValue* biggerArray = (KeyValue*)realloc(dictionary->data, dictionary->capacity * sizeof(KeyValue));

		if (biggerArray != NULL) {
			dictionary->data = biggerArray;

			return SUCCESS;
		}
	}

	return FAILURE;
}

int removeValue(Dictionary* dictionary, char* key) {
	int index;

	if (getKeyIndex(dictionary, key, &index) == SUCCESS) {
		for (int i = index; i < dictionary->size - 1; i++) {
			dictionary->data[i] = dictionary->data[i + 1];
		}

		dictionary->size--;

		if (dictionary->size * dictionary->resizedFactor < dictionary->capacity) {
			return resizeArray(dictionary, dictionary->capacity / dictionary->resizedFactor);
		}

		return SUCCESS;
	}

	return FAILURE;
}

int getKeyIndex(Dictionary* dictionary, char* key, int* index) {
	for (int i = 0; i < dictionary->size; i++) {
		if (strcmp(dictionary->data[i].key, key) == 0) {
			*index = i;
			return SUCCESS;
		}
	}

	*index = -1;
	return FAILURE;
}

int cloneDictionary(Dictionary** dst, Dictionary* src) {
	if (dst == NULL || src == NULL) {
		return FAILURE;
	}

	*dst = (Dictionary*)malloc(sizeof(Dictionary));

	if (*dst != NULL) {
		KeyValue* data = (KeyValue*)malloc(src->capacity * sizeof(KeyValue));

		if (data != NULL) {
			for (int i = 0; i < src->size; i++) {
				KeyValue holder = src->data[i];
				KeyValue newKeyValue;

				if (createKeyValue(&newKeyValue, holder.key, holder.value) == SUCCESS) {
					(*dst)->data[i] = newKeyValue;
				} else {
					return FAILURE;
				}
			}

			(*dst)->size = src->size;
			(*dst)->capacity = src->capacity;
			(*dst)->resizedFactor = src->resizedFactor;
		}
	}

	return SUCCESS;
}

void printDictionary(Dictionary* dictionary) {
	int i;

	for (i = 0; i < dictionary->size - 1; i++) {
		printf("Key: %s, Value: %s\n", dictionary->data[i].key, dictionary->data[i].value);
	}

	printf("Key: %s, Value: %s\n", dictionary->data[i].key, dictionary->data[i].value);
}

void freeDictionary(Dictionary* dictionary) {
	if (dictionary->data != NULL) {
		for (int i = 0; i < dictionary->size; i++) {
			KeyValue keyValue = dictionary->data[i];
			if (keyValue.key != NULL) {
				free(keyValue.key);
			}

			if (keyValue.value != NULL) {
				free(keyValue.value);
			}
		}

		free(dictionary->data);
	}
}

