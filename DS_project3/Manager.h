#define _CRT_SEpntE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Graph.h"
#include "Result.h"
#include <fstream>
using namespace std;

class Manager
{
private:
	// the filePath for the result log
	const char* RESULT_LOG_P = "log.txt";
	// the filePath for the error log
    

	// the file stream for the result log
	std::ofstream fout;
	// the file stream for the error log
    
	// graph instance to manage the vertics.
	Graph m_graph;

public:
	~Manager();
	void Run(const char* filePathath);
	void PrintError(Result result);

private:
	Result Load(const char* filePathath);
	Result Print();
	Result FindShortestPathDijkstraUsingSet(int cmdVertexKey, int endVertexKey);
	Result FindShortestPathDijkstraUsingMinHeap(int cmdVertexKey, int endVertexKey);
	Result FindShortestPathBellmanFord(int cmdVertexKey, int endVertexKey);
	Result FindShortestPathFloyd();
	void Insertion_Sort(vector<int>& v, const int left, const int right);
	void Insert(int& e, vector<int>& v, int i, const int left);
	void Quick_Sort(vector<int>& v, const int left, const int right);
};

#endif
