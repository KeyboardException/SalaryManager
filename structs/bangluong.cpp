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

const float LUONG_CUNG = 5500000.0f;
const float THUE = 0.01f;

struct BangLuongList;

struct BangLuong {
	struct SanPhamBangLuong {
		char maSP[12];
		int soLuong;
		float thanhTien;

		/**
		 * @brief Nhập thông tin sản phẩm cho bảng lương
		 * 
		 * @param	sanPhamList 
		 * @return	true	Nếu nhập thành công mà không có lỗi gì
		 * @return	false	Nếu nhập bị lỗi hoặc người dùng hủy nhập
		 */
		bool input(SanPhamList* sanPhamList) {
			SanPham* sp;
			while (true) {
				cout << " + Nhập Mã Sản Phẩm (-1 để hủy): ";
				getl(maSP);

				if (strcmp(maSP, "-1") == 0)
					return false;

				try {
					sp = sanPhamList -> getSanPham(maSP);
					cout << "   Sản Phẩm " << *sp << endl;
					break;
				} catch (SanPhamList::NotFound error) {
					cout << "EXCP BangLuong::show(): " << error.what() << endl;
				}
			}

			cout << " + Số Lượng        : ";
			cin >> soLuong;

			thanhTien = sp -> donGia * soLuong;
			return true;
		}
	};

	int maBL;
	int thang;
	int nam;
	int maCN;
	SanPhamBangLuong sanPham[50];
	int soLuong = 0;
	float luongCung = LUONG_CUNG;
	float thue = THUE;
	float tongTien = .0f;
	
	void setCongNhanList(CongNhanList *list) {
		congNhanList = list;
	}

	void setSanPhamList(SanPhamList *list) {
		sanPhamList = list;
	}

	float luong() {
		return (tongTien + luongCung) * (1 - thue);
	}

	/**
	 * @brief Lấy công nhân với mã công nhân đưa vào, throw lỗi khi không
	 * tìm thấy Công Nhân.
	 * 
	 * @throws CongNhanList::NotFound
	 * @return CongNhan
	 */
	CongNhan getCongNhan() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuongList::createBangLuong(): congNhanList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		return *congNhanList -> getCongNhan(maCN);
	}

	/**
	 * @brief Lấy công nhân với mã công nhân đưa vào, trả về đối tượng
	 * Công Nhân mặc định nếu không tìm thấy.
	 * 
	 * @return CongNhan
	 */
	CongNhan getCongNhanSafe() {
		if (congNhanList == NULL) {
			cout << "ERROR BangLuongList::createBangLuong(): congNhanList is NULL! Please set it first before calling this function." << endl;
			exit(1);
		}

		CongNhan congNhan;

		try {
			congNhan = *congNhanList -> getCongNhan(maCN);
		} catch(CongNhanList::NotFound e) {
			// No further action needed.
		}

		return congNhan;
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

		CongNhan congNhan = getCongNhanSafe();

		// Header
		cout << endl << "   |********************************* BẢNG LƯƠNG ********************************|" << endl;

		// First Line
		char thangNam[8];
		thangNamString(thangNam);
		cout << "   |  Mã Bảng Lương:     "
			 << left << setw(42) << maBL
			 << right << setw(12) << thangNam
			 << "  |" << endl;

		// Second Line
		cout << "   |  Công Nhân:         "
			 << left << setw(42) << congNhan
			 << right << setw(12) << congNhan.ngaySinh
			 << "  |" << endl;
		
		cout << "   |                                                                             |" << endl;
		cout << "   |  Danh sách sản phẩm:                                                        |" << endl;

		// Table
		cout << "   |  STT   Tên SP                           SL      Đơn Giá         Thành Tiền  |" << endl;

		tongTien = .0f;
		if (soLuong > 0) {
			SanPham* sp;

			for (int i = 0; i < soLuong; i++) {
				try {
					sp = sanPhamList -> getSanPham(sanPham[i].maSP);
				} catch(SanPhamList::NotFound e) {
					sp = new SanPham;
				}

				cout << "   |  "
					<< right << setw(3) << i + 1 << "   "
					<< left << setw(33) << truncate(sp -> tenSP, 32)
					<< right << setw(2) << sanPham[i].soLuong << " "
					<< right << setw(12) << setprecision(1) << fixed << sp -> donGia
					<< right << setw(19) << setprecision(1) << fixed << sanPham[i].thanhTien
					<< "  |" << endl;

				tongTien += sanPham[i].thanhTien;
			}
		} else {
			cout << "   |                                                                             |" << endl
				 << "   |                               >>> TRỐNG! <<<                                |" << endl
				 << "   |                                                                             |" << endl;
		}

		cout << "   |                                                     ----------------------  |" << endl;
		cout << "   |                                                     TỔNG:"
			 << right << setw(17) << setprecision(1) << fixed << tongTien
			 << "  |" << endl;

		cout << "   |                                               LƯƠNG CỨNG:"
			 << right << setw(17) << setprecision(1) << fixed << luongCung
			 << "  |" << endl;

		cout << "   |                                                THUẾ ("
			 << setprecision(0) << fixed << (thue * 100) << "%):"
			 << right << setw(17) << setprecision(1) << fixed << (tongTien + luongCung) * thue
			 << "  |" << endl;

		cout << "   |                                                    LƯƠNG:"
			 << right << setw(17) << setprecision(1) << fixed << luong()
			 << "  |" << endl;

		cout << "   |*****************************************************************************|" << endl;
	}

	void printRow() {
		CongNhan congNhan = getCongNhanSafe();

		char thangNam[8];
		thangNamString(thangNam);

		cout << setw(8) << maBL
			 << setw(16) << thangNam
			 << setw(28) << congNhan.hoTen
			 << setw(16) << setprecision(1) << fixed << luong()
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

	int show(bool isRemoveAvailable = false) {
		if (congNhanList == NULL) {
			cout << "WARN BangLuong::show(): set CongNhan list first :bruh:" << endl;
			return 0;
		}

		if (sanPhamList == NULL) {
			cout << "WARN BangLuong::show(): set SanPham list first :bruh:" << endl;
			return 0;
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
				 << "   4. Sửa Lương Cứng            5. Sửa % Thuế" << endl
				 << "   6. Xóa Sản Phẩm";

			if (isRemoveAvailable)
				cout << "              7. Xóa Bảng Lương";

			cout << endl
				 << "   0. Quay Lại (Lưu Thay Đổi)" << endl;

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
				
				case 3: {
					int stt;

					while (true) {
						cout << "Nhập STT (-1 để hủy): ";
						cin >> stt;

						if (stt < 1 || stt > soLuong) {
							cout << "STT bạn vừa nhập không hợp lệ!" << endl;
							continue;
						}

						sanPham[stt - 1].input(sanPhamList);
						break;	
					}

					break;
				}

				case 4: {
					cout << "Lương Cứng Mới ("
						 << setprecision(1) << fixed << luongCung
						 << "): ";

					cin >> luongCung;
					break;
				}

				case 5: {
					cout << "% Thuế Mới ("
						 << setprecision(1) << fixed << thue * 100
						 << "%): ";

					cin >> thue;
					thue /= 100.0f;
					break;
				}
				
				case 6: {
					int stt;

					while (true) {
						cout << "Nhập STT (-1 để hủy): ";
						cin >> stt;

						if (stt < 1 || stt > soLuong) {
							cout << "STT bạn vừa nhập không hợp lệ!" << endl;
							continue;
						}

						cout << "Đã xóa Sản Phẩm "
							 << sanPhamList -> getSanPhamSafe(sanPham[stt - 1].maSP) -> tenSP
							 << endl;

						for (int i = stt - 1; i < soLuong; i++)
							sanPham[i] = sanPham[i + 1];

						soLuong--;
						break;
					}

					break;
				}
				
				case 7: {
					if (!isRemoveAvailable)
						continue;

					return command;
				}
				
				case 0:
					return command;

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
					cout << "   Công Nhân " << *congNhanList -> getCongNhan(maCN) << endl;
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

	/**
	 * @brief
	 * Xóa Bảng Lương với mã bảng lương đưa vào khỏi danh sách, 
	 * sau đó lưu thay đổi vào tệp.
	 * 
	 * @param	maCN
	 * 
	 * @return
	 * true nếu tìm thấy và xóa thành công,
	 * ngược lại trả về false
	 */
	bool remove(int maBL) {
		Node* node;

		for (node = list.head; node != NULL; node = node -> next) {
			if (node -> info.maBL == maBL) {
				if ((node == list.head) && (node == list.tail)) {
					list.head = NULL;
					list.tail = NULL;
				} else if (node == list.head)
					list.head = node -> next;
				else if (node == list.tail) {
					node -> prev -> next = NULL;
					list.tail = node -> prev;
				} else {
					node -> prev -> next = node -> next;
					node -> next-> prev = node -> prev;
				}

				cout << "Đã xóa Bảng Lương [" << node -> info.maBL << "]" << endl;
				delete node;

				save();
				return true;
			}
		}

		return false;
	}

	void print() {
		listHeader();

		BangLuong bangLuong;
		Node* node;
		bool found = false;

		for (node = list.head; node != NULL; node = node -> next) {
			bangLuong = node -> info;
			bangLuong.printRow();
			found = true;
		}

		if (!found)
			cout << endl << "                              >> TRỐNG! <<" << endl << endl;
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

	
	/**
	 * Sắp xếp danh sách bảng lương theo lương
	 * @author Birdchocolate said: hí ae :D
	 */
	void sort(bool ascending = false)
	{
		Node *nodeFirst, *nodeSecond;
		for (nodeFirst = list.head; nodeFirst != NULL; nodeFirst = nodeFirst -> next)
		{
			for (nodeSecond = nodeFirst -> next; nodeSecond != NULL; nodeSecond = nodeSecond -> next)
			{
				if (ascending)
				{
					if (nodeFirst -> info.luong() > nodeSecond -> info.luong())
					{
						swap(nodeFirst -> info, nodeSecond -> info);
					}
				}
				else
				{
					if (nodeFirst -> info.luong() < nodeSecond -> info.luong())
					{
						swap(nodeFirst -> info, nodeSecond -> info);
					}
				}
			}
		}
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
			if (node -> info.maBL == maBL)
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
			cout << " 3) Xem Bảng Lương" << endl;
			cout << " 4) Chỉnh Sửa Bảng Lương" << endl;
			cout << " 5) Xóa Bảng Lương" << endl;
			cout << " 6) Tổng Tiền Tất Cả Bảng Lương Theo Tháng" << endl;
			cout << " 7) Tổng Tiền Tất Cả Bảng Lương Theo Năm" << endl;
			cout << " 8) Sắp Xếp Lương Công Nhân" << endl;
			cout << " 9) Liệt Kê Các Bảng Lương Có Lương Trong Khoảng [s, e]" << endl;
			cout << " 0) Quay Lại" << endl;

			cout << endl << " > ";
			cin >> cmd;
			cout << endl;

			switch (cmd) {
				case 1: {
					int newMaBL = 1;
					if (list.tail != NULL)
						newMaBL = list.tail -> info.maBL + 1;

					BangLuong newBangLuong = createBangLuong();
					newBangLuong.input(newMaBL);

					sanPhamList -> print();
					cout << endl;

					while (true) {
						BangLuong::SanPhamBangLuong spbl;
						bool check = spbl.input(sanPhamList);
						if (!check);
							break;

						newBangLuong.sanPham[newBangLuong.soLuong++] = spbl;
					}

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
						cout << "Mã Bảng Lương Cần Xem: ";
						cin >> maBL;

						try {
							bangLuong = getBangLuong(maBL);
							break;
						} catch (BangLuongList::NotFound error) {
							cout << "EXCP BangLuongList::show(): " << error.what() << endl;
						}
					}

					bangLuong -> print();
					cout << endl;
					break;
				}

				case 4: {
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

					int command = bangLuong -> show(true);
					if (command == 5)
						remove(bangLuong -> maBL);
					else
						// Remove will call save() so we don't need to call it again.
						save();
					
					break;
				}

				case 5: {
					int maBL;

					while (true) {
						cout << "Nhập mã Bảng Lương (-1 để hủy): ";
						cin >> maBL;

						if (maBL == -1 || remove(maBL))
							break;
						
						cout << "Không tìm thấy Bảng Lương với mã " << maBL << endl;
					}

					break;
				}

				case 6: {
					float tong = .0f;
					int thang;

					cout << "Nhập tháng cần tính: ";
					cin >> thang;

					Node* node;
					for (node = list.head; node != NULL; node = node -> next)
						if (node -> info.thang == thang)
							tong += node -> info.luong();

					cout << "Tổng lương trong tháng " << thang << ": "
						 << setprecision(0) << fixed << tong << endl;
					break;
				}

				case 7: {
					float tong = .0f;
					int nam;

					cout << "Nhập năm cần tính: ";
					cin >> nam;

					Node* node;
					for (node = list.head; node != NULL; node = node -> next)
						if (node -> info.nam == nam)
							tong += node -> info.luong();

					cout << "Tổng lương trong năm " << nam << ": "
						 << setprecision(0) << fixed << tong << endl;
					
					break;
				}
				
				case 8: {
					bool follow = false;
					string cmd;
					cout << "Nhập bất kì để sắp xếp giảm dần & 'up' để tăng dần: ";
					cin >> cmd;
					if (cmd == "up")
					{
						follow = true;
					}
					sort(follow);
					print();
				}

				case 9: {
					float start;
					float end;

					cout << "Nhập khoảng lương từ: ";
					cin >> start;

					cout << "Nhập khoảng lương đến: ";
					cin >> end;

					Node* node;
					bool found = false;
					cout << endl;
					listHeader();

					for (node = list.head; node != NULL; node = node -> next)
						if (node -> info.luong() >= start && node -> info.luong() <= end) {
							node -> info.printRow();
							found = true;
						}

					if (!found)
						cout << endl << "                              >> TRỐNG! <<" << endl << endl;

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

		void listHeader() {
			cout << "   Mã BL       Tháng/Năm                   Công Nhân           Lương" << endl;
		}
};