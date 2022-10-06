#include <iostream>
#include "TransferWindowManager.h"

using namespace std;

/*int main(int argc, char** argv)
{
	TransferWindowManager transfer_window_manager(argv[1], atoi(argv[2]));*/
int main () {
	TransferWindowManager transfer_window_manager("ShootForLog.txt", 3500);
	cout << transfer_window_manager << endl;
	TransferWindowManager::SoccerTeam team = transfer_window_manager.getBestTeam();
	cout << "Best Players" << endl;
	cout << team << endl; //load best team
	cout << "-----" << endl;
	cout << "The Transfer window close" << endl;
	cout << transfer_window_manager << endl; //delete best team member and print BST inorder
    return 0;
}

