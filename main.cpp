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
	cout << string(leftMargin, ' ') << text;
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
			Print( "Введите корректные данные: ");
		}
	}
	return value;
}

void next() {
	Print("Нажмите любую кнопку, чтобы продолжить\n");
	_getch();
}
template <typename V>
vector<V>  selection_pair() {
	Print("Выбор пары вершин\n");
	Print( "Введите имя вершины (откуда): ");
	V v_from = check<V>();
	Print ( "Введите имя вершины (куда): ");
	V v_to = check<V>();
	vector<V> result;
	result.push_back(v_from);
	result.push_back(v_to);
	return result;
}
template <typename V, typename D>
void Edd_vertex(Graph<V,D> &G) {
	system("cls");
	Print ("\n\tВведите имя вершины, которую хотете добавить: ");
	V v = check<V>();
	try {
		G.add_V(v);
		Print ("Вершина успешно добавлена\n");
	}
	catch (const char* ex) {
		Print(ex);
	}
	next();

}


template <typename V, typename D>
void Edd_edge(Graph<V,D> &G){
	if (G.size_g() < 2) {return;}
	system("cls");
	Print("Введите вес ребра: ");
	D d = check<D>();
	vector<V> pair = selection_pair<V>();
	try {
		G.add_E(pair[0], pair[1], d);
		Print("Ребро успешно проведено\n");
	}
	catch (const char* ex) {
		Print(ex);
	}
	next();
}
template <typename V, typename D>
void delete_V(Graph<V, D>& G) {
	if (G.size_g() < 1) { return; }
	system("cls");
	Print("Введите имя вершины: ");
	V v = check<V>();
	try {
		G.delete_V(v);
		Print("Вершина удалена\n");
	}
	catch (const char* ex) {
		Print(ex);
	}
	next();

}
template <typename V, typename D>
void delete_E(Graph<V, D>& G) {
	if (G.size_g() < 2) { return; }
	system("cls");
	vector<V> pair = selection_pair<V>();
	try {
		G.delete_E(pair[0], pair[1]);
	}
	catch (const char* ex) {
		Print(ex);
	}
}
template <typename V, typename D>
void deep_walk(Graph<V, D>& G) {
	if (G.size_g() < 1) { return; }
	system("cls");
	Print("Введите стртовую точку для обхода в глубину: ");
	V v = check<V>();
	try {
		vector<V> result = G.deep_cool(v);
		for (int i = 0; i < result.size(); i++) {
			//Print(result[i]);
		}
	}
	catch (const char* ex) {
		Print(ex);
	}

}
int menu_1() {
	while (true) {
		system("cls");
		Print( "\n\n\n\n\n");
		Print( "Добавить вершину         - [ 1 ]\n");
		Print( "Добавить ребро           - [ 2 ]\n");
		Print( "Удалить вершину          - [ 3 ]\n");
		Print( "Удалить ребро            - [ 4 ]\n");
		Print( "Обход в глубину          - [ 5 ]\n");
		Print( "Найти мин путь           - [ 6 ]\n");
		Print( " Лучшее место для склада  - [ 7 ]\n\n");
		Print( "Назад                    - [esc]");
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
		delete_V<V, D>(G);
		goto menu;
	case 52:
		delete_E<V, D>(G);
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
		Print( "Выбрать тип данных вершина и вес ребра\n");
		Print( "Ребро -  int,    вес - int:	 [ 1 ]\n");
		Print("Ребро -  string, вес - int:	 [ 2 ]\n");
		Print ("Ребро -  char,   вес - int:	 [ 3 ]\n");
		Print ("Ребро -  double, вес - int:	 [ 4 ]\n");
		Print ("  Ребро -  int,    вес - double:[ 5 ]\n");
		Print ("  Ребро -  string, вес - double:[ 6 ]\n");
		Print ("  Ребро -  char,   вес - double:[ 7 ]\n");
		Print ("  Ребро -  double, вес - double:[ 8 ]\n\n");

		Print( "Выход - [esc]");
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