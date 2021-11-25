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
#include <congnhan.cpp>
#include <bangluong.cpp>

using namespace std;

int main() {
	CongNhanList congNhanList;
	SanPhamList sanPhamList;
	BangLuong bangLuong;

	congNhanList.load();
	congNhanList.print();

	// SanPham sanPham;
	// sanPham.input();
	// sanPhamList.insert(sanPham);
	// sanPhamList.save();
	sanPhamList.load();
	sanPhamList.print();

	bangLuong.setCongNhanList(&congNhanList);
	bangLuong.setSanPhamList(&sanPhamList);
	bangLuong.show();

	return 0;
}