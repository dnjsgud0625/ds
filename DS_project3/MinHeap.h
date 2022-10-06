#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>
#include <climits>
using namespace std;

template<typename TKey, typename TValue>
class MinHeap
{
private:
	std::vector<std::pair<TKey, TValue>> m_vec;

public:
	MinHeap() {
		m_vec.push_back(make_pair(INT_MAX, INT_MAX));
	}

	~MinHeap()
	{
		m_vec.clear();
	}

	void Push(TKey key, TValue value) {
		if (IsEmpty()) {
			m_vec.push_back(make_pair(key, value)); //insert	
			return;
		}

		int flag = 0;
		for (int i = 1; i < m_vec.size(); i++) {
			if (m_vec[i].second == value)	flag = 1;
		}
		if (flag == 1)	DecKey(value, key);
		else {
			m_vec.push_back(make_pair(key, value));
			Heapify(1);
		}

	}

	void Pop() {
		if (IsEmpty()) return; //heap not exist

		m_vec[1].first = 0;
		m_vec[1].second = 0;
		Heapify(-1);
	}
	
	std::pair<TKey, TValue> Top() {
		if (m_vec.size() != 1)
			return m_vec[1];
	}
	
	std::pair<TKey, TValue> Get(TValue target) {
		for (int i = 1; i <= m_vec.size(); i++) {
			if (m_vec[i].second == target)
				return m_vec[i];
		}
	}
	
	bool IsEmpty() {
		if (m_vec.size() == 1)
			return true;
		return false;
	}
	
	void DecKey(TValue target, TKey newKey) {
		pair<TKey, TValue> dk = Get(target);
		dk.first = newKey;

		int idx = 1;

		for (; idx < m_vec.size(); idx++) {
			if (m_vec[idx].second == dk.second)
				break;
		}

		int pp = idx;
		while (pp != 1 && m_vec[pp / 2].first > dk.first) { //while pp not root, e is more than parent node
			m_vec[pp] = m_vec[pp / 2];
			pp /= 2; //move to parent
		}
		m_vec[pp].first = dk.first;
		m_vec[pp].second = dk.second;
	}

private:
	void Heapify(int index) {
		if (index == 1)	{ //push
			pair<TKey, TValue> sa = m_vec.back();

			int pp = m_vec.size() - 1;
			while (pp != 1 && m_vec[pp / 2].first > m_vec.back().first) { //while pp not root, e is more than parent node
				m_vec[pp].first = m_vec[pp / 2].first;
				m_vec[pp].second = m_vec[pp / 2].second;
				pp /= 2; //move to parent
			}
			m_vec[pp].first = sa.first;
			m_vec[pp].second = sa.second;
			return;
		}
		else if (index == -1) {	//pop
			if (m_vec.size() == 2) {
				m_vec.pop_back();
				return;
			}
			int pp = 1, p = 2;
			pair<TKey, TValue> la = m_vec.back();
			m_vec.pop_back();
			while (p <= m_vec.size() - 1) { //search
				if (p < m_vec.size() - 1 && m_vec[p].first > m_vec[p + 1].first) //select
					p++;
				if (la.first <= m_vec[p].first)
					break;
				m_vec[pp].first = m_vec[p].first;
				m_vec[pp].second = m_vec[p].second;
				pp = p; p *= 2;
			}
			m_vec[pp].first = la.first;
			m_vec[pp].second = la.second;
			return;
		}
	}
};

#endif

/Users/lee/Desktop/DS/2015722055_DS_project3/MinHeap.h
