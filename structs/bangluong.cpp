/**
 * BẢNG LƯƠNG
 * 
 * File này chứa khai báo cấu trúc của đối tượng Sản Phẩm của Bảng Lương, 
 * Bảng Lương và Danh Sách Bảng Lương. Danh sách sử dụng liên kết đôi.
 * 
 * @version	1.0
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <funcs.cpp>
#include <congnhan.cpp>
#include <sanpham.cpp>

const float THUE = 0.03f;

struct BangLuong {
	struct SanPhamBangLuong {
		char maSP[8];
		int soLuong;
		float thanhTien;
	};

	int maBL;
	int thang;
	int nam;
	int maCN;
	SanPhamBangLuong sanPham[50];
	int soLuong = 0;
	float thue = THUE;
	float tongTien = .0f;
	
	void setCongNhanList(CongNhanList *list) {
		congNhanList = list;
	}

	void setSanPhamList(SanPhamList *list) {
		sanPhamList = list;
	}

	float luong() {
		return tongTien * (1 - thue);
	}

	CongNhan getCongNhan() {
		return congNhanList -> getCongNhan(maCN);
	}

	void print() {
		//   |******************************** BANG LUONG *******************************|
		//   |  Ma Bang Luong:     1                                       |    08/2021  |
		//   |  Cong Nhan:	       [1] Nguyen Van A                          12/34/5678  |
		//   |                                                                           |
		//   |  Danh Sach San Pham:                                                      |
		//   |  STT   Ten SP                           SL    Don Gia         Thanh Tien  |
		//   |    1   San Pham Bla                      1       2000               2000  |
		//   |    2   San Pham Bla                      1       2000               2000  |
		//   |    3   San Pham Bla                      1       2000               2000  |
		//   |                                                       ------------------  |
		//   |                                                       TONG:         6000  |
		//   |                                                       THUE (3%):     500  |
		//   |                                                      LUONG:         5500  |
		//   |  Danh Sach San Pham:                                                      |
		//   |  STT   Ten SP                           SL    Don Gia         Thanh Tien  |
		//   |                                                                           |
		//   |                              >>> TRONG! <<<                               |
		//   |                                                                           |
		//   |***************************************************************************|
		//
		//   1. Chinh Sua Thong Tin
		//   2. Them San Pham             3. Chinh Sua San Pham
		//   4. Xoa San Pham              5. Xoa Bang Luong
		//   6. Quay Lai
		// 
		//   >

		CongNhan congNhan = getCongNhan();

		// Header
		cout << "   |******************************** BẢNG LƯƠNG *******************************|" << endl;

		// First Line
		char thangNam[8];
		sprintf(thangNam, "%02d/%04d", thang, nam);
		cout << "   |  Mã Bảng Lương:     "
			 << left << setw(40) << maBL
			 << right << setw(12) << thangNam
			 << "  |" << endl;

		// Second Line
		cout << "   |  Công Nhân:         "
			 << left << setw(40) << congNhan
			 << right << setw(12) << congNhan.ngaySinh
			 << "  |" << endl;
		
		cout << "   |                                                                           |" << endl;
		cout << "   |  Danh sách sản phẩm:                                                      |" << endl;

		// Table
		cout << "   |  STT   Tên SP                           SL    Đơn Giá         Thành Tiền  |" << endl;

		tongTien = .0f;
		float thanhTien = 0;

		if (soLuong > 0) {
			SanPham sp;

			for (int i = 0; i < soLuong; i++) {
				sp = sanPhamList -> getSanPham(sanPham[i].maSP);
				thanhTien = sanPham[i].soLuong * sp.donGia;

				cout << "   |  "
					<< right << setw(3) << i + 1 << "   "
					<< left << setw(33) << sp.tenSP
					<< right << setw(2) << sanPham[i].soLuong << " "
					<< right << setw(10) << sp.donGia
					<< right << setw(18) << thanhTien
					<< "  |" << endl;

				tongTien += thanhTien;
			}

			free(&sp);
		} else {
			cout << "   |                                                                           |" << endl
				 << "   |                              >>> TRỐNG! <<<                               |" << endl
				 << "   |                                                                           |" << endl;
		}

		// Totals
		cout << "   |                                                       ------------------  |" << endl;
		cout << "   |                                                       TỔNG:"
			 << right << setw(13) << tongTien
			 << "  |" << endl;

		cout << "   |                                                       THUẾ (3%):"
			 << right << setw(8) << tongTien * thue
			 << "  |" << endl;

		cout << "   |                                                      LƯƠNG:"
			 << right << setw(13) << luong()
			 << "  |" << endl;

		cout << "   |***************************************************************************|" << endl;
	}

	void input() {
		if (!initialized) {
			cout << " + Mã Bảng Lương  : ";
			cin >> maBL;

			cout << " + Tháng          : ";
			cin >> thang;

			cout << " + Năm            : ";
			cin >> nam;

			inputMaCN(" + Mã Công Nhân   ");
		} else {
			cout << " + Mã Bảng Lương (" << setw(2) << maBL << ")       : ";
			cin >> maBL;

			cout << " + Tháng (" << setw(2) << thang << ")          : ";
			cin >> thang;

			cout << " + Năm (" << setw(4) << nam << ")          : ";
			cin >> nam;

			stringstream msg;
			msg << " + Mã Công Nhân (" << setw(2) << maCN << ") ";
			inputMaCN(msg.str());
		}
	}

	void show() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuong::show(): set CongNhan list first :bruh:" << endl;
			return;
		}

		// if (sanPhamList == NULL) {
		// 	cout << "ERROR BangLuong::show(): set SanPham list first :bruh:" << endl;
		// 	return;
		// }

		if (!initialized) {
			cout << endl;
			input();
			cout << endl;
		}

		int command;
		while (true) {
			print();

			cout << endl;
			cout << "   1. Chỉnh Sửa Thông Tin" << endl
				 << "   2. Thêm Sản Phẩm             3. Chỉnh Sửa Sản Phẩm" << endl
				 << "   4. Xóa Sản Phẩm              5. Xóa Bảng Lương" << endl
				 << "   6. Quay Lại" << endl;

			cout << endl << "> ";
			cin >> command;

			switch (command) {
				case 1:
					cout << endl;
					input();
					cout << endl;
					break;
				
				case 2:
					break;
				
				case 3:
					break;
				
				case 4:
					break;
				
				case 5:
					break;
				
				case 6:
					return;

				default:
					break;
			}
		}
	}

	friend ostream &operator<<(ostream &os, BangLuong bl) {
		os << bl.maBL;
		return os;
	}

	private:
		bool initialized = false;
		CongNhanList *congNhanList = NULL;
		SanPhamList *sanPhamList = NULL;

		void inputMaCN(string prompt) {
			while (true) {
				cout << prompt << ": ";
				cin >> maCN;

				try {
					cout << "   Công Nhân " << congNhanList -> getCongNhan(maCN) << endl;
				} catch(CongNhanList::NotFound error) {
					cout << "EXCP BangLuong::inputMaCN(): " << error.what() << endl;
					continue;
				}

				break;
			}
		}
};

struct BangLuongList {
	struct Node {
		BangLuong info;
		Node *next;
		Node *prev;
	};

	struct List {
		Node *head;
		Node *tail;
	};

	List list;
	char file[14] = "bangluong.dat";

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		Node *node = list.head;
		FILE *fileHandler = fopen(file, "wb");

		while (node) {
			fwrite(&node -> info, sizeof(BangLuong), 1, fileHandler);
			node = node -> next;
		}

		fclose(fileHandler);
	}

	void load() {
		cout << "Đang đọc " << file << "..." << endl;
		list = *new List;
		FILE *fileHandler = fopen(file, "rb");

		do {
			BangLuong bangLuong;
			fread(&bangLuong, sizeof(BangLuong), 1, fileHandler);
			push(bangLuong);
		} while(!feof(fileHandler));

		fclose(fileHandler);
	}

	/**
	 * Chèn thêm một bảng lương mới vào cuối danh sách
	 * @param	bangLuong	Bảng lương cần chèn
	 */
	void push(BangLuong bangLuong) {
		Node *node;
		node -> info = bangLuong;

		if (list.head == NULL) {
			node -> next = NULL;
			node -> prev = NULL;
			list.head = list.tail = node;
		} else {
			node -> next = NULL;
			node -> prev = list.tail;
			list.tail -> next = node;
			list.tail = node;
		}
	}
};