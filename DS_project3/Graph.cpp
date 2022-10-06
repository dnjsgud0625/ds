#include "Graph.h"
#include "Result.h"
#include "MinHeap.h"
#include <set>
#include <climits>
#include <iostream>
#include <functional>
using namespace std;

Graph::Graph() { //Graph
	m_pVHead = NULL;
	m_vSize = 0;
}
Graph::~Graph() { //Graph Destructor
	Clear();
}

void Graph::AddVertex(int vertexKey) { //AddVertex
	Vertex* Vnew = new Vertex(vertexKey); // new node dynamic allocation
	if (!m_pVHead) { //head isn't exist
		m_pVHead = Vnew; //new node
	}
	else {	//head exist
		Vertex* pnt = m_pVHead;	//dynamic allocation
		while (pnt->GetNext())
			pnt = pnt->GetNext();
		pnt->SetNext(Vnew); //set Next
	}
	m_vSize++;	//size ++
}

void Graph::AddEdge(int cmdVertexKey, int endVertexKey, int weight) { //AddEdge
	if (!m_pVHead)	return;	// not exist
	Vertex* pnt = FindVertex(cmdVertexKey);
	if (!pnt)	return;
	pnt->AddEdge(endVertexKey, weight);
}

Vertex* Graph::FindVertex(int key) { //FindVertex
	if (!m_pVHead)
		return NULL; // fail

	Vertex* pnt = m_pVHead;

	while (pnt) {
		if (pnt->GetKey() == key)
			return pnt;	//success
		pnt = pnt->GetNext();
	}
	return NULL;//fail
}

int Graph::Size() const { //Size
	return m_vSize;
}

void Graph::Clear() { //Clear
	Vertex* pnt = m_pVHead;	// head
	Vertex* re_pnt = NULL;	//remove Vertex node
	Edge* finder = NULL;
	Edge* tmp = NULL; //remove Edge node
	while (pnt) {
		finder = pnt->GetHeadOfEdge();
		while (finder) { //to delete
			tmp = finder;
			finder = finder->GetNext();
			tmp->SetNext(NULL);	//delete connection
			delete tmp;	// delete
		}
		re_pnt = pnt;
		pnt = pnt->GetNext();	//pnt move
		delete re_pnt;	//delete Vertex node
	}
}

void Graph::Print(std::ofstream& fout) {	//Print
	Vertex* pnt = m_pVHead;	//head
	int Dsize = Size();
	while (pnt) {	//to Print
		Edge* pnt2 = pnt->GetHeadOfEdge();	//pnt's edge
		for (int i = 0; i < Dsize; i++) {
			if (!pnt2) {
				for (; i < Dsize; i++)
					fout << "0 ";
				break;
			}
			else if (pnt2->GetKey() == i) {
				fout << pnt2->GetWeight() << " ";
			}
			else {
				fout << "0 ";
				continue;
			}
			pnt2 = pnt2->GetNext();
		}
		fout << endl;
		pnt = pnt->GetNext();
	}
	fout << "===================" << endl << endl << endl;
}

bool Graph::IsNegativeEdge() {	//IsNegativeEdge
	Vertex* pnt = m_pVHead;	//head
	while (pnt) {	//tosearch
		Edge* pnt2 = pnt->GetHeadOfEdge();	//pnt's edge
		while (pnt2) {
			if (pnt2->GetWeight() < 0)	// negative
				return true;	//return
			pnt2 = pnt2->GetNext();
		}
		pnt = pnt->GetNext();
	}
	return false;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int cmdVertexKey, int endVertexKey) {	//FIndDijkstra using set
	vector<int> Vec;
	int* dis = new int[Size()];
	int INF = 100000;
	int* vis = new int[Size()];
	int* P = new int[Size()];
	int Cost = 0;
	int flag = 0;
	set <pair<int, int>	> s;
	//start
	for (int i = 0; i < Size(); i++) {
		dis[i] = INF;
		vis[i] = 0;
		P[i] = -1;
	}
	dis[cmdVertexKey] = 0;
	vis[cmdVertexKey] = 1;
	Vertex* pnt = FindVertex(cmdVertexKey);

	// cmd
	while (1) {
		Edge* pnt2 = pnt->GetHeadOfEdge(); //pnt's edge
		while (pnt2) {
			if (dis[pnt->GetKey()] + pnt2->GetWeight() < dis[pnt2->GetKey()]) {	//shorter distance update
				s.erase(make_pair(dis[pnt2->GetKey()], pnt2->GetKey())); //erase
				dis[pnt2->GetKey()] = dis[pnt->GetKey()] + pnt2->GetWeight(); //distance update
				P[pnt2->GetKey()] = pnt->GetKey(); //update
			}
			if (vis[pnt2->GetKey()] != 1)
				s.insert(make_pair(dis[pnt2->GetKey()], pnt2->GetKey())); //insert
			pnt2 = pnt2->GetNext();	// pnt2 move
		}
		pnt = FindVertex(s.begin()->second); //next pnt
		vis[pnt->GetKey()] = 1;	//table check
		for (int i = 0; i < Size(); i++) {	//check
			if (vis[i] != 1) {
				flag = -1;
				break;
			}
		}
		if (flag == 0 || s.empty() || pnt->GetKey() == endVertexKey) //end
			break;
		flag = 0;
		s.erase(s.begin());
	}

	// cmd Dijkstra using set cmd -> end
	// searched the reverse vetrex
	Vec.push_back(pnt->GetKey());
	pnt = FindVertex(endVertexKey);
	while (Vec.back() != cmdVertexKey) {
		pnt = FindVertex(P[pnt->GetKey()]);
		Edge* pnt2 = pnt->GetHeadOfEdge();	//pnt's edge
		while (pnt2) {
			if (pnt2->GetKey() == Vec.back()) {	 //same
				Cost += pnt2->GetWeight();	//update
				break;
			}
			pnt2 = pnt2->GetNext();	//pnt2 move
		}
		Vec.push_back(pnt->GetKey());
	}
	Vec.push_back(Cost);

	delete[]dis;
	delete[]vis;
	delete[]P;
	s.clear();
	return Vec;
}

std::vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int cmdVertexKey, int endVertexKey) {	//Find Dijkstra using minheap
	vector<int> Vec;
	int* dis = new int[Size()];
	int INF = 100000;
	int* vis = new int[Size()];
	int* P = new int[Size()];
	int Cost = 0;
	int flag = 0;
	MinHeap<int, int> m;

	//start
	for (int i = 0; i < Size(); i++) {
		dis[i] = INF;
		vis[i] = 0;
		P[i] = -1;
	}
	vis[cmdVertexKey] = 1;
	dis[cmdVertexKey] = 0;
	Vertex* pnt = FindVertex(cmdVertexKey);

	while (1) {
		Edge* pnt2 = pnt->GetHeadOfEdge(); //pnt's edge
		while (pnt2) {
			if (dis[pnt->GetKey()] + pnt2->GetWeight() < dis[pnt2->GetKey()]) {	//shorter dis update
				dis[pnt2->GetKey()] = dis[pnt->GetKey()] + pnt2->GetWeight(); //distance update
				P[pnt2->GetKey()] = pnt->GetKey();	//update
			}
			if (vis[pnt2->GetKey()] != 1)
				m.Push(dis[pnt2->GetKey()], pnt2->GetKey()); //push
			pnt2 = pnt2->GetNext();
		}
		pnt = FindVertex(m.Top().second); //next pnt
		vis[pnt->GetKey()] = 1;
		for (int i = 0; i < Size(); i++) {
			if (vis[i] != 1) {
				flag = -1;
				break;
			}
		}
		if (flag == 0 || m.IsEmpty() || pnt->GetKey() == endVertexKey) //end
			break;
		flag = 0;
		m.Pop(); //nextheap
	}
	// searched
	pnt = FindVertex(endVertexKey);
	Vec.push_back(pnt->GetKey());
	while (Vec.back() != cmdVertexKey) {
		pnt = FindVertex(P[pnt->GetKey()]);
		Edge* pnt2 = pnt->GetHeadOfEdge(); //pnt's edge
		while (pnt2) {
			if (pnt2->GetKey() == Vec.back()) {	//same
				Cost += pnt2->GetWeight();
				break;
			}
			pnt2 = pnt2->GetNext();
		}
		Vec.push_back(pnt->GetKey());
	}
	Vec.push_back(Cost);

	delete[]dis;
	delete[]vis;
	delete[]P;
	return Vec;
}

std::vector<int> Graph::FindShortestPathBellmanFord(int cmdVertexKey, int endVertexKey) {  //BellmanFord
	int flag = 0;
	vector<int> Vec;
	int Cost = 0;
	int* dis = new int[Size()];
	int* P = new int[Size()];
	int INF = 100000;

	 //start
	for (int i = 0; i < Size(); i++) {
		dis[i] = INF;
		P[i] = -1;
	}
	Vertex* pnt = m_pVHead;
	dis[cmdVertexKey] = 0;
	// Repeatedly to all Vetrex
	for (int i = 0; i < Size() + 1; i++) {
		pnt = m_pVHead;
		for (int j = 0; j < Size(); j++) {
			if (dis[pnt->GetKey()] != INF) {
				Edge* pnt2 = pnt->GetHeadOfEdge(); // pnt's edge
				while (pnt2) {
					if (dis[pnt->GetKey()] + pnt2->GetWeight() < dis[pnt2->GetKey()]) {   //shorter distance update
						if (i == Size()) {
							Vec.clear();
							return Vec;
						}
						dis[pnt2->GetKey()] = dis[pnt->GetKey()] + pnt2->GetWeight(); // distance update
						P[pnt2->GetKey()] = pnt->GetKey();
					}
					pnt2 = pnt2->GetNext();
				}
			}
			pnt = pnt->GetNext();
		}
	}
	// searched the reverse vetrex
	pnt = FindVertex(endVertexKey);
	Vec.push_back(pnt->GetKey());
	while (Vec.back() != cmdVertexKey) {
		pnt = FindVertex(P[pnt->GetKey()]);
		Edge* pnt2 = pnt->GetHeadOfEdge(); //pnt's edge
		while (pnt2) {
			if (pnt2->GetKey() == Vec.back()) {	// same
				Cost += pnt2->GetWeight();
				break;
			}
			pnt2 = pnt2->GetNext();
		}
		Vec.push_back(pnt->GetKey());
	}
	Vec.push_back(Cost);
	delete[] dis;
	delete[] P;
	return Vec;
}

std::vector<vector<int>> Graph::FindShortestPathFloyd() { //Find Floyd
	int size = Size();
	Vertex* pnt = FindVertex(0);
	vector<vector<int>> floyd(size, vector<int>(size, IN_FINITY));

	for (int i = 0; i < Size(); i++) {
		Edge* pnt2 = pnt->GetHeadOfEdge();
		floyd[i][i] = 0;
		while (pnt2) {
			floyd[i][pnt2->GetKey()] = pnt2->GetWeight();
			pnt2 = pnt2->GetNext();
		}
		pnt = pnt->GetNext();
	}

	for (int k = 0; k < Size(); k++) {
		for (int i = 0; i < Size(); i++) {
			for (int j = 0; j < Size(); j++) {
				if (floyd[i][j] > floyd[i][k] + floyd[k][j])
					floyd[i][j] = floyd[i][k] + floyd[k][j];
			}
		}
	}
	//find Negative Cycle
	for (int k = 0; k < Size(); k++) {
		for (int i = 0; i < Size(); i++) {
			for (int j = 0; j < Size(); j++) {
				if (floyd[i][j] > floyd[i][k] + floyd[k][j]) { //find Negative Cycle
					floyd[0][0] = IN_FINITY; //insert infinity
					return floyd;
				}
			}
		}
	}
	return floyd;
}
