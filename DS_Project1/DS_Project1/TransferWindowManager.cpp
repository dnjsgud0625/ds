#include "TransferWindowManager.h"
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int cnt = 0;
string p_name[200];
string p_pos[200];
int p_fee[200] = { 0, };
int p_abl[200] = { 0, };

TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(std::string file_dir, int budget)
{
	m_budget = budget;

	ifstream in("ShootForLog.txt"); //load ShootForLog
	string line = "";
	char *l_buf = new char[100]; //memory allocate
	while (std::getline(in, line)) //read line by line
	{	
			char *l_buf = new char[100]; //memory allocate
			strcpy(l_buf, line.c_str()); //copy in to l_buf

			char* name = strtok(l_buf, ","); //cut to ',' 
			p_name[cnt] = string(name); //save player's name

			char* pos = strtok(NULL, ", "); //cut
			p_pos[cnt] = string(pos); //position
			
			char* fee = strtok(NULL, ", "); //cut
			p_fee[cnt] = atoi(fee); //fee

			char* abl = strtok(NULL, ", "); //cut
			p_abl[cnt] = atoi(abl); //ability

			SoccerPlayerData player = SoccerPlayerData(name,pos,atoi(fee),atoi(abl)); //make player's date
			//Insert playerData into BST by position
			if (strcmp(pos, "Forward") == 0)
				fwBST.insert(player);
			else if (strcmp(pos, "Midfielder") == 0)
				mfBST.insert(player);
			else if (strcmp(pos, "Defender") == 0)
				dfBST.insert(player);
			else if (strcmp(pos, "Goalkeeper") == 0) 
				gkBST.insert(player);
		cnt++;
	}
	delete[] l_buf; //delete memory allacation
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager)
{
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam() //make best team
{
	SoccerTeam best_team;
	SoccerPlayerData bfw;
	SoccerPlayerData bmf;
	SoccerPlayerData bdf;
	SoccerPlayerData bgk;

	int Total_fee = 0;
	int Total_able = 0;
	int F;	int A;	int cf;	int cm;	int cd;	int cg;
	vector <string> fw_n;	vector <int> fw_a;	vector <int> fw_f;	vector<int> c_fw;	vector<int> c2_fw;
	vector <string> mf_n;	vector <int> mf_a;	vector <int> mf_f;	vector<int> c_mf;	vector<int> c2_mf;
	vector <string> df_n;	vector <int> df_a;	vector <int> df_f;	vector<int> c_df;	vector<int> c2_df;
	vector <string> gk_n;	vector <int> gk_a;	vector <int> gk_f;	vector<int> c_gk;	vector<int> c2_gk;
	vector <int> total_f;	vector <int> ub_f; 
	vector <int> total_a;	vector <int> ub_a;
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//*best team means the most powerful team that is defined in the project introduction file. 

	for (int i = 0; i < cnt; i++) { //clssification into position
		if (p_pos[i] == "Forward") {
			fw_n.push_back(p_name[i]);
			fw_f.push_back(p_fee[i]);
			fw_a.push_back(p_abl[i]);
		}
		else if (p_pos[i] == "Midfielder") {
			mf_n.push_back(p_name[i]);
			mf_f.push_back(p_fee[i]);
			mf_a.push_back(p_abl[i]);
		}
		else if (p_pos[i] == "Defender") {
			df_n.push_back(p_name[i]);
			df_f.push_back(p_fee[i]);
			df_a.push_back(p_abl[i]);
		}
		else if (p_pos[i] == "Goalkeeper") {
			gk_n.push_back(p_name[i]);
			gk_f.push_back(p_fee[i]);
			gk_a.push_back(p_abl[i]);
		}
		else
			break;
	}
	//All soccerteam combination that can be created by playerdata
	for (int i = 0; i < fw_f.size(); i++) {
		for (int j = 0; j < mf_f.size(); j++) {
			for (int k = 0; k < df_f.size(); k++) {
				for (int l = 0; l < gk_f.size(); l++) {
					Total_fee = fw_f.at(i) + mf_f.at(j) + df_f.at(k) + gk_f.at(l); //total soccerteam's fee
					total_f.push_back(Total_fee); //save
					Total_able= fw_a.at(i) + mf_a.at(j) + df_a.at(k) + gk_a.at(l); //total soccerteam's ability
					total_a.push_back(Total_able);
					c_fw.push_back(i); //find team's composition
					c_mf.push_back(j);
					c_df.push_back(k);
					c_gk.push_back(l);
				}
			}
		}
	}
	
	for (int i = 0; i < total_f.size(); i++) { //filter under budget
		if (total_f[i] < m_budget || total_f[i] == m_budget){
			ub_f.push_back(total_f[i]);
			ub_a.push_back(total_a[i]);
			c2_fw.push_back(c_fw[i]);
			c2_mf.push_back(c_mf[i]);
			c2_df.push_back(c_df[i]);
			c2_gk.push_back(c_gk[i]);
		}
	}
	F = ub_f.at(0);
	A = ub_a.at(0);
	cf = c2_fw.at(0);
	cm = c2_mf.at(0);
	cd = c2_df.at(0);
	cg = c2_gk.at(0);

	for (int j = 1; j < ub_f.size(); j++) {

		if (A > ub_a[j]) //if abitity is smaller
			continue; //keep go
		else if (A < ub_a[j]) { //bigger
			F = ub_f[j]; //change
			A = ub_a[j];
			cf = c2_fw[j];
			cm = c2_mf[j];
			cd = c2_df[j];
			cg = c2_gk[j];
		}
		else { //ability is same
			if (F < ub_f[j] || F == ub_f[j]) //if fee is bigger or same 
				continue; //continue
			else { //if fee is smaller
				F = ub_f[j];
				A = ub_a[j];
				cf = c2_fw[j];
				cm = c2_mf[j];
				cd = c2_df[j];
				cg = c2_gk[j];
			}
		}
	}
	//make best team player's soccerplayerdata
	bfw.m_name = fw_n[cf];
	bfw.m_position = "Forward";
	bfw.m_ability = fw_a[cf];
	bfw.m_transfer_fee = fw_f[cf];

	bmf.m_name = mf_n[cm];
	bmf.m_position = "Midfielder";
	bmf.m_ability = mf_a[cm];
	bmf.m_transfer_fee = mf_f[cm];

	bdf.m_name = df_n[cd];
	bdf.m_position = "Defender";
	bdf.m_ability = df_a[cd];
	bdf.m_transfer_fee = df_f[cd];

	bgk.m_name = gk_n[cg];
	bgk.m_position = "Goalkeeper";
	bgk.m_ability = gk_a[cg];
	bgk.m_transfer_fee = gk_f[cg];

	best_team = { bfw, bmf, bdf, bgk }; //make best team
	
	fwBST.deletion(best_team.fw.m_ability); //delete best team player
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;
}
