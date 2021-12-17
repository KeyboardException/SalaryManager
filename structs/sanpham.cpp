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
#include <funcs.cpp>

using namespace std;

struct SanPham {
	char maSP[12] = "UN00000000";
	char tenSP[50] = "EMPTY";
	float donGia = -1.0f;
	int soLuong;

	void print() {
		cout << setw(12) << maSP
			 << setw(40) << truncate(tenSP, 38)
			 << setw(20) << setprecision(1) << fixed << donGia
			 << setw(17) << soLuong
			 << setw(11) << (isBanSi() ? 'S' : 'L');

		float phi = phiVanChuyen();

		if (phi == 0)
			cout << setw(24) << "MIEN PHI";
		else
			cout << setw(24) << phi;

		cout << endl;
	}

	void input() {
		if (strcmp(maSP, "UN00000000") == 0) {
			cout << " + Mã Sản Phẩm (CCYYMMDDII): ";
			getl(maSP);
		}

		cout << " + Tên Sản Phẩm (50 kí tự) : ";
		getl(tenSP);

		cout << " + Đơn Giá                 : ";
		cin >> donGia;

		cout << " + Số Lượng                : ";
		cin >> soLuong;
	}

	bool isBanSi() {
		return soLuong > 100;
	}

	float phiVanChuyen() {
		return isBanSi() ? 0 : ((float) soLuong * donGia) * 0.5f;
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

		if (fileHandler == NULL) {
			cout << "LỖI: File " << file << " không tồn tại! Dừng việc đọc file." << endl;
			return;
		}

		while (true) {
			SanPham sanPham;
			fread(&sanPham, sizeof(SanPham), 1, fileHandler);

			if (feof(fileHandler))
				break;

			insert(sanPham);
		}

		fclose(fileHandler);
	}

	/**
	 * @brief
	 * Xóa Sản Phẩm với mã Sản Phẩm đưa vào. khỏi danh sách, sau đó
	 * lưu thay đổi vào tệp.
	 * 
	 * @param	maSP
	 * 
	 * @return
	 * true nếu tìm thấy và xóa thành công,
	 * ngược lại trả về false
	 */
	bool remove(char* maSP) {
		bool found = false;
		tree = __remove(tree, maSP, found);

		if (found)
			save();

		return found;
	}

	/**
	 * In ra bảng danh sách Sản Phẩm
	 * Cây sẽ duyệt theo thứ tự L -> N -> R
	 */
	void print() {
		bool found = false;

		listHeader();
		__printLNR(tree, found);

		if (!found)
			cout << endl << "                          >> TRỐNG <<" << endl << endl;
	}

	int size() {
		return __size(tree);
	}

	void inSanPhamCoPhiShip() {
		listHeader();
		__printY1(tree);
	}

	void sortSanPhamSiLe() {
		listHeader();
		__printY2(tree, true);
		__printY2(tree, false);
	}

	void show() {
		int cmd;
		while (true) {
			cout << "" << endl;
			cout << " 1) Thêm Sản Phẩm" << endl;
			cout << " 2) Hiện Danh Sách Sản Phẩm" << endl;
			cout << " 3) Chỉnh Sửa Sản Phẩm" << endl;
			cout << " 4) Xóa Sản Phẩm" << endl;
			cout << " 5) Tìm Kiếm Sản Phẩm" << endl;
			cout << " 6) In Sản Phẩm Có Phí Vận Chuyển" << endl;
			cout << " 7) Sắp Xếp Sản Phẩm Xỉ Lẻ" << endl;
			cout << " 0) Quay Lại" << endl;

			cout << endl << " > ";
			cin >> cmd;
			cout << endl;

			switch (cmd) {
				case 1: {
					SanPham newSanPham;
					newSanPham.input();
					insert(newSanPham);
					save();
					break;
				}

				case 2: {
					print();
					break;
				}

				case 3: {
					char maSP[12];
					SanPham* sanPham;

					while (true) {
						cout << "Mã Sản Phẩm Cần Sửa: ";
						getl(maSP);

						try {
							sanPham = getSanPham(maSP);
							break;
						} catch (SanPhamList::NotFound error) {
							cout << "EXCP SanPhamList::show(): " << error.what() << endl;
						}
					}
					
					sanPham -> input();
					save();

					break;
				}

				case 4:
					char maSP[50];

					while (true) {
						cout << "Nhập mã Sản Phẩm (-1 để hủy): ";
						cin >> maSP;

						if (strcmp(maSP, "-1") == 0 || remove(maSP))
							break;
						
						cout << "Không tìm thấy Sản Phẩm với mã " << maSP << endl;
					}

					break;

				case 5: {
					char search[30];
					bool found = false;

					cout << "Nhập chuỗi tìm kiếm: ";
					getl(search);

					listHeader();
					__searchLNR(tree, search, found);
					
					if (!found)
						cout << endl << "                          >> TRỐNG <<" << endl << endl;

					break;
				}

				case 6:
					inSanPhamCoPhiShip();
					break;

				case 7:
					sortSanPhamSiLe();
					break;

				case 0:
					return;
			}
		}
	}

	class NotFound : public exception {
		public:
			const char* what() const throw () {
				return "Sản Phẩm không tồn tại!";
			}
	};

	/**
	 * @brief
	 * Lấy thông tin Sản Phẩm dựa trên mã Sản Phẩm, 
	 * throw SanPhamList::NotFound khi không tìm thấy sản phẩm trong
	 * danh sách.
	 * 
	 * @throws	SanPhamList::NotFound
	 * @return	SanPham
	 */
	SanPham* getSanPham(char maSP[8]) {
		return __get(maSP, tree);
	}

	/**
	 * @brief
	 * Lấy thông tin Sản Phẩm dựa trên mã Sản Phẩm. 
	 * Trả về Sản Phẩm mặc định khi không tìm thấy sản phẩm trong
	 * danh sách.
	 * 
	 * @return	SanPham
	 */
	SanPham* getSanPhamSafe(char maSP[8]) {
		try {
			return __get(maSP, tree);
		} catch(NotFound e) {
			return new SanPham;
		}
	}

	private:
		void listHeader() {
			cout << "       Mã SP                                  Tên SP             Đơn Giá         Số Lượng      Sỉ/Lẻ          Phí Vận Chuyển" << endl;
		}

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

		SanPham* __get(char maSP[8], Node* root) {
			if (root == NULL)
				throw NotFound();

			int cmp = strcmp(maSP, root -> info.maSP);

			if (cmp == 0)
				return &root -> info;
			else if (cmp < 0)
				return __get(maSP, root -> left);
			else
				return __get(maSP, root -> right);
		}

		void __printLNR(Node* root, bool &found) {
			if (root == NULL)
				return;

			__printLNR(root -> left, found);

			found = true;
			root -> info.print();

			__printLNR(root -> right, found);
		}
		// in sản phẩm có phí vận chuyển
		void __printY1(Node* root) {
			if (root == NULL)
				return;

			__printY1(root -> left);

			if (root -> info.phiVanChuyen() > 0)
				root -> info.print();

			__printY1(root -> right);
		}
		// Sắp xếp sản phẩm sỉ lẻ.
		void __printY2(Node* root, bool isBanSi) {
			if (root == NULL)
				return;

			__printY2(root -> left, isBanSi);

			if ((isBanSi == root -> info.isBanSi()))
				root -> info.print();

			__printY2(root -> right, isBanSi);
		}

		void __searchLNR(Node* root, char* search, bool &found) {
			if (root == NULL)
				return;

			__searchLNR(root -> left, search, found);

			// Process
			char tenSP[50];
			strcpy(tenSP, root -> info.tenSP);

			if (strstr(strlwr(tenSP), strlwr(search)) != NULL) {
				root -> info.print();
				found = true;
			}

			__searchLNR(root -> right, search, found);
		}

		void __saveLNR(Node* root, FILE* fh) {
			if (root == NULL)
				return;
			
			__saveLNR(root -> left, fh);
			fwrite(&root -> info, sizeof(SanPham), 1, fh);
			__saveLNR(root -> right, fh);
		}

		int __size(Node* root) {
			if (root == NULL)
				return 0;

			return 1 + __size(root -> left) + __size(root -> right);
		}

		Node* __remove(Node* root, char* maSP, bool &found) {
			if (root == NULL)
				return root;

			// Recursive calls for ancestors of
			// node to be deleted
			int cmp = strcmp(maSP, root -> info.maSP);

			if (cmp < 0) {
				root -> left = __remove(root -> left, maSP, found);
				return root;
			} else if (cmp > 0) {
				root -> right = __remove(root -> right, maSP, found);
				return root;
			}

			// We reach here when root is the node
    		// to be deleted.
			found = true;
			cout << "Đã xóa Sản Phẩm [" << root -> info.maSP << "] " << root -> info.tenSP << endl;

			if (root -> left == NULL) {
				Node *temp = root -> right;
				delete root;
				return temp;
			} else if (root -> right == NULL) {
				Node *temp = root -> left;
				delete root;
				return temp;
			} else {
				Node *succParent = root;
				Node *succ = root -> right;

				while (succ -> left != NULL) {
					succParent = succ;
					succ = succ->left;
				}

				if (succParent != root)
					succParent -> left = succ -> right;
				else
					succParent -> right = succ -> right;

				root -> info = succ -> info;

				delete succ;
				return root;
			}
		}
};