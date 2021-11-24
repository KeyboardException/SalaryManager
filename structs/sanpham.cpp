/**
 * SẢN PHẨM
 * 
 * File này chứa khai báo cấu trúc của đối tượng Sản Phẩm và
 * Danh Sách Sản Phẩm. Danh sách sử dụng thuật toán tách m để làm khóa
 * cho bảng băm.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <funcs.cpp>

using namespace std;

const int SP_TABLE_LIMIT = 3000;

struct SanPham {
	// FORMAT: CCYYMMDDVV
	// EX    : VN21111901
	char maSP[8];
	char tenSP[50];
	float donGia;
};

struct SanPhamList {
	SanPham table[SP_TABLE_LIMIT];

	char file[12] = "sanpham.dat";

	int getKey(char maSP[8]) {
		
	}
};