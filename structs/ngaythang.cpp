/**
 * CÔNG NHÂN
 * 
 * File này chứa khai báo cấu trúc của đối tượng Ngày Tháng.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#include <iostream>
#include <iomanip>

using namespace std;

struct NgayThang {
	int ngay;
	int thang;
	int nam;

	void input(string prompt = "Ngay Thang") {
		cin.ignore();
		cout << prompt << " (dd/mm/yyyy): ";
		scanf("%d/%d/%d", ngay, thang, nam);
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