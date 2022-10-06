#include "Vertex.h"

Vertex::Vertex() {//Vertex
	m_key = 0;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::Vertex(int key)	{ //Vertex initialize
	m_key = key;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::~Vertex()	//Vertex destructor
{
}

void Vertex::SetNext(Vertex* pNext)	{ //Set Next
	m_pNext = pNext;
}

int Vertex::GetKey() const	{ //Get key
	return m_key;
}

Vertex* Vertex::GetNext() const {	//Get Next
	return m_pNext;
}

int Vertex::Size() const { //Get Size
	return m_size;
}

void Vertex::AddEdge(int edgeKey, int weight) { //Add Edge
	if (!m_pEHead) { //head isn't exist
		Edge* Egnew = new Edge(edgeKey, weight);
		m_pEHead = Egnew;
	}
	else {	// head exist
		Edge* Egnew = new Edge(edgeKey, weight);
		Edge* pnt = m_pEHead;
		while (pnt->GetNext())
			pnt = pnt->GetNext();
		pnt->SetNext(Egnew);
	}
	m_size++; // size ++
}

Edge* Vertex::GetHeadOfEdge() const {	//Get Head of edge
	return m_pEHead;
}

void Vertex::Clear()
{
}

