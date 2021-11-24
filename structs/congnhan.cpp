/**
 * CÔNG NHÂN
 * 
 * File này chứa khai báo cấu trúc của đối tượng Công Nhân và
 * Danh Sách Công Nhân. Danh sách sử dụng liên kết đôi.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <ngaythang.cpp>
#include <funcs.cpp>

using namespace std;

struct CongNhan {
	int maCN;
	char hoTen[30];
	char queQuan[50];
	char SDT[14];
	NgayThang ngaySinh;

	void input() {
		cout << " + Ma Cong Nhan          : ";
		cin >> maCN;

		cout << " + Ho Ten Cong Nhan      : ";
		getl(hoTen);

		cout << " + Que Quan              : ";
		getl(queQuan);

		cout << " + SDT (<= 14 ki tu)     : ";
		getl(SDT);

		//        + Ngay Sinh (dd/mm/yyyy):
		ngaySinh.input(" + Ngay Sinh");
	}

	void print() {
		cout
			<< setw(8) << maCN
			<< setw(18) << hoTen
			<< setw(16) << queQuan
			<< setw(14) << SDT
			<< setw(12) << ngaySinh
			<< endl;
	}

	friend ostream &operator<<(ostream &os, CongNhan cn) {
		os << cn.hoTen;
		return os;
	}
};

/**
 * Cấu trúc của danh sách Công Nhân
 * Sử dụng liên kết đơn
 * 
 * @version	1.0
 */
struct CongNhanList {
	struct Node {
		CongNhan info;
		Node *next = NULL;
	};

	struct List {
		Node *head = NULL;
		Node *tail = NULL;
	};

	List list;
	char file[13] = "congnhan.dat";

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		Node *node = list.head;
		FILE *fileHandler = fopen(file, "wb");

		while (node) {
			fwrite(&node -> info, sizeof(CongNhan), 1, fileHandler);
			node = node -> next;
		}

		fclose(fileHandler);
	}

	void load() {
		cout << "Đang đọc " << file << "..." << endl;
		list = *new List;
		FILE *fileHandler = fopen(file, "rb");

		do {
			CongNhan congNhan;
			fread(&congNhan, sizeof(CongNhan), 1, fileHandler);
			push(congNhan);
		} while(!feof(fileHandler));

		fclose(fileHandler);
	}

	/**
	 * Chèn thêm một công nhân mới vào cuối danh sách
	 * @param	congNhan	Công nhân cần chèn
	 */
	void push(CongNhan congNhan) {
		Node *node;
		node -> info = congNhan;

		if (list.head == NULL) {
			node -> next = NULL;
			list.head = node;
			list.tail = node;
		} else {
			list.tail -> next = node;
			list.tail = node;
		}
	}

	/**
	 * Xóa một công nhân ở phía cuối danh sách.
	 */
	void pop() {
		if (list.tail == NULL)
			return;

		Node *node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> next == list.tail) {
				list.tail = node;
				free(node -> next);
				node -> next = NULL;

				return;
			}
	}

	void print() {
		cout
			<< setw(8) << "Ma CN"
			<< setw(18) << "Ho Ten"
			<< setw(16) << "Que Quan"
			<< setw(14) << "SDT"
			<< setw(12) << "Ngay Sinh"
			<< endl;

		Node *node;
		for (node = list.head; node != NULL; node = node -> next)
			node -> info.print();
	}

	CongNhan getCongNhan(int maCN) {
		Node *node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> info.maCN == maCN)
				return node -> info;
	}
};