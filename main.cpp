#include "graph.h"
#include <windows.h>
#include <conio.h>
using namespace std;

int main() {
	Graph<int> a;
	a.add_V(1);
	a.add_V(2);
	a.add_V(3);
	a.add_V(4);

	a.add_E(2,1,10);
	a.add_E(1,3,4);
	a.add_E(2,3,5);
	a.add_E(2, 4, 3);

	a.delete_V(3); 
	vector<int> vv= a.walk_in_deep(3);
	for (auto i : vv) {
		cout << i << " ";
	}
	_getch();
	//a.showGraph();
}