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

void printLuongOfCongNhan(CongNhanList cn, BangLuongList bl) {
	cout << "      Mã CN                        Tên CN          Số Bảng Lương                 Tổng Lương" << endl;

	float tong = 0;
	float soBL = 0;
	CongNhanList::Node* cnNode;
	BangLuongList::Node* blNode;
	
	for (cnNode = cn.list.head; cnNode != NULL; cnNode = cnNode -> next) {
		tong = 0;
		soBL = 0;

		// Tính tổng lương
		for (blNode = bl.list.head; blNode != NULL; blNode = blNode -> next) {
			if (blNode -> info.maCN == cnNode -> info.maCN) {
				soBL++;
				tong += blNode -> info.luong();
			}
		}

		cout << setw(11) << cnNode -> info.maCN
			 << setw(30) << cnNode -> info.hoTen
			 << setw(23) << soBL
			 << setw(27) << setprecision(2) << fixed << tong
			 << endl;
	}
}

void printTotalOfSanPham(SanPhamList::Node* root, BangLuongList bl) {
	if (root == NULL)
		return;

	printTotalOfSanPham(root -> left, bl);

	int tong = 0;
	BangLuongList::Node* blNode;
	for (blNode = bl.list.head; blNode != NULL; blNode = blNode -> next)
		for (int i = 0; i < blNode -> info.soLuong; i++)
			if (strcmp(blNode -> info.sanPham[i].maSP, root -> info.maSP) == 0)
				tong += blNode -> info.sanPham[i].soLuong;
		
	cout << setw(10) << root -> info.maSP
		 << setw(40) << truncate(root -> info.tenSP, 38)
		 << setw(20) << tong
		 << setw(20) << setprecision(1) << fixed << root -> info.donGia
		 << endl;

	printTotalOfSanPham(root -> right, bl);
}

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
		cout << endl;
		cout << " 1) Quản lí danh sách công nhân   (SINGLY LINKED LIST)" << endl;
		cout << " 2) Quản lí danh sách sản phẩm    (TREE)" << endl;
		cout << " 3) Quản lí bảng lương            (DOUBLY LINKED LIST)" << endl;
		cout << " 4) Hiển thị tổng tiền lương của mỗi công nhân" << endl;
		cout << " 5) Thống kê tổng số sản phẩm đã làm của mỗi sản phẩm" << endl;
		cout << " 0) Thoát" << endl;

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
				printLuongOfCongNhan(congNhanList, bangLuongList);
				break;

			case 5: {
				cout << "     Mã SP                                  Tên SP       Tổng Số Lượng             Đơn Giá" << endl;
				printTotalOfSanPham(sanPhamList.tree, bangLuongList);
				break;
			}

			case 0:
			default:
				return 0;
		}
	}

	return 0;
}