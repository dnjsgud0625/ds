#pragma warning (disable:4996)
#include "Manager.h"
#include <cstring>
#include <iostream>
using namespace std;

Manager::~Manager()
{
	if (fout.is_open())
		fout.close();
}

void Manager::Run(const char* filePath)
{
	fout.open(RESULT_LOG_P);

	ifstream fin;
	fin.open(filePath); //load

	if (!fin) {	//file open error
		fout << "====== SYSTEM ======" << endl;
		fout << "CommandFileNotExist" << endl;
		fout << "=====================" << endl << endl << endl;
		PrintError(CommandFileNotExist);
		fout.close();
		return;
	}

	char cmd[64] = { 0 };
	char* token = NULL;

	while (!fin.eof()) {
		fin.getline(cmd, 64);
		if (strlen(cmd) == 0) break;
		token = strtok(cmd, " ");

		if (!strcmp(token, "LOAD")) { //LOAD
			token = strtok(NULL, " ");
			if (!token) { //NULL
				fout << "====== LOAD ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist); //print error
				continue;
			}
			PrintError(Load(token));
		}
		else if (!strcmp(token, "PRINT")) {	//PRINT
			token = strtok(NULL, " ");
			if (token) {
				fout << "====== PRINT ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist); //print error
				continue;
			}
			PrintError(Print());
		}
		else if (!strcmp(token, "DIJKSTRA")) {	//DIJKSTRA
			int cmd = 0;
			int end = 0;
			token = strtok(NULL, " ");
			if (!token) {
				fout << "===== DIJKSTRA =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			cmd = atoi(token);
			token = strtok(NULL, " ");
			if (!token) {
				fout << "===== DIJKSTRA =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	// print error
				continue;
			}
			end = atoi(token);
			token = strtok(NULL, " ");
			if (token) {
				fout << "===== DIJKSTRA =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			PrintError(FindShortestPathDijkstraUsingSet(cmd, end));
		}
		else if (!strcmp(token, "DIJKSTRAMIN"))	//DIJKSTRAMIN
		{
			int cmd = 0;
			int end = 0;
			token = strtok(NULL, " ");
			if (!token) {
				fout << "====== DIJKSTRAMIN ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			cmd = atoi(token);
			token = strtok(NULL, " ");
			if (!token) {
				fout << "====== DIJKSTRAMIN ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			end = atoi(token);
			token = strtok(NULL, " ");
			if (token) {
				fout << "====== DIJKSTRAMIN ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	// Error
				continue;
			}
			PrintError(FindShortestPathDijkstraUsingMinHeap(cmd, end));
		}
		else if (!strcmp(token, "BELLMANFORD")) { //BELLMANFORD
			int cmd = 0;
			int end = 0;
			token = strtok(NULL, " ");
			if (!token) {
				fout << "===== BELLMANFORD =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			cmd = atoi(token);
			token = strtok(NULL, " ");
			if (!token) {
				fout << "===== BELLMANFORD =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			end = atoi(token);
			token = strtok(NULL, " ");
			if (token) {
				fout << "===== BELLMANFORD =====" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			PrintError(FindShortestPathBellmanFord(cmd, end));
		}
		else if (!strcmp(token, "FLOYD")) {	//FLOYD
			token = strtok(NULL, " ");
			if (token) {
				fout << "====== FLOYD ======" << endl;
				fout << "VertexKeyNotExist" << endl;
				fout << "=================" << endl << endl << endl;
				PrintError(VertexKeyNotExist);	//print error
				continue;
			}
			PrintError(FindShortestPathFloyd());
		}
		else { //command not exist
			fout << "====== " << token << " ======" << endl;
			fout << "NonDefinedCommand" << endl;
			fout << "=================" << endl << endl << endl;
			PrintError(NonDefinedCommand);	//print error
		}
	}
	fin.close(); //file close
}
void Manager::PrintError(Result result)	{ //Print Error function
	fout << "=================" << endl;
	fout << "Error code: " << result << std::endl;
	fout << "=================" << endl << endl << endl;
}

Result Manager::Load(const char* filePath)	//Load
{
	ifstream fin;
	fin.open(filePath);

	if (!fin) {	//file not exist
		fout << "====== LOAD ======" << endl;
		fout << "LoadFileNotExist" << endl;
		fout << "====================" << endl << endl << endl;
		return LoadFileNotExist;
	}
	char* token = NULL;
	char data[200] = { 0 };
	int weight = 0;

	fin.getline(data, 100);
	int Dsize = atoi(strtok(data, " "));
	// Load mapdata.txt
	for (int i = 0; i < Dsize; i++) {
		m_graph.AddVertex(i);	//Add vertex
		fin.getline(data, 100);
		weight = atoi(strtok(data, " "));	//weight
		for (int j = 0; j < Dsize; j++) {
			if (weight != 0)	m_graph.AddEdge(i, j, weight);	//Add edge
			if (j != Dsize - 1)
				weight = atoi(strtok(NULL, " "));
		}
	}
	fout << "====== LOAD ======" << endl;
	fout << "Success           " << endl;
	fout << "===================" << endl << endl << endl;
	return Success;
}

Result Manager::Print() { //Print function
	fout << "====== PRINT ======" << endl;
	if (!m_graph.Size()) { //GraphNotExist Error
		fout << "GraphNotExist" << endl;
		fout << "===================" << endl << endl << endl;
		return GraphNotExist;
	}
	m_graph.Print(fout);
	return Success;
}

Result Manager::FindShortestPathDijkstraUsingSet(int cmdVertexKey, int endVertexKey) //Find Dijkstra using set
{
	int size = 0;
	if (!m_graph.Size()) { //GraphNotExist Error
		fout << "===== DIJKSTRA =====" << endl;
		fout << "GraphNotExist" << endl;
		fout << "======================" << endl << endl << endl;
		return GraphNotExist;
	}
	if (!m_graph.FindVertex(cmdVertexKey) || !m_graph.FindVertex(endVertexKey)) { //InvalidVertexKey Error
		fout << "===== DIJKSTRA =====" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "======================" << endl << endl << endl;
		return InvalidVertexKey;
	}
	if (m_graph.IsNegativeEdge()) {	//InvalidAlgorithm Error
		fout << "===== DIJKSTRA =====" << endl;
		fout << "InvalidAlgorithm" << endl;
		fout << "======================" << endl << endl << endl;
		return InvalidAlgorithm;
	}
	fout << "===== DIJKSTRA =====" << endl;

	vector<int> Dijk = m_graph.FindShortestPathDijkstraUsingSet(cmdVertexKey, endVertexKey);

	fout << "shortest P: ";
	for (int i = Dijk.size() - 2; i >= 0; i--)
		fout << Dijk[i] << " ";
	fout << endl;
	size = Dijk.size();
	Quick_Sort(Dijk, 0, size - 2); //quick_sort
	fout << "sorted nodes: ";
	for (int i = 0; i < Dijk.size() - 1; i++) //sort
		fout << Dijk[i] << " ";
	fout << endl << "P length: " << Dijk[Dijk.size() - 1];
	fout << endl << "======================" << endl << endl << endl;

	Dijk.clear();
	return Success;
}

Result Manager::FindShortestPathDijkstraUsingMinHeap(int cmdVertexKey, int endVertexKey) {	// Find Dijkstra minheap
	int S = 0;

	if (!m_graph.Size()) { // GraphNotExist Error
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=========================" << endl << endl << endl;
		return GraphNotExist;
	}
	if (!m_graph.FindVertex(cmdVertexKey) || !m_graph.FindVertex(endVertexKey)) { // InvalidVertexKey Error
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "======================" << endl << endl << endl;
		return InvalidVertexKey;
	}
	if (m_graph.IsNegativeEdge()) {	// InvalidAlgorithm Error
		fout << "====== DIJKSTRAMIN ======" << endl;
		fout << "InvalidAlgorithm" << endl;
		fout << "======================" << endl << endl << endl;
		return InvalidAlgorithm;
	}
	fout << "====== DIJKSTRAMIN ======" << endl;
	vector<int> Dijkmin = m_graph.FindShortestPathDijkstraUsingMinHeap(cmdVertexKey, endVertexKey);

	fout << "shortest P: ";
	for (int i = Dijkmin.size() - 2; i >= 0; i--)
		fout << Dijkmin[i] << " ";
	fout << endl;
	S = Dijkmin.size();
	Quick_Sort(Dijkmin, 0, S - 2); //quick_sort
	fout << "sorted nodes: ";
	for (int i = 0; i < Dijkmin.size() - 1; i++) //sorted P
		fout << Dijkmin[i] << " ";
	fout << endl << "P length: " << Dijkmin[Dijkmin.size() - 1]; //P length
	fout << endl << "======================" << endl << endl << endl;

	Dijkmin.clear();
	return Success;
}

Result Manager::FindShortestPathBellmanFord(int cmdVertexKey, int endVertexKey) { // FInd bellmanform
	int size = 0;
	if (!m_graph.Size()) { //GraphNotExist Error
		fout << "===== BELLMANFORD =====" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=================" << endl << endl << endl;
		return GraphNotExist; //return
	}
	if (!m_graph.FindVertex(cmdVertexKey) || !m_graph.FindVertex(endVertexKey))	{ //InvalidVertexKey Error
		fout << "===== BELLMANFORD =====" << endl;
		fout << "InvalidVertexKey" << endl;
		fout << "=================" << endl << endl << endl;
		return InvalidVertexKey; //return
	}

	vector<int> bmf = m_graph.FindShortestPathBellmanFord(cmdVertexKey, endVertexKey);
	if (bmf.size() == 0) { //NegativeCycleDetected Error
		fout << "===== BELLMANFORD =====" << endl;
		fout << "NegativeCycleDetected" << endl;
		fout << "=================" << endl << endl << endl;
		return NegativeCycleDetected;
	}
	fout << "===== BELLMANFORD =====" << endl;

	//shortest P
	fout << "shortest P: ";
	for (int i = bmf.size() - 2; i >= 0; i--)
		fout << bmf[i] << " ";
	fout << endl;
	size = bmf.size();
	Quick_Sort(bmf, 0, size - 2); //qucik_sort
	fout << "sorted nodes: ";
	for (int i = 0; i < bmf.size() - 1; i++) //sorted P
		fout << bmf[i] << " ";
	fout << endl << "P length: " << bmf[bmf.size() - 1]; // P length
	fout << endl << "=================" << endl << endl << endl;

	bmf.clear();
	return Success;
}

Result Manager::FindShortestPathFloyd() { // floyd
	int size = 0;
	if (!m_graph.Size()) { //GraphNotExist Error
		fout << "====== FLOYD ======" << endl;
		fout << "GraphNotExist" << endl;
		fout << "=================" << endl << endl << endl;
		return GraphNotExist;
	}

	vector<vector<int>> floyd = m_graph.FindShortestPathFloyd(); //m_graph floyd function call

	if (floyd[0][0] == IN_FINITY) {	//NegativeCycleDetected Error
		fout << "====== FLOYD ======" << endl;
		fout << "NegativeCycleDetected" << endl;
		fout << "=================" << endl << endl << endl;
		return NegativeCycleDetected;
	}
	fout << "====== FLOYD ======" << endl;
	for (int i = 0; i < m_graph.Size(); i++) { //print out Matrix 
		for (int j = 0; j < m_graph.Size(); j++) {
			fout << floyd[i][j] << " ";
		}
		fout << endl;
	}
	fout << "======================" << endl << endl << endl;

	floyd.clear(); //clear
	return Success;	//return
}

void Manager::Quick_Sort(vector<int>& Vec, const int left, const int right) { //Quick_Sort
	if (right - left + 1 <= 6)		//high-low+1 <= segment
		return Insertion_Sort(Vec, left, right);	//Insertion_Sort
	else if (left < right) {
		int i = left,
			j = right + 1,
			pi = Vec[left];
		do {
			do { //pi on the left
				i++;
				if (i >= j)	 //break
					break;
			} while (Vec[i] < pi);
			do { //pi on the right
				j--;
				if (j <= i)	 //break
					break;
			} while (Vec[j] > pi);
			if (i < j) swap(Vec[i], Vec[j]); //found
		} while (i <= j);

		swap(Vec[left], Vec[j]); //swap

		Quick_Sort(Vec, left, j - 1); //quicksort
		Quick_Sort(Vec, j + 1, right); //quicksort
	}
}

void Manager::Insertion_Sort(vector<int>& Vec, const int left, const int right) { //Insertion_Sort
	for (int j = (left + 1); j <= right; j++) {	 //left to right
		int tmp = Vec[j]; //save
		Insert(tmp, Vec, j - 1, left); //Insert
	}
}

void Manager::Insert(int& e, vector<int>& Vec, int i, const int left) {		//Insert
	while (e < Vec[i]) {
		Vec[i + 1] = Vec[i];	//shift the v to the right
		i--;
		if (i == left - 1) {	//reach the end
			Vec[left] = e;
			return;		//end
		}
	}
	Vec[i + 1] = e;
}
