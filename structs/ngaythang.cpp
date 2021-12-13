/**
 * NGÀY THÁNG
 * 
 * File này chứa khai báo cấu trúc của đối tượng Ngày Tháng.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <funcs.cpp>

using namespace std;

struct NgayThang {
	int ngay = 0;
	int thang = 0;
	int nam = 0;

	void input(string prompt = "Ngay Thang") {
		int s = 0;
		string input;

		cout << prompt << " (dd/mm/yyyy): ";
		getline(cin >> ws, input);
		
		int start = 0;
		int end = input.find('/');

		// Ngay
		ngay = stoi(input.substr(start, end - start));
		start = end + 1;
		end = input.find('/', start);

		// Thang
		thang = stoi(input.substr(start, end - start));
		start = end + 1;
		end = input.find('/', start);

		// Nam
		nam = stoi(input.substr(start, end - start));
	}

	friend ostream& operator<<(ostream& os, NgayThang n) {
		char buffer[12];
		sprintf(buffer, "%02d/%02d/%04d", n.ngay, n.thang, n.nam);
		os << buffer;

		return os;
	}

	string toString() {
		char buffer[12];
		sprintf(buffer, "%02d/%02d/%04d", ngay, thang, nam);

		ostringstream stream;
        stream << buffer;
		return stream.str();
	}
};