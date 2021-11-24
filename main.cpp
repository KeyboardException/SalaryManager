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

using namespace std;

/**
 * Sử dụng bảng băm với khóa được băm bằng thuật toán
 * tách m
 */
struct SanPham {
	// FORMAT: CCYYMMDDVV
	// EX    : VN21111901
	char maSP[8];
	char tenSP[50];
	float donGia;
};

struct SanPhamBangLuong {
	char maSP[8];
	int soLuong;
	float thanhTien;
};

/**
 * Sử dụng liên kết đôi
 */
struct BangLuong {
	int maBL;
	int thang;
	int nam;
	int maCN;
	SanPhamBangLuong sanPham[50];
	int tongSo;
	float tongTien;
};

//* |=========================================================|
//* |                          MAIN                           |
//* |=========================================================|

int main() {

}