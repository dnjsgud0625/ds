#include "Edge.h"

Edge::Edge() { //Edge
	m_key = 0;
	m_weight = 0;
	m_pNext = NULL;
}

Edge::Edge(int key, int weight) { //Edge initialize
	m_key = key;
	m_weight = weight;
	m_pNext = NULL;
}

void Edge::SetNext(Edge* pNext) { //SetNext
	m_pNext = pNext;
}

int Edge::GetKey() const { //Getkey
	return m_key;
}

int Edge::GetWeight() const	{ //GetWeight
	return m_weight;
}

Edge* Edge::GetNext() const	{ //GetNext
	return m_pNext;
}

