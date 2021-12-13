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
#include <funcs.cpp>
#include <congnhan.cpp>
#include <sanpham.cpp>

const float THUE = 0.03f;

struct BangLuong {
	struct SanPhamBangLuong {
		char maSP[12];
		int soLuong;
		float thanhTien;

		void input(SanPhamList* sanPhamList) {
			if (sanPhamList == NULL) {
				cout << "WARN BangLuong::SanPhamBangLuong::input(): sanPhamList is NULL! Please set it first before calling this function." << endl;
				return;
			}

			SanPham sp;
			while (true) {
				cout << " + Nhập Mã Sản Phẩm: ";
				getl(maSP);

				try {
					sp = sanPhamList -> getSanPham(maSP);
					cout << "   Sản Phẩm " << sp << endl;
					break;
				} catch (SanPhamList::NotFound error) {
					cout << "EXCP BangLuong::show(2): " << error.what() << endl;
				}
			}

			cout << " + Số Lượng        : ";
			cin >> soLuong;

			thanhTien = sp.donGia * soLuong;
		}
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
		if (congNhanList == NULL) {
			cout << "ERROR BangLuongList::createBangLuong(): congNhanList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		return congNhanList -> getCongNhan(maCN);
	}

	void thangNamString(char thangNam[8]) {
		sprintf(thangNam, "%02d/%04d", thang, nam);
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
		thangNamString(thangNam);
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
		if (soLuong > 0) {
			SanPham sp;

			for (int i = 0; i < soLuong; i++) {
				sp = sanPhamList -> getSanPham(sanPham[i].maSP);

				cout << "   |  "
					<< right << setw(3) << i + 1 << "   "
					<< left << setw(33) << sp.tenSP
					<< right << setw(2) << sanPham[i].soLuong << " "
					<< right << setw(10) << sp.donGia
					<< right << setw(19) << sanPham[i].thanhTien
					<< "  |" << endl;

				tongTien += sanPham[i].thanhTien;
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

	void printRow() {
		CongNhan congNhan = getCongNhan();

		char thangNam[8];
		thangNamString(thangNam);

		cout << setw(8) << maBL
			 << setw(16) << thangNam
			 << setw(28) << congNhan.hoTen
			 << setw(16) << luong()
			 << endl;
	}

	void input(int newMaBL = -1) {
		if (!initialized) {
			if (newMaBL < 0) {
				cout << " + Mã Bảng Lương  : ";
				cin >> maBL;
			} else
				maBL = newMaBL;

			cout << " + Tháng          : ";
			cin >> thang;

			cout << " + Năm            : ";
			cin >> nam;

			inputMaCN(" + Mã Công Nhân   ");
		} else {
			cout << " + Tháng (" << setw(2) << thang << ")          : ";
			cin >> thang;

			cout << " + Năm (" << setw(4) << nam << ")          : ";
			cin >> nam;

			stringstream msg;
			msg << " + Mã Công Nhân (" << setw(2) << maCN << ") ";
			inputMaCN(msg.str());
		}

		initialized = true;
	}

	void show() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuong::show(): set CongNhan list first :bruh:" << endl;
			return;
		}

		if (sanPhamList == NULL) {
			cout << "ERROR BangLuong::show(): set SanPham list first :bruh:" << endl;
			return;
		}

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
				 << "   6. Quay Lại (Lưu Thay Đổi)" << endl;

			cout << endl << " > ";
			cin >> command;

			switch (command) {
				case 1:
					cout << endl;
					input();
					cout << endl;
					break;
				
				case 2:
					sanPhamList -> print();
					cout << endl;

					SanPhamBangLuong spbl;
					spbl.input(sanPhamList);

					sanPham[soLuong++] = spbl;
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
		CongNhanList* congNhanList = NULL;
		SanPhamList* sanPhamList = NULL;

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
		Node* next = NULL;
		Node* prev = NULL;
	};

	struct List {
		Node* head = NULL;
		Node* tail = NULL;
	};

	List list;
	char file[14] = "bangluong.dat";

	void save() {
		cout << "Đang lưu " << file << "..." << endl;
		Node* node = list.head;
		FILE* fileHandler = fopen(file, "wb");

		while (node) {
			fwrite(&node -> info, sizeof(BangLuong), 1, fileHandler);
			node = node -> next;
		}

		fclose(fileHandler);
	}

	void load() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuongList::load(): congNhanList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		if (sanPhamList == NULL) {
			cout << "ERROR BangLuongList::load(): sanPhamList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		cout << "Đang đọc " << file << "..." << endl;
		list = *new List;
		FILE* fileHandler = fopen(file, "rb");

		if (fileHandler == NULL) {
			cout << "LỖI: File " << file << " không tồn tại! Dừng việc đọc file." << endl;
			return;
		}

		while (true) {
			BangLuong bangLuong;
			fread(&bangLuong, sizeof(BangLuong), 1, fileHandler);

			if (feof(fileHandler))
				break;

			bangLuong.setCongNhanList(congNhanList);
			bangLuong.setSanPhamList(sanPhamList);
			push(bangLuong);
		}

		fclose(fileHandler);
	}

	int size() {
		int size = 0;

		if (list.head == NULL)
			return 0;

		Node* node;
		for (node = list.head; node != NULL; node = node -> next)
			size += 1;

		return size;
	}

	/**
	 * Chèn thêm một bảng lương mới vào cuối danh sách
	 * @param	bangLuong	Bảng lương cần chèn
	 */
	void push(BangLuong bangLuong) {
		Node* node = new Node;
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

	void print() {
		cout << "   Mã BL       Tháng/Năm                   Công Nhân           Lương" << endl;

		BangLuong bangLuong;
		Node* node;

		for (node = list.head; node != NULL; node = node -> next) {
			bangLuong = node -> info;
			bangLuong.printRow();
		}
	}

	BangLuong createBangLuong() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuongList::createBangLuong(): congNhanList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		if (sanPhamList == NULL) {
			cout << "ERROR BangLuongList::createBangLuong(): sanPhamList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		BangLuong bangLuong;
		bangLuong.setCongNhanList(congNhanList);
		bangLuong.setSanPhamList(sanPhamList);

		return bangLuong;
	}

	class NotFound : public exception {
		public:
			const char* what() const throw () {
				return "Bảng Lương không tồn tại!";
			}
	};

	BangLuong* getBangLuong(int maBL) {
		Node* node;

		for (node = list.head; node != NULL; node = node -> next)
			if (node -> info.maCN == maBL)
				return &node -> info;

		throw NotFound();
	}

	void setCongNhanList(CongNhanList *list) {
		congNhanList = list;
	}

	void setSanPhamList(SanPhamList *list) {
		sanPhamList = list;
	}

	void show() {
		if (congNhanList == NULL) {
			cout << "WARN BangLuongList::show(): set CongNhan list first :bruh:" << endl;
			return;
		}

		if (sanPhamList == NULL) {
			cout << "WARN BangLuongList::show(): set SanPham list first :bruh:" << endl;
			return;
		}

		int cmd;
		while (true) {
			cout << "" << endl;
			cout << " 1) Tạo Bảng Lương" << endl;
			cout << " 2) Hiện Danh Sách Bảng Lương" << endl;
			cout << " 3) Chỉnh Sửa Bảng Lương" << endl;
			cout << " 4) Xóa Bảng Lương" << endl;
			cout << " 5) Tổng Tiền Tất Cả Bảng Lương Theo Tháng" << endl;
			cout << " 6) Tổng Tiền Tất Cả Bảng Lương Theo Năm" << endl;
			cout << " 0) Quay Lại" << endl;

			cout << endl << " > ";
			cin >> cmd;

			switch (cmd) {
				case 1: {
					int newMaBL = size() + 1;

					BangLuong newBangLuong = createBangLuong();
					newBangLuong.input(newMaBL);
					newBangLuong.print();
					push(newBangLuong);
					save();
					break;
				}

				case 2: {
					print();
					break;
				}

				case 3: {
					int maBL;
					BangLuong* bangLuong;

					while (true) {
						cout << "Mã Bảng Lương Cần Sửa: ";
						cin >> maBL;

						try {
							bangLuong = getBangLuong(maBL);
							break;
						} catch (BangLuongList::NotFound error) {
							cout << "EXCP BangLuongList::show(): " << error.what() << endl;
						}
					}

					bangLuong -> show();
					save();
					break;
				}

				case 4:
					break;

				case 5: {
					float tong = .0f;
					int thang;

					cout << "Nhập tháng cần tính: ";
					cin >> thang;

					Node* node;
					for (node = list.head; node != NULL; node = node -> next)
						if (node -> info.thang == thang)
							tong += node -> info.luong();

					cout << "Tổng lương trong tháng " << thang << ": " << tong << endl;
					break;
				}

				case 6: {
					float tong = .0f;
					int nam;

					cout << "Nhập năm cần tính: ";
					cin >> nam;

					Node* node;
					for (node = list.head; node != NULL; node = node -> next)
						if (node -> info.nam == nam)
							tong += node -> info.luong();

					cout << "Tổng lương trong năm " << nam << ": " << tong << endl;
					break;
				}

				case 0:
					return;
			}
		}
	}

	private:
		CongNhanList* congNhanList = NULL;
		SanPhamList* sanPhamList = NULL;
};