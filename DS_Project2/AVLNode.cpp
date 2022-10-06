#include "AVLNode.h"

AVLNode::AVLNode()
{
	pCityData = NULL;
	pLeft = NULL;
	pRight = NULL;
	mBF = 0;
}

AVLNode::~AVLNode()
{
}

CityData * AVLNode::GetCityData()
{
	return this->pCityData;
}

AVLNode * AVLNode::GetLeft()
{
	return pLeft;
}

AVLNode * AVLNode::GetRight()
{
	return pRight;
}

int AVLNode::GetmBF()
{
	return mBF;
}

void AVLNode::SetCityData(CityData * node)
{
	pCityData = node;
}

void AVLNode::SetLeft(AVLNode * node)
{
	pLeft = node;
}

void AVLNode::SetRight(AVLNode * node)
{
	pRight = node;
}

void AVLNode::SetmBF(int n)
{
	mBF = n;
}
