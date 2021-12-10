/**
 * PROGRAM ENTRY FILE
 * 
 * BTL Cấu Trúc Dữ Liệu & Giải Thuật - Nhóm 02
 * 
 * Thành Viên:
 *  + Nguyễn Đức Cảnh	- 2010A01
 *  + Vũ Tuấn Đạt 		- 2010A01
 *  + Đỗ Mạnh Hà 		- 2010A03
 *  + Nguyễn Văn Thụy 	- 2010A01
 * 
 * File Báo Cáo:
 * https://1drv.ms/w/s!AgsItGd8_BzBiQqZ0AON0kHPf45R
 * 
 * @version	1.0
 * @license	MIT
 */ 

#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <congnhan.cpp>
#include <sanpham.cpp>
#include <bangluong.cpp>

using namespace std;

int main() {
	SetConsoleOutputCP(CP_UTF8);

	CongNhanList congNhanList;
	SanPhamList sanPhamList;
	BangLuongList bangLuongList;

	// Attempt to read data from files
	congNhanList.load();
	sanPhamList.load();

	bangLuongList.setCongNhanList(&congNhanList);
	bangLuongList.setSanPhamList(&sanPhamList);
	bangLuongList.load();

	int cmd;
	while (true) {
		cout << "" << endl;
		cout << " 1) Quản lí danh sách công nhân" << endl;
		cout << " 2) Quản lí danh sách sản phẩm" << endl;
		cout << " 3) Quản lí bảng lương" << endl;
		cout << " 4) Thoát" << endl;

		cout << endl << " > ";
		cin >> cmd;

		switch (cmd) {
			case 1: {
				congNhanList.show();
				break;
			}

			case 2: {
				sanPhamList.show();
				break;
			}

			case 3:
				bangLuongList.show();
				break;

			case 4:
				return 0;
		}
	}

	return 0;
}