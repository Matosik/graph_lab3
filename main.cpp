#include "graph.h"
#include <windows.h>
#include <conio.h>
#include <type_traits>
using namespace std;


void Print(const string& text) {
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);

	int screenWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
	int textWidth = static_cast<int>(text.size());

	int leftMargin = (screenWidth - textWidth) / 2;
	cout << string(leftMargin, ' ') << text << endl;
}

template <typename T>
T check()
{
	T value;

	while (!(cin >> value) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n')
		{
			system("cls");
			Print( "\t������� ���������� ������: ");
		}
	}
	return value;
}
template <typename T>
struct is_valid_V : std::disjunction<
	is_same<T, int>,
	is_same<T, std::string>,
	is_same<T, char>,
	is_same<T, double>
> {};

template <typename T>
struct is_valid_D : std::disjunction<
	is_same<T, int>,
	is_same<T, double>
> {};
void next() {
	Print("\n\n\t������� ����� ������, ����� ����������");
	_getch();
}
template <typename V>
vector<V>  selection_pair() {
	Print("\n\t\t����� ���� ������");
	Print( "\n\t������� ��� ������� (������): ");
	V v_from = check<V>();
	Print ( "\n\t������� ��� ������� (����): ");
	V v_to = check<V>();
	vector<V> result;
	result.push_back(v_from);
	result.push_back(v_to);
	return result;
}
template <typename V, typename D>
void Edd_vertex(Graph<V,D> &G) {
	system("cls");
	Print ("\n\t������� ��� �������, ������� ������ ��������: ");
	V v = check<V>();
	try {
		G.add_V(v);
		Print ("\t\t������� ������� ���������");
	}
	catch (const char* ex) {
		Print(ex);
	}
	next();

}


template <typename V, typename D>
typename enable_if<is_valid_V<V>::value&& is_valid_D<D>::value, void>::type
Edd_edge(Graph<V,D> &G){
	if (G.size_g() < 2) {
		return;
	}
	system("cls");
	Print("\n\t������� ��� �����: ");
	D d = check<D>();
	vector<V> pair = selection_pair<V>();
	try {
		G.add_E(pair[0], pair[1], d);
		Print("����� �� ������� '" + to_string(pair[0]) +"' � ������� '" + to_string(pair[1]) + "' ������� ���������");
	}
	catch (const char* ex) {
		Print(ex);
	}
	next();
}

int menu_1() {
	while (true) {
		system("cls");
		Print( "\n\n\n\n\n");
		Print( "�������� �������         - [ 1 ]");
		Print( "�������� �����           - [ 2 ]");
		Print( "������� �������          - [ 3 ]");
		Print( "������� �����            - [ 4 ]");
		Print( "����� � �������          - [ 5 ]");
		Print( "����� ��� ����           - [ 6 ]");
		Print( " ������ ����� ��� ������  - [ 7 ]\n");
		Print( "�����                    - [esc]");
		int key = _getch();
		if (key == 49 || key == 50 || key == 51 || key == 52 || key == 53 || key == 54 || key == 55 || key == 27) { return key; }
	}
}

template <typename V, typename D>
void main_menu() {
	Graph<V, D> G;
menu:
	int key = menu_1();
	switch (key) {
	case 49:
		Edd_vertex<V, D>(G);
		goto menu;
	case 50:
		Edd_edge<V, D>(G);
		goto menu;
	case 51:
		//delete_V<V, D>(G);
		goto menu;
	case 52:
		//delete_D<V, D>(G);
		goto menu;
	case 53:
		goto menu;
	case 54:
		goto menu;
	case 55:
		goto menu;
	case 27:
		return;

	}
}

int selection_menu(){
here:
	while (true) {
		system("cls");
		Print ( "\n\n\n\n\n");
		Print( "������� ��� ������ ������� � ��� �����");
		Print( "����� -  int,    ��� - int:	 [ 1 ]");
		Print("����� -  string, ��� - int:	 [ 2 ]");
		Print ("����� -  char,   ��� - int:	 [ 3 ]");
		Print ("����� -  double, ��� - int:	 [ 4 ]");
		Print ("  ����� -  int,    ��� - double:[ 5 ]");
		Print ("  ����� -  string, ��� - double:[ 6 ]");
		Print ("  ����� -  char,   ��� - double:[ 7 ]");
		Print ("  ����� -  double, ��� - double:[ 8 ]");

		Print( "����� - [esc]");
		int key = _getch();
		switch (key)
		{
		case(49):
			main_menu<int, int>();
			goto here;
		case(50):
			main_menu<string, int>();
		case(51):
			main_menu<char, int>();
			goto here;
		case(52):
			main_menu<double, int>();
			goto here;
		case(53):
			main_menu<int, double>();
			goto here;
		case(54):
			main_menu<string, double>();
			goto here;
		case(55):
			main_menu<char, double>();
			goto here;
		case(56):
			main_menu<double, double>();
			goto here;
		case(27):
			return -1;
		}
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	selection_menu();
}