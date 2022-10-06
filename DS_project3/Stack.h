#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;

		StackNode(T data) : Data(data), pNext(NULL) {}
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;

public:
	Stack() {
		m_pTop = NULL;
	}

	~Stack() {
		while (m_pTop)
			Pop();
	}

	/// <summary>
	/// push the data into this stack
	/// </summary>
	///
	/// <param name="data">
	/// a data to push into this stack
	/// </param>
	void Push(T data) {
		if (!m_pTop) {
			StackNode* _new = new StackNode(data);
			m_pTop = _new;
		}
		else {
			StackNode* _new = new StackNode(data);
			_new->pNext = m_pTop;
			m_pTop = _new;
		}
	}
	/// <summary>
	/// pop(remove) the last-in data from this stack
	/// </summary>
	void Pop() {
		StackNode* cur = m_pTop;
		if (!m_pTop)
			return;
		m_pTop = cur->pNext;
		delete cur;

	}
	/// <summary>
	/// get the last-in data of this stack
	/// </summary>
	/// 
	/// <returns>
	/// the last-in data of this stack
	/// </returns>
	T Top() {
		return m_pTop->Data;
	}
	/// <summary>
	/// check whether this stack is empty or not.
	/// </summary>
	///
	/// <returns>
	/// true if this stack is empty.
	/// false otherwise.
	/// </returns>
	bool IsEmpty() {
		if (!m_pTop)
			return true;
		return false;

	}
};

#endif

