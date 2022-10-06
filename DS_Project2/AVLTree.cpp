#include "AVLTree.h"

AVLTree::AVLTree(ofstream* flog)
{
	root = NULL;
	nodesize = 0;
}

AVLTree::~AVLTree()
{
}

AVLNode * AVLTree::Getroot()
{
	return NULL;
}

void AVLTree::Setroot(AVLNode * node)
{
}

bool AVLTree::Insert(CityData * node)
{
	AVLNode* pNew = new AVLNode;
	pNew->SetCityData(node);
	char* pName = node->Getname();
	
	if (root == NULL) { //empty tree
		root = pNew;
		nodesize++;
		return true;
	}
	//phase 1 : locate insertion point
	nodesize++;
	AVLNode * a = root, //most recent node with bf = +-1
			* pa = NULL, //parent of a
			* p = root, //p moves throuht the tree
			* pp = NULL, //parent of p
			* rootSub = NULL;

	while (p != NULL) { //root is exist
		if (p->GetmBF() != 0) {
			a = p; pa = pp; 
		}
		if(strcmp(pName,p->GetCityData()->Getname())<0){ //pName < p->name, go left
			pp = p; p = p->GetLeft();
		}
		else if (strcmp(pName, p->GetCityData()->Getname()) > 0) { //go right
			pp = p; p = p->GetRight();
		}
	}
	//start insert
	AVLNode* y = new AVLNode;
	y = pNew;
	//assignming memory to y and connecting with parents
	if (strcmp(pName, pp->GetCityData()->Getname()) < 0)
		pp->SetLeft(y);
	else
		pp->SetRight(y);

	int d; //rotation
	AVLNode * b, //child of a
			* c; //child of b;
	//set the direction that is not balanced
	if (strcmp(pName, a->GetCityData()->Getname()) > 0) {
		b = p = a->GetRight(); d = -1;
	}
	else {
		b = p = a->GetLeft(); d = 1;
	}
	//set balance factor between inserted node and a
	while (strcmp(p->GetCityData()->Getname(), y->GetCityData()->Getname()) != 0) {
		//height of right increases by 1
		if (strcmp(pName, p->GetCityData()->Getname()) > 0) {
			p->SetmBF(-1); p = p->GetRight();
		}
		else if (strcmp(pName, p->GetCityData()->Getname()) < 0) {
			p->SetmBF(1); p = p->GetLeft();
		}
	}
	//should balance by modified?
	if (a->GetmBF() == 0 || a->GetmBF() + d == 0) { //tree still balanced
		a->SetmBF(a->GetmBF() + d);
		return true;
	}
	if (d == 1) { //left imbalance
		if (b->GetmBF() == 1) { //LL
			a->SetLeft(b->GetRight());
			b->SetRight(a);
			a->SetmBF(0);
			b->SetmBF(0);
			rootSub = b;
		}
		else { //LR
			c = b->GetRight();
			b->SetRight(c->GetLeft());
			a->SetLeft(c->GetRight());
			c->SetLeft(b);
			c->SetRight(a);
			switch (c->GetmBF()) {
			case 0:
				b->SetmBF(0); a->SetmBF(0);
				break;
			case 1:
				a->SetmBF(-1); b->SetmBF(0);
				break;
			case 2:
				b->SetmBF(1); a->SetmBF(0);
				break;
			}
			c->SetmBF(0); rootSub = c; //c is the new root of the subtree
		} //end of LR
	} //end of left imbalance
	else { //right imbalance
		if (b->GetmBF() == -1) { //RR
			a->SetRight(b->GetLeft());
			b->SetLeft(a);
			a->SetmBF(0);
			b->SetmBF(0);
			rootSub = b;
		}
		else { //RL
			c = b->GetLeft();
			b->SetLeft(c->GetRight());
			a->SetRight(c->GetLeft());
			c->SetRight(b);
			c->SetLeft(a);
			switch (c->GetmBF()) {
			case 0:
				b->SetmBF(0); a->SetmBF(0);
				break;
			case 1:
				b->SetmBF(-1); a->SetmBF(0);
				break;
			case 2:
				a->SetmBF(1); b->SetmBF(0);
				break;
			}
			c->SetmBF(0); rootSub = c; //c is the new root of the subtree
		} //end of RL
	} //end of right imbalance
	//subtree with root b has been rebalanced
	if (pa == NULL)root = rootSub;
	else if (a == pa->GetLeft())pa->SetLeft(rootSub);
	else pa->SetRight(rootSub);
	return true;
} //end of insert

CityData * AVLTree::Delete(int num)
{
	AVLNode *p = root,
			*pp = NULL, //pp is p's parent
			*a = root, //Balance variable a
			*pa = NULL, //pa is parent of a
			*rootSub = NULL; //subtree bariable
	stack<AVLNode*> s;
	/////////////////////////Search part////////////////////////
	if (root == NULL) //if root empty
		return NULL;
	while (1) {
		while (p != NULL) { //root exist
			if (p->GetmBF() != 0) { a = p; pa = pp; }
			s.push(p); //insert
			p = p->GetLeft();
		}
		if (!s.empty()) { //stack not empty
			p = s.top(); //receive node
			s.pop(); //remove stack
			if (num == p->GetCityData()->GetLocationId()) { //if input data is in tree
				break;
			}
			p = p->GetRight();
		}
		else //data doesn't exist
			return NULL;
	}
	int d; //rotation
	AVLNode* b, * c;
	///////////////delete part/////////////////
	if (p == NULL) //tree doesn't exist
		return NULL;
	//if p is leafnode
	if (p->GetLeft() == NULL && p->GetRight() == NULL) {
		if (pp->GetLeft() == p)
			pp->SetLeft(NULL);
		else
			pp->SetRight(NULL);
		delete p; //return
	}
	//if p has only one child
	else if (p->GetLeft() == NULL || p->GetRight() == NULL) {
		AVLNode* child;
		child = (p->GetLeft() != NULL) ? p->GetLeft() : p->GetRight();
		//true:left child,false:right child
		if (pp) {
			if (pp->GetLeft() == p) //left child is p
				pp->SetLeft(child); //delete p
			else
				pp->SetRight(child);
		}
		else //q is null
			root = child;
	}
	//p has both child
	else {
		AVLNode* prevprev = p, * prev = p->GetLeft(), * curr = p->GetLeft()->GetRight();
		while (curr) { //find biggest node
			prevprev = prev;
			prev = curr;
			curr = curr->GetRight();
		}
		p->SetCityData(prev->GetCityData()); //node value change
		if (prevprev == p) //parent go the child node
			prevprev->SetLeft(prev->GetLeft()); //delete
		else //not move
			prevprev->SetRight(prev->GetLeft());
		delete prev; //return
	}









	nodesize--;

	return 0;
}

CityData * AVLTree::Search(int num) //search inorder
{
	AVLNode* pCur = root;
	CityData* pCd = pCur->GetCityData();
	stack<AVLNode*> s;
	if (root == NULL) //if root empty
		return NULL;
	ofstream fout("log.txt", ios::app); //file open
	while (1) {
		while (pCur != NULL) { //root exist
			s.push(pCur); //insert
			pCur = pCur->GetLeft();
		}
		if (!s.empty()) { //stack not empty
			pCur = s.top(); //receive node
			s.pop(); //remove stack
			if (num == pCur->GetCityData()->GetLocationId()) { //if input data is in tree
				printCitydata(pCur->GetCityData()); //print
				fout << endl;
				break;
			}
			pCur = pCur->GetRight();
		}
		else //data doesn't exist
			return NULL;
	}
	fout.close(); //close file
	return pCd;
}

bool AVLTree::Print() //inorder
{
	AVLNode* p1 = root;
	stack<AVLNode*> k;
	if (root == NULL) //if root empty
		return false;
	ofstream fout("log.txt", ios::app); //file open
	while (1) { //loop
		while (p1 != NULL) { //root exist
			k.push(p1); //insert
			p1 = p1->GetLeft(); //move left nodes
		}
		if (!k.empty()) { //stack not empty
			p1 = k.top(); //receive node
			k.pop(); //remove stack
			printCitydata(p1->GetCityData());
			p1 = p1->GetRight(); //move right node
		}
		else
			break;
	}
	fout << endl;
	fout.close();
	return true;
}

void AVLTree::printCitydata(CityData* node) //print citydata
{
	ofstream fx("log.txt", ios::app);
	fx << "( " << node->GetLocationId() << ", " << node->Getname() << ", " << node->Getcountry() << " )" <<endl;
	fx.close();
}


