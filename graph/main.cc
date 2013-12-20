/*************************************************************************
	> File Name: main.cc
	> Author: Weiang
	> Mail: weiang@mail.ustc.edu.cn 
	> Created Time: 2013年12月17日 星期二 16时59分34秒
    > Describition: 
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"

using namespace std;
typedef string DateType;

int main(void)
{
	int kd;
	cin >> kd;
	Graph<DateType> g(static_cast<GraphKind>(kd));
	int vexNum, edgeNum;
	cin >> vexNum >> edgeNum;
	//	cout << kd <<  " " << vexNum << " " << edgeNum << " " << endl;

	/**
	 * Get vertices
	 */
	for (int i = 0;i != vexNum; i ++) {
		DateType s;
		cin >> s;
		cout << s << endl;
		g.addVertex(s);
	}
	
	/**
	 * Get edges 
	 */
	switch (kd) {
		case UDG:
		case DG:
			for (int i = 0; i != edgeNum; i ++) {
				string s, d;
				cin >> s >> d;
				cout << s << " " << d << endl;
				g.addEdge(s, d);
			}
			break;

		case UDN:
		case DN:
			for (int i = 0;i != edgeNum; i ++) {
				string s, d;
				int w;
				cin >> s >> d >> w;
				cout << s  << " " << d  << w << endl;
				g.addEdge(s, d, w);
			}
			break;
		
		default:
			;
	}

	/**
	 * Test 
	 */
	g.showGraph();	// Produce "g.dot" 

	DateType s;
	switch (kd) {
		case UDG:
			cin >> s;
			cout << "BFS test(from " << s << "): " << endl;
			g.BFS(s, Graph<DateType>::print);	// Produce "BFS.dot"
			cout << endl;
			break;
		
		case UDN:
			break;

		case DG:
			cout << "DFS test: " << endl;
			g.DFS(Graph<DateType>::print);		// Produce "DFS.dot"
			cout << endl;
			break;

		case DN:
			break;

		default:
			;
	}
	return 0;
}
