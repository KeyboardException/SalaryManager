/**
 * General Functions Definition
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
#include <iostream>
#include <cstdio>

using namespace std;

void getl(char value[]) {
	cin.clear();
	cin.ignore(1000, '\n');
	cin >> value;
	// cin.getline(value, 1000, '\n');
}