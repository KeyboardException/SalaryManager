/**
 * CÔNG NHÂN
 * 
 * File này chứa khai báo cấu trúc của đối tượng Công Nhân và
 * Danh Sách Công Nhân. Danh sách sử dụng liên kết đơn.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
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

	void input(int newMaCN = -1) {
		if (maCN < 0) {
			cout << " + Mã Công Nhân          : ";
			cin >> maCN;
		} else
			maCN = newMaCN;

		cout << " + Họ Tên Công Nhân      : ";
		getl(hoTen);

		cout << " + Quê Quán              : ";
		getl(queQuan);

		cout << " + SDT (<= 14 kí tự)     : ";
		getl(SDT);

		//        + Ngay Sinh (dd/mm/yyyy):
		ngaySinh.input(" + Ngày Sinh");
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
		stringstream str;
		str << "[" << setw(3) << cn.maCN << "] " << cn.hoTen;
		os << str.str();
		return os;
	}
};

struct CongNhanList {
	struct Node {
		CongNhan info;
		Node* next = NULL;
	};

	struct List {
		Node* head = NULL;
		Node* tail = NULL;
	};

	List list;
	char file[13] = "congnhan.dat";

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		Node* node = list.head;
		FILE* fileHandler = fopen(file, "wb");

		while (node) {
			fwrite(&node -> info, sizeof(CongNhan), 1, fileHandler);
			node = node -> next;
		}

		fclose(fileHandler);
	}

	void load() {
		cout << "Đang đọc " << file << "..." << endl;
		list = *new List;
		FILE* fileHandler = fopen(file, "rb");

		if (fileHandler == NULL) {
			cout << "LỖI: File " << file << " không tồn tại! Dừng việc đọc file." << endl;
			return;
		}

		while (true) {
			CongNhan congNhan;
			fread(&congNhan, sizeof(CongNhan), 1, fileHandler);

			if (feof(fileHandler))
				break;

			push(congNhan);
		}

		fclose(fileHandler);
	}

	/**
	 * Chèn thêm một công nhân mới vào cuối danh sách
	 * @param	congNhan	Công nhân cần chèn
	 */
	void push(CongNhan congNhan) {
		Node* node = new Node;
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
	 * Xóa một công nhân ở phía cuối danh sách và trả về công nhân
	 * đã bị xóa.
	 * 
	 * @return	CongNhan
	 */
	CongNhan* pop() {
		if (list.tail == NULL)
			return NULL;

		CongNhan* info;
		Node* node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> next == list.tail) {
				list.tail = node;
				info = &(node -> next -> info);
				free(node -> next);
				node -> next = NULL;

				return info;
			}

		return NULL;
	}

	int size() {
		int size = 0;

		Node* node;
		for (node = list.head; node != NULL; node = node -> next)
			size += 1;

		return size;
	}

	void print() {
		cout << "   Mã CN            Họ Tên        Quê Quán           SDT   Ngày Sinh" << endl;

		Node* node;
		for (node = list.head; node != NULL; node = node -> next)
			node -> info.print();
	}

	void show() {
		int cmd;
		while (true) {
			cout << "" << endl;
			cout << " 1) Thêm Công Nhân" << endl;
			cout << " 2) Hiện Danh Sách Công Nhân" << endl;
			cout << " 3) Xóa Công Nhân" << endl;
			cout << " 4) Quay Lại" << endl;

			cout << endl << " > ";
			cin >> cmd;

			switch (cmd) {
				case 1: {
					int newMaCongNhan = size() + 1;

					CongNhan newCongNhan;
					newCongNhan.input(newMaCongNhan);
					push(newCongNhan);
					save();
					break;
				}

				case 2: {
					print();
					break;
				}

				case 3: {
					
					break;
				}

				case 4:
					return;
			}
		}
	}

	class NotFound : public exception {
		public:
			const char* what() const throw () {
				return "Công Nhân không tồn tại!";
			}
	};

	/**
	 * Lấy thông tin Công Nhân dựa trên mã Công Nhân,
	 * throw exception khi không tìm thấy công nhân trong
	 * danh sách.
	 * 
	 * @return	CongNhan
	 * @throw	CongNhanList::NotFound
	 */
	CongNhan getCongNhan(int maCN) {
		Node* node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> info.maCN == maCN)
				return node -> info;

		throw NotFound();
	}
};
