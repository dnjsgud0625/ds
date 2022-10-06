#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

Manager::Manager()
{
	flog.open("log.txt", ios::app);
	flog.setf(ios::fixed);
	avl = new AVLTree(&flog);
	gp = new Graph(&flog);
	iter = 0;
	cmd = NULL;
}

Manager::~Manager()
{
	flog.close();
}

void Manager::run(const char * command)
{
	fin.open(command);
	cmd = new char[40];
	CityData* ins;
	int load = -1;

	if (!fin) {
		ofstream fout("log.txt", ios::app);
		 fout << "[ERROR] command file open error!" << endl;
		 fout.close();
	}
	while (!fin.eof())
	{
		iter = iter + 1;
		fin.getline(cmd, 40);
		char * one = strtok(cmd, " ");
		int a = 0;
		if (!strcmp(one, "LOAD")) { //LOAD
			one = strtok(NULL, " ");
			if (load == 1)
				printErrorCode(100, "LOAD");
			else if (one != NULL)
				printErrorCode(100, "LOAD");
			else if (LOAD()) {
				printSuccessCode("LOAD");
				a = 1;
			}
			else printErrorCode(100, "LOAD");
			load = 1;
		}
		else if (!strcmp(one, "INSERT")) { //INSERT
			ins = new CityData();
			char* one = strtok(NULL, " ");
			ins->SetLocationId(atoi(one));
			char* two = strtok(NULL, " ");
			ins->Setname(two);
			char* thr = strtok(NULL, " ");
			ins->Setcountry(thr);

			avl->Insert(ins);
			
			if (avl == NULL)
				printErrorCode(200, "INSERT");
			else {
				printSuccessCode("INSERT");
				ofstream fout("log.txt", ios::app);
				fout << "( " << one << ", " << two << ", " << thr << " )" << endl << endl;
				fout.close();
			}
 		}
		else if (!strcmp(one, "PRINT_AVL")) { //PRINT_AVL
			if (avl == NULL)
				printErrorCode(300, "PRINT_AVL");
			else {
				printSuccessCode("PRINT_AVL");
				PRINT_AVL();
			}
		}
		else if (!strcmp(one, "SEARCH_AVL")) { //SEARCH_AVL
			one = strtok(NULL, " ");
			if (one == NULL) printErrorCode2(500, "SEARCH_AVL", atoi(one)); //nothing entered
			else {
				printSucesssCode2("SEARCH_AVL", atoi(one)); //value entered
				if (SEARCH_AVL(atoi(one))) {} //value exist
				else { //not exist
					ofstream fout("log.txt", ios::app);
					fout << "Error code : 500" << endl << endl;
					fout.close();
				}
			}
		}
		else if (!strcmp(one, "DELETE_AVL")) { //DELETE_AVL
			one = strtok(NULL, " ");
			if (one == NULL) printErrorCode2(400, "DELETE_AVL", atoi(one)); //nothing entered
			else {
				printSucesssCode2("DELETE_AVL", atoi(one)); //value entered
				if (DELETE_AVL(atoi(one))) {
					ofstream fout("log.txt", ios::app);
					fout << "Success" << endl << endl;
					fout.close();
				} //value exist
				else { //not exist
					ofstream fout("log.txt", ios::app);
					fout << "Error code : 400" << endl << endl;
					fout.close();
				}
			}
		}
		else if (!strcmp(one, "BUILD_GP")) { //BUILD_GP
			if(avl==NULL)  printErrorCode(600, "BUILD_GP"); //nothing entered
			if (BUILD_GP()) printSuccessCode("BUILD_GP"); //if grape made
			else printErrorCode(600, "BUILD_GP");
		}
		else if (!strcmp(one, "PRINT_GP")) { //PRINT_GP
			if (avl == NULL || gp == NULL)printErrorCode(700, "PRINT_GP"); //nothing entered
			else {
				printSuccessCode("PRINT_GP"); //print grape
				PRINT_GP();
			}
		}
		else if (!strcmp(one, "BUILD_MST")) { //BUILD_MST
			if (avl == NULL || gp == NULL)printErrorCode(800, "BUILD_MST"); //nothing entered
			if (BUILD_MST()) printSuccessCode("BUILD_MST");
			else printErrorCode(800, "BUILD_MST");
		}
		else if (!strcmp(one, "PRINT_MST")) { //PRINT_MST
			if (avl == NULL || gp == NULL)printErrorCode(900, "BUILD_MST"); //nothing entered
			else {
				printSuccessCode("PRINT_MST"); //print mst
				PRINT_MST();
			}
		}		
		else if (!strcmp(one, "EXIT")) { //EXIT
			printSuccessCode("EXIT");
			EXIT();	
		}
		else {
			printErrorCode(0,"Unknown"); //unknown command entered
		}
	}
	fin.close(); //close
	return;
}

bool Manager::LOAD() //LOAD
{
	char* two = NULL;
	char buf[128] = { 0, };
	char buf2[128] = { 0, };

	ifstream fin;
	fin.open("city_list.txt"); //file open

	if (!fin) //file doesn't exist
		return false;

	while (fin.getline(buf, 128)) {
		CityData* node = NULL;
		strcpy(buf2, buf);

		two = strtok(buf, "\t"); //locationid
		two = strtok(NULL, "\t"); //city name
		two = strtok(NULL, " "); //country
		node = new CityData();

		two = strtok(buf2, "\t"); //locationid
		node->SetLocationId(atoi(two));
		two = strtok(NULL, "\t"); //city name
		node->Setname(two);
		two = strtok(NULL, " "); //country
		node->Setcountry(two);

		avl->Insert(node); //avl insert
	}
	return true;
}

bool Manager::INSERT(CityData* node)
{
	return true;
}

bool Manager::PRINT_AVL()
{
	if (!avl->Print()) return false;
	else return true;
}

bool Manager::SEARCH_AVL(int num)
{
	if (!avl->Search(num)) return false;
	else return true;
}

bool Manager::DELETE_AVL(int num)
{
	if (!avl->Delete(num)) return false;
	else return true;
}

bool Manager::BUILD_GP()
{
	return gp->Build(avl);
}

bool Manager::PRINT_GP()
{
	return gp->Print_GP();
	
}

bool Manager::BUILD_MST()
{
	return gp->Kruskal();
}

bool Manager::PRINT_MST()
{
	return gp->Print_MST();
}

void Manager::EXIT()
{
	exit(1);
}

void Manager::printErrorCode(int n, const char * cmdname) {//ERROR CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Error code: " << n << endl << endl;
}

void Manager::printErrorCode2(int n, const char* cmdname, int m) //ERROR CODE PRINT FUNCION2
{
	flog << "==> command " << iter << ") " << cmdname << " " << m << endl;
	flog << "Error code: " << n << endl << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	if (strcmp(cmdname, "LOAD") == 0 || strcmp(cmdname, "DELETE_AVL") == 0 || strcmp(cmdname, "BUILD_GP") == 0 || strcmp(cmdname, "BUILD_MST") == 0 || strcmp(cmdname, "EXIT") == 0)
		flog << "Success" << endl << endl;
}
void Manager::printSucesssCode2(const char* cmdname, int n) //SUCCESS CODE PRINT FUNCTION2
{
	flog << "==> command " << iter << ") " << cmdname << " " << n << endl;
}
