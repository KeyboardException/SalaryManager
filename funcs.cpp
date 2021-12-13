/**
 * General Functions Definition
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
#include <iostream>

using namespace std;

void getl(char value[]) {
	fflush(stdin);
	gets(value);
}

char* truncate(char* input, int length = 12) {
	if (strlen(input) > length) {
		char* temp = (char *) malloc(sizeof(input));
		strcpy(temp, input);

		temp[length - 1] = temp[length - 2] = temp[length - 3] = '.';
		temp[length] = '\0';
		return temp;
	}

	return input;
}