#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
#include <vector>
using namespace std;
class Graph
{
public:
	map<int, int> *mList;	// mList[from vetex] = map<to vertex, weigth>
	CityData ** vertex;			// vetex[index] = CityData * 
	int size;					// AVLTree size
	int * mstMatrix;			// MST
	int parent[300];
	int rank[300];
	ofstream * flog;
	vector< pair<int, pair<int, int>>> edges; //weight , <from , to>
	vector< pair<int, pair<int, int>>> shortest; //weight , <from , to>

public:
	Graph(ofstream* flog);
	~Graph();

	bool	Build(AVLTree * root); //make grape
	bool 	Print_GP(); //print grape
	bool	Print_MST(); //print mst
	void	addEdge(int u, int v, int w);

	/*for Kruskal union_set*/
	bool	Kruskal(); //kurskal algorithm
	void 	make_set();
	void	union_set(int x, int y);
	int		find(int u);

};


