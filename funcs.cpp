/**
 * Copyright (C) Team KeyboardOverflow - contact.kbexcp@gmail.com
 *
 * We publish and distribute this code in the hope that it will be useful
 * for learning purpose, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Anyone can refer to this source code and the document come alongside
 * with it. DO NOT COPY AND PASTE this code, or the document into your own
 * personal/group project.
 */

/**
 * General Functions Definition
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void getl(char value[]) {
	fflush(stdin);
	gets(value);
}

char* truncate(char* input, int length = 12) {
	if (strlen(input) > length) {
		char* temp = (char *) malloc(strlen(input) + 1);
		strcpy(temp, input);

		temp[length - 1] = temp[length - 2] = temp[length - 3] = '.';
		temp[length] = '\00';
		return temp;
	}

	return input;
}