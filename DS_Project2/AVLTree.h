#include "AVLNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class AVLTree
{
public:
	AVLNode * root;	// AVLTree Root
	ofstream * flog;
	int nodesize;

public:
	AVLTree(ofstream * flog);
	~AVLTree();

	AVLNode  *  Getroot();
	void	 	Setroot(AVLNode * node);
	bool		Insert(CityData * node);
	CityData *	Delete(int num); //Delete in avltree
	CityData *	Search(int num); //Search in avltree
	bool		Print(); //Print avltree
	void printCitydata(CityData* node);
};

