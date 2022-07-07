#pragma once
#include "KeyValue.h"

typedef struct Dictionary {
	int capacity;
	int size;
	KeyValue* data;
	int resizedFactor;
} Dictionary;

int getKeyIndex(Dictionary* dictionary, char* key, int* index);
int cloneDictionary(Dictionary** dst, Dictionary* src);
int resizeArray(Dictionary* dictionary, int resizeFactor);
int addValue(Dictionary* dictionary, char* key, char* value);
int getValue(Dictionary* dictionary, char* key, char** value);
int copyString(char** dst, char* src);
Dictionary* createDictionary(int capacity);
int getClosestPower(int n, int wantedValue);
void printDictionary(Dictionary* dictionary);
void freeDictionary(Dictionary* dictionary);

