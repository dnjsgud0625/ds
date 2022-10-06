#include "Graph.h"
#include <map>
#include <stack>
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>

Graph::Graph(ofstream* flog)
{
	this->flog = flog;
	mstMatrix = 0;
}

Graph::~Graph()
{
}

bool Graph::Build(AVLTree * root) //make grape
{
	mList = new map<int,int>;
	this->size = root->nodesize; //get size
	AVLNode* p1 = root->root;
	stack<AVLNode*> k;
	this->mList = new map<int, int>[size]; //allocation
	this->vertex = new CityData * [size];
	int count = 0;
	if (root == NULL) //if root empty
		return false;
	while (1) { //loop
		while (p1 != NULL) { //root exist
			k.push(p1); //insert
			p1 = p1->GetLeft(); //move left nodes
		}
		if (!k.empty()) { //stack not empty
			p1 = k.top(); //receive node
			k.pop(); //remove stack
			vertex[count++] = p1->GetCityData();
			p1 = p1->GetRight(); //move right node
		}
		else
			break;
	}

	for (int i = 0; i < size; i++) { //input gap of two city
		for (int j = 0; j < size; j++) {
			if (i == j) //if 0
				continue;
			this->mList[i][j] = abs(vertex[i]->GetLocationId() - vertex[j]->GetLocationId());
		}
	}

	for (int i = 0; i < size; i++) { //get data without same part
		for (int j = 0; j <= i; j++) {
			if (i == j) continue;
			addEdge(i, j, this->mList[i][j]);
		}
	}
	return true;
}

bool Graph::Print_GP() //print grape
{
	ofstream fout("log.txt", ios::app); //file open
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int data;
			if (i == j) //distance gap is 0
				data = 0;
			else //depart
			{
				data = this->mList[i][j]; //get data
			}
			fout.setf(ios::left); //print
			fout << setw(3) << (data);
		}
		fout << endl;
	}
	fout << endl;
	fout.close();
	return true;
}

bool Graph::Print_MST() //print mst
{
	ofstream fout("log.txt", ios::app); //file open
	int total = 0;
	vector< pair<int, pair<int, int>>>::iterator st;
	for (st = shortest.begin(); st != shortest.end(); st++) { //repeat
		int dis = st->first; //distance
		int from = st->second.first; //from
		int to = st->second.second; //to
		total += dis; //total
	
		fout << "( " << vertex[from]->Getname() << ", " << vertex[to]->Getname() << " ), " << dis << endl; //print
	}
	fout << "Total: " << total << endl;
	fout << endl;
	fout.close();
	return true;
}

void Graph::addEdge(int u, int v, int w) //addedge
{
	edges.push_back({ w,{u,v} }); //add data into edge
}

bool Graph::Kruskal() //Kruskal algorithm
{
	sort(edges.begin(), edges.end()); //sort data
	make_set(); //set 

	vector< pair<int, pair<int, int>>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++) {
		int u = it->second.first;
		int v = it->second.second;
		int min = it->first;

		int set_u = find(u); //find parent and figure make cycle
		int set_v = find(v);

		if (set_u != set_v) { //if parent not same
			union_set(set_u, set_v); //set inputed vertex
			shortest.push_back(make_pair(min, make_pair(u, v))); //save into shortest
		}
	}
	return true;
}

void Graph::make_set() //makeset
{
	for (int i = 0; i < size; i++) {
		parent[i] = i; //every element is parent of itself
		rank[i] = 0; //tree high
	}
}

void Graph::union_set(int x, int y) //union
{
	x = find(x);
	y = find(y);

	if (x == y)
		return;
	//make tree with smaller height a subtree of the other tree
	if (rank[x] < rank[y]) {
		parent[x] = y;
	}
	else if (rank[x] > rank[y]) { //keep find and change every parent node to root
		parent[y] = x;
	}
	else {
		parent[y] = x;
		rank[y]++;
	}
}

int Graph::find(int x) //find
{
	//make the parent of the node in the path
	//x->panent[x] point to parent[x]
	if (x!=parent[x]){
		parent[x] = find(parent[x]);
	}
	return parent[x];
}
