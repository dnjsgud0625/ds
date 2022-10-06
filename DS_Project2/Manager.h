#include "Graph.h"
#include<utility>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Manager
{
public:
	AVLTree * avl;
	Graph * gp;

	char * cmd;
	int iter;

public:
	Manager();
	~Manager();

	ofstream flog;
	ifstream fin;

	void run(const char * command);
	bool LOAD();
	bool INSERT(CityData* node);
	bool PRINT_AVL();
	bool SEARCH_AVL(int num);
	bool DELETE_AVL(int num);
	bool BUILD_GP();
	bool PRINT_GP();
	bool BUILD_MST();
	bool PRINT_MST();
	void EXIT();

	void printErrorCode(int n, const char * cmdname);
	void printErrorCode2(int n, const char* cmdname, int m);
	void printSuccessCode(const char * cmdname);
	void printSucesssCode2(const char* cmdname, int n);

};
