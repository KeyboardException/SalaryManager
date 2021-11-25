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
	char maSP[10];
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
};

struct SanPhamList {
	struct Node {
		SanPham info;
		Node* left = NULL;
		Node* right = NULL;
	};

	Node tree;
	char file[13] = "sanpham.dat";

	/**
	 * Chèn thêm một sản phẩm mới vào cây
	 * @param	SanPham		Sản phẩm cần chèn
	 */
	void insert(SanPham info, Node* root = NULL, bool traveling = false) {
		if (root == NULL && !traveling)
			root = &tree;

		if (root != NULL) {
			int cmp = strcmp(info.maSP, root -> info.maSP);

			if (cmp < 0)
				insert(info, root -> left, true);
			else if (cmp > 0)
				insert(info, root -> right, true);
			else {
				cout << "ERROR SanPhamList::insert(): Sản Phẩm " << info.maSP << " đã tồn tại trong cây!" << endl;
				return;
			}
		} else {
			root = new Node;
			root -> info = info;
		}
	}

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		FILE* fileHandler = fopen(file, "wb");

		__saveLNR(&tree, fileHandler);
		fclose(fileHandler);
	}

	void load() {
		cout << "Đang đọc " << file << "..." << endl;
		tree = *new Node;
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
		__printLNR(&tree);
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

		throw NotFound();
	}

	private:
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