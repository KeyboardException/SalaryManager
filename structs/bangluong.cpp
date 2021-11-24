/**
 * BẢNG LƯƠNG
 * 
 * File này chứa khai báo cấu trúc của đối tượng Sản Phẩm của Bảng Lương, 
 * Bảng Lương và Danh Sách Bảng Lương. Danh sách sử dụng liên kết đôi.
 * 
 * @version	1.0
 */

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <funcs.cpp>

struct SanPhamBangLuong {
	char maSP[8];
	int soLuong;
	float thanhTien;
};

struct BangLuong {
	int maBL;
	int thang;
	int nam;
	int maCN;
	SanPhamBangLuong sanPham[50];
	int tongSo;
	float tongTien;

	void print() {

	}

	void input() {

	}

	friend ostream &operator<<(ostream &os, BangLuong bl) {
		os << bl.maBL;
		return os;
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