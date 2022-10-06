#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
#define IN_FINITY 999999
#define visited true
#define unvisited false

class Graph
{
private:
    // the head pointer for the linked list of the vertics
    Vertex* m_pVHead;
    // the number of the vertics
    int m_vSize;

public:
	/// constructor
	Graph();
	/// destructor
	~Graph();


    /// add vertex with vertexNum at the end of the linked list for the vertics
    void AddVertex(int vertexKey);

    /// add edge from the vertex which the number is cmdVertexKey to the vertex which the number is endVertexKey
    void AddEdge(int cmdVertexKey, int endVertexKey, int weight);

    /// get the vertex which the key is vertexNum
    Vertex* FindVertex(int key);

    /// get the number of the vertics
    int Size() const;

    /// memory free for the vertics
    void Clear();

    /// print out the graph as matrix form
    void Print(std::ofstream& fout);

    /// check whether the graph has negative edge or not.
    bool IsNegativeEdge();


    /// find the shortest P from cmdVertexKey to endVertexKey with Dijkstra using std::set
    std::vector<int> FindShortestPathDijkstraUsingSet(int cmdVertexKey, int endVertexKey);

    /// find the shortest P from cmdVertexKey to endVertexKey with Dijkstra using MinHeap
    std::vector<int> FindShortestPathDijkstraUsingMinHeap(int cmdVertexKey, int endVertexKey);

    /// find the shortest P from cmdVertexKey to endVertexKey with Bellman-Ford
    std::vector<int> FindShortestPathBellmanFord(int cmdVertexKey, int endVertexKey);
    
    std::vector<vector<int> > FindShortestPathFloyd();
};

#endif

