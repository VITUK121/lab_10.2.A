#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string.h>

using namespace std;

#pragma region enums
enum Majors { RI = 1, IK, PZ, AI, KN, SA };
enum Subjects { Physics = 1, Math, IT };
#pragma endregion enums

#pragma region prototypes
void try_input(const char message[], Majors& a);
void try_input(const char message[], unsigned short& a);
#pragma endregion prototypes

#pragma region student_struct
#pragma pack(push, 1) //less memory using
struct Student {
	string return_prizv() {
		return this->prizv;
	}
	unsigned short return_course() {
		return this->course;
	}
	string return_major() {
		switch (this->major) {
		case RI:
			return "RI";
		case IK:
			return "IK";
		case PZ:
			return "PZ";
		case AI:
			return "AI";
		case KN:
			return "KN";
		case SA:
			return "SA";
		}
	}
	unsigned short return_physics() {
		return this->physics;
	}
	unsigned short return_math() {
		return this->math;
	}
	unsigned short return_it() {
		return this->it;
	}
	void fill_class(int i) {
		cout << "������� �" << i + 1 << endl;
		cout << "�������: "; cin >> this->prizv;
		try_input("����: ", this->course);
		try_input("������������� (RI=1, IK=2, PZ=3, AI=4, KN=5, SA=6): ", this->major);
		try_input("������ � ������: ", this->physics);
		try_input("������ � ����������: ", this->math);
		try_input("������ � �����������: ", this->it);
	}
private:
	string prizv;
	unsigned short course;
	Majors major;
	unsigned short physics;
	unsigned short math;
	unsigned short it;
};
#pragma pack(pop)    // return old config 
#pragma endregion student_struct

#pragma region functions
void fill_arr(Student* arr, int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = Student();
		arr[i].fill_class(i);
		cout << endl;
	}
}

void try_input(const char message[], Majors& a) {
	bool fail;
	int var;
	do {
		fail = false;
		cout << message; cin >> var;
		if (var < RI || var > SA) {
			fail = true;
		}
		else {
			a = (Majors) var;
		}
		if (cin.fail()) {
			fail = true;
			cout << "������������ ���!\n";
			cin.clear();
			cin.ignore(65535,'\n');
		}
	} while (fail);
}

void try_input(const char message[], unsigned short& a) {
	bool fail;
	do {
		fail = false;
		cout << message; cin >> a;
		if (cin.fail()) {
			fail = true;
			cout << "������������ ���!\n";
			cin.clear();
			cin.ignore(65535,'\n');
		}
	} while (fail);
}

int calc_n(int n) {
	int res = 0;
	while (n != 0) {
		n /= 10;
		res++;
	}
	return res;
}

int lenOfLongestPrizv(Student* arr, int n) {
	int res = -1;
	for (int i = 0; i < n; i++) {
		if (static_cast<int>(arr[i].return_prizv().length()) > res) {
			res = static_cast<int>(arr[i].return_prizv().length());
		}
	}
	return res;
}

void printHeader(Student* arr, int n) {
	int width = lenOfLongestPrizv(arr, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);

	cout << "=======================================================================";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "�";
	cout << "|" << setw(width) << left << "�������" << "| ���� | ������������� | Գ���� | ���������� | ����������� | " << endl;

	cout << "-----------------------------------------------------------------------";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << arr[i].return_prizv();
		cout << "|" << setw(6) << left << arr[i].return_course();
		cout << "|" << setw(15) << left << arr[i].return_major();
		cout << "|" << setw(8) << left << arr[i].return_physics();
		cout << "|" << setw(12) << left << arr[i].return_math();
		cout << "|" << setw(13) << left << arr[i].return_it();
		cout << setw(13) << "|" << endl;
	}

	cout << "-----------------------------------------------------------------------";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "-";
	}
	cout << endl;
}

void sort(Student* arr, int n) {
	Student tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j].return_course() > arr[j+1].return_course() || 
				arr[j].return_course() == arr[j + 1].return_course() && arr[j].return_it() > arr[j + 1].return_it() ||
				arr[j].return_course() == arr[j + 1].return_course() && arr[j].return_it() == arr[j + 1].return_it() && arr[j].return_prizv() < arr[j+1].return_prizv()) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

void make_index_arr(Student* arr, int n, int* mas) {
	for (int i = 0; i < n; i++) {
		mas[i] = i;
	}

	int i, j, value;
	for (int i = 1; i < n; i++) {
		value = mas[i];
		for (j = i - 1; j >= 0; j--){
			bool should_swap = false;

			if (arr[mas[j]].return_course() > arr[mas[j + 1]].return_course()) {
				should_swap = true;
			}

			else if (arr[mas[j]].return_course() == arr[mas[j + 1]].return_course() &&
				arr[mas[j]].return_it() > arr[mas[j + 1]].return_it()) {
				should_swap = true;
			}

			else if (arr[mas[j]].return_course() == arr[mas[j + 1]].return_course() &&
				arr[mas[j]].return_it() == arr[mas[j + 1]].return_it() &&
				arr[mas[j]].return_prizv() > arr[mas[j + 1]].return_prizv()) {
				should_swap = true;
			}

			if (should_swap) {
				mas[j + 1] = mas[j];
			}
			else {
				break;
			}
		}
		mas[j + 1] = value;
	}
}

void print_index_sorted(Student* arr, int n, int* index_arr) {
	int width = lenOfLongestPrizv(arr, n);
	(width <= 8) ? (width = 8) : (NULL);
	int maxDigits = calc_n(n);
	cout << "���� ����� ����� �������:\n";
	cout << "=======================================================================";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "=";
	}
	cout << endl;

	cout << "|" << setw(maxDigits) << right << "�";
	cout << "|" << setw(width) << left << "�������" << "| ���� | ������������� | Գ���� | ���������� | ����������� | " << endl;

	cout << "-----------------------------------------------------------------------";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "-";
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << "|" << setw(maxDigits) << right << i + 1;
		cout << "|" << setw(width) << left << arr[index_arr[i]].return_prizv();
		cout << "|" << setw(6) << left << arr[index_arr[i]].return_course();
		cout << "|" << setw(15) << left << arr[index_arr[i]].return_major();
		cout << "|" << setw(8) << left << arr[index_arr[i]].return_physics();
		cout << "|" << setw(12) << left << arr[index_arr[i]].return_math();
		cout << "|" << setw(13) << left << arr[index_arr[i]].return_it();
		cout << setw(13) << "|" << endl;
	}

	cout << "-----------------------------------------------------------------------";
	for (int i = 0; i < (maxDigits - 1) + (width - 8); i++) {
		cout << "-";
	}
	cout << endl;
}

void print_index_arr(int* arr, int n) {
	cout << "��������� �����: {";
	for (int i = 0; i < n; i++) {
		cout << setw(2) << arr[i];
	}
	cout << "}\n";
}

int binSearch(Student* arr, int n, string prizv, unsigned short course, unsigned short it) {
	int L = 0, R = n - 1, m;
	do {
		m = (L + R) / 2;
		if (arr[m].return_prizv() == prizv && arr[m].return_course() == course && arr[m].return_it() == it)
			return m;
		if ((arr[m].return_prizv() < prizv) || (arr[m].return_prizv() == prizv && arr[m].return_course() < course) || (arr[m].return_prizv() == prizv && arr[m].return_course() == course && arr[m].return_it() == it))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

void menu(Student* arr, int n, int* index_arr) {
	int option_1, option_2, res;
	string prizv_;
	bool _continue;
	while (true) {
		cout << "[����]: \n";
		cout << "[1] ������� ������ ��������\n";
		cout << "[2] ���������� ������ ��������\n";
		cout << "[3] ����� ��������\n";
		cout << "[4] �����\n : ";
		cin >> option_1;

		switch (option_1) {
			case 1:
				cout << "������ ��������:\n";
				printHeader(arr, n);
				break;
			case 2:
				_continue = true;
				while (_continue) {
					cout << "[1] Գ����� ������������� ������ ��������\n";
					cout << "[2] ��������� ����� ������\n";
					cout << "[3] �����\n : ";
					cin >> option_2;

					switch (option_2) {
						case 1:
							sort(arr, n);
							_continue = false;
							break;
						case 2:
							make_index_arr(arr, n, index_arr);
							print_index_arr(index_arr, n);
							print_index_sorted(arr, n, index_arr);
							_continue = false;
							break;
						case 3:
							_continue = false;
							break;
						default:
							cout << "������������ ���\n";
							break;
					}
				}
				break;

			case 3:
				unsigned short course, it;
				bool fail;
				do {
					fail = false;
					cout << "������ �������: "; cin >> prizv_;
					if (cin.fail()) {
						fail = true;
						cout << "������������ ���!\n";
						cin.clear();
						cin.ignore(65535, '\n');
					}
				} while (fail);
				try_input("������ ����: ", course);
				try_input("������ ������ � �����������: ", it);
				sort(arr, n);
				res = binSearch(arr, n, prizv_, course, it);
				(res != -1) ? (cout << "�������� �������� � �������� " << res) : (cout << "�� �������� ��������");
				cout << endl << endl;
				break;

			case 4:
				cout << "���������� ������";
				return;

			default:
				cout << "������������ ���\n";
				break;
		}
	}
}

#pragma endregion functions

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned short n;
	try_input("������ ������� ��������: ", n);

	Student* arr = new Student[n];
	int* index_arr = new int[n];

	fill_arr(arr, n);

	menu(arr, n, index_arr);

	delete[] index_arr;
	delete[] arr;
}