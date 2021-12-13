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
#include <cstring>
#include <ngaythang.cpp>
#include <funcs.cpp>

using namespace std;

struct CongNhan {
	int maCN = -1;
	char hoTen[30] = "EMPTY";
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

	/**
	 * @brief
	 * Xóa Công Nhân với mã công nhân đưa vào khỏi danh sách, sau đó
	 * lưu thay đổi vào tệp.
	 * 
	 * @param	maCN
	 * 
	 * @return
	 * true nếu tìm thấy và xóa thành công,
	 * ngược lại trả về false
	 */
	bool remove(int maCN) {
		Node* node;
		Node* prev = NULL;

		for (node = list.head; node != NULL; node = node -> next) {
			if (node -> info.maCN == maCN) {
				if (prev == NULL)
					list.head = node -> next;
				else
					prev -> next = node -> next;

				cout << "Đã xóa Công Nhân [" << node -> info.maCN << "] " << node -> info.hoTen << endl;
				delete node;

				save();
				return true;
			}

			prev = node;
		}

		return false;
	}

	int size() {
		int size = 0;

		Node* node;
		for (node = list.head; node != NULL; node = node -> next)
			size += 1;

		return size;
	}

	void print() {
		listHeader();

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
			cout << " 4) Tìm Kiếm Công Nhân" << endl;
			cout << " 0) Quay Lại" << endl;

			cout << endl << " > ";
			cin >> cmd;

			switch (cmd) {
				case 1: {
					int newMaCN = 1;
					if (list.tail != NULL)
						newMaCN = list.tail -> info.maCN + 1;

					CongNhan newCongNhan;
					newCongNhan.input(newMaCN);
					push(newCongNhan);
					save();
					break;
				}

				case 2: {
					print();
					break;
				}

				case 3: {
					int maCN;

					while (true) {
						cout << "Nhập mã Công Nhân (-1 để hủy): ";
						cin >> maCN;

						if (maCN == -1 || remove(maCN))
							break;
						
						cout << "Không tìm thấy Công Nhân với mã " << maCN << endl;
					}

					break;
				}

				case 4: {
					Node* node;
					char search[30];
					bool found = false;

					cout << "Nhập chuỗi tìm kiếm: ";
					getl(search);

					listHeader();
					for (node = list.head; node != NULL; node = node -> next) {
						char hoTen[30];
						strcpy(hoTen, node -> info.hoTen);

						if (strstr(strlwr(hoTen), strlwr(search)) != NULL) {
							node -> info.print();
							found = true;
						}
					}

					if (!found)
						cout << endl << "                             >> TRỐNG <<" << endl << endl;

					break;
				}

				case 0:
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
	 * @brief Lấy thông tin Công Nhân dựa trên mã Công Nhân,
	 * throw exception khi không tìm thấy công nhân trong
	 * danh sách.
	 * 
	 * @throws	CongNhanList::NotFound
	 * @return	CongNhan
	 */
	CongNhan getCongNhan(int maCN) {
		Node* node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> info.maCN == maCN)
				return node -> info;

		throw NotFound();
	}

	private:
		void listHeader() {
			cout << "   Mã CN            Họ Tên        Quê Quán           SDT   Ngày Sinh" << endl;
		}
};
