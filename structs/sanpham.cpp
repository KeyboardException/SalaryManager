/**
 * SẢN PHẨM
 * 
 * File này chứa khai báo cấu trúc của đối tượng Sản Phẩm và
 * Danh Sách Sản Phẩm. Danh sách sử dụng cây 🌳.
 * 
 * @author	Belikhun
 * @version	1.0
 */

#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#include <filesystem>
#include <funcs.cpp>

using namespace std;

struct SanPham {
	char maSP[12];
	char tenSP[50];
	float donGia;

	void print() {
		cout << setw(12) << maSP
			 << setw(28) << tenSP
			 << setw(20) << donGia
			 << endl;
	}

	void input() {
		cout << " + Mã Sản Phẩm (CCYYMMDDII): ";
		getl(maSP);

		cout << " + Tên Sản Phẩm (50 kí tự) : ";
		getl(tenSP);

		cout << " + Đơn Giá                 : ";
		cin >> donGia;
	}

	friend ostream &operator<<(ostream &os, SanPham sp) {
		stringstream str;
		str << "[" << setw(10) << sp.maSP << "] " << sp.tenSP;
		os << str.str();
		return os;
	}
};

struct SanPhamList {
	struct Node {
		SanPham info;
		Node* left = NULL;
		Node* right = NULL;
	};

	Node* tree = NULL;
	char file[13] = "sanpham.dat";

	/**
	 * Chèn thêm một sản phẩm mới vào cây
	 * @param	SanPham		Sản phẩm cần chèn
	 */
	void insert(SanPham info) {
		__insert(info, tree);
	}

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		FILE* fileHandler = fopen(file, "wb");

		__saveLNR(tree, fileHandler);
		fclose(fileHandler);
	}

	void load() {
		cout << "Đang đọc " << file << "..." << endl;
		tree = NULL;
		FILE* fileHandler = fopen(file, "rb");

		do {
			SanPham sanPham;
			fread(&sanPham, sizeof(SanPham), 1, fileHandler);
			insert(sanPham);
		} while (!feof(fileHandler));

		fclose(fileHandler);
	}

	/**
	 * In ra bảng danh sách Sản Phẩm
	 * Cây sẽ duyệt theo thứ tự L -> N -> R
	 */
	void print() {
		cout << "       Mã SP                      Tên SP             Đơn Giá" << endl;
		__printLNR(tree);
	}

	class NotFound : public exception {
		public:
			const char* what() const throw () {
				return "Sản Phẩm không tồn tại!";
			}
	};

	/**
	 * Lấy thông tin Sản Phẩm dựa trên mã Sản Phẩm,
	 * throw exception khi không tìm thấy sản phẩm trong
	 * danh sách.
	 * 
	 * @return	SanPham
	 * @throw	SanPhamList::NotFound
	 */
	SanPham getSanPham(char maSP[8]) {
		return __get(maSP, tree);
	}

	private:
		void __insert(SanPham info, Node* &root) {
			if (root != NULL) {
				int cmp = strcmp(info.maSP, root -> info.maSP);

				if (cmp < 0)
					__insert(info, root -> left);
				else if (cmp > 0)
					__insert(info, root -> right);
				else {
					cout << "ERROR SanPhamList::insert(): Sản Phẩm " << info.maSP << " đã tồn tại trong cây!" << endl;
					return;
				}
			} else {
				root = new Node;
				root -> info = info;
			}
		}

		SanPham __get(char maSP[8], Node* root) {
			if (root == NULL)
				throw NotFound();

			int cmp = strcmp(maSP, root -> info.maSP);

			if (cmp == 0)
				return root -> info;
			else if (cmp < 0)
				return __get(maSP, root -> left);
			else
				return __get(maSP, root -> right);
		}

		void __printLNR(Node* root) {
			if (root == NULL)
				return;

			__printLNR(root -> left);
			root -> info.print();
			__printLNR(root -> right);
		}

		void __saveLNR(Node* root, FILE* fh) {
			if (root == NULL)
				return;
			
			__saveLNR(root -> left, fh);
			fwrite(&root -> info, sizeof(SanPham), 1, fh);
			__saveLNR(root -> right, fh);
		}
};