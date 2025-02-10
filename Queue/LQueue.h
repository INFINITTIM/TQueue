#pragma once

template<class T>
struct Node {
	T val;
	Node<T>* pNext;
};

template<class T>
class LQueue
{
	Node<T>* pHead;
	Node<T>* pTail;
public:
	LQueue();
	LQueue(const LQueue<T>& q);
	~LQueue();

	LQueue<T>& operator=(const LQueue<T>& q);
	bool operator==(const LQueue<T>& q) const;
	bool operator!=(const LQueue<T>& q) const;

	bool isEmpty() const;
	bool isFull() const;

	T pop();
	void push(T element);
	void clear();
	int size()  const;
	T back() const;
	T front() const;
};

template <class T>
LQueue<T>::LQueue()
{
	pHead = nullptr;
	pTail = nullptr;
}

template <class T>
LQueue<T>::LQueue(const LQueue<T>& q)
{
	Node<T>* stmp = q.pHead; // ��������� �� ������ ������� �������� ������� 
	Node<T>* stmp2 = q.pTail; // ��������� �� ��������� ������� �������� ������� 
	if (stmp != nullptr)
	{
		pHead = new Node<T>; // �������� ������ ��� ������ ������� ����� �������
		pHead->val = stmp->val; // ����������� �������� ������� �������� �������� �������
		pHead->pNext = nullptr; // ����������� ��������� �� ���� ��� ������� nullptr

		if (stmp == stmp2) // ���� ���� ������� � ������� ����� 
		{
			pTail = new Node<T>;
			pTail->val = stmp->val;
			pTail->pNext = nullptr;
		}
		else
		{
			stmp = stmp->pNext; // ������������ ��������� �� ������ ������� �������� �������

			Node<T>* gtmp = pHead; // ��������� �� ������ ������� ����� �������

			while (stmp != stmp2) // ���� ��������� �� ������� �������� ������� �� ����� ����� ��������� �� ��������� ������� �������� ������� 
			{
				Node<T>* newNode = new Node<T>; //������� ����� ������� ����� �������
				newNode->val = stmp->val; // �������� � ���� ��������
				newNode->pNext = nullptr; // ���������� ��� ����. ���. ������� ��� nullptr

				gtmp->pNext = newNode; // ����. ���. ������� ������ ��� ����� ����� (��������� �� ���� ��� ������� � ������� �������� ������ �� ���� newNode � ��)

				stmp = stmp->pNext; // ��������� �� ��������� ������� ������ �� �������� ��������
				gtmp = gtmp->pNext; // ��������� �� ��������� ������� ������ ������
			}
			pTail = new Node<T>;
			pTail->val = stmp->val;
			pTail->pNext = nullptr;

			gtmp->pNext = pTail;
		}
	}
	else
	{
		pHead = nullptr;
		pTail = nullptr;
	}
}

template <class T>
LQueue<T>::~LQueue()
{
	while (pHead != nullptr)
	{
		Node<T>* tmp = pHead;
		pHead = pHead->pNext;
		delete tmp;
	}
}

template <class T> 
LQueue<T>& LQueue<T>::operator=(const LQueue<T>& q)
{
	if (this == &q) return *this;
	while (pHead != nullptr) 
	{
		Node<T>* tmp = pHead;
		pHead = pHead->pNext;
		delete tmp;
	}
	Node<T>* stmp = q.pHead;
	Node<T>* stmp2 = q.pTail;
	if (stmp != nullptr)
	{
		pHead = new Node<T>; // �������� ������ ��� ������ ������� ����� �������
		pHead->val = stmp->val; // ����������� �������� ������� �������� �������� �������
		pHead->pNext = nullptr; // ����������� ��������� �� ���� ��� ������� nullptr

		if (stmp == stmp2) // ���� ���� ������� � ������� ����� 
		{
			pTail = new Node<T>;
			pTail->val = stmp->val;
			pTail->pNext = nullptr;
		}
		stmp = stmp->pNext; // ������������ ��������� �� ������ ������� �������� �������

		Node<T>* gtmp = pHead; // ��������� �� ������ ������� ����� �������

		while (stmp != stmp2) // ���� ��������� �� ������� �������� ������� �� ����� ����� ��������� �� ��������� ������� �������� ������� 
		{
			Node<T>* newNode = new Node<T>; //������� ����� ������� ����� �������
			newNode->val = stmp->val; // �������� � ���� ��������
			newNode->pNext = nullptr; // ���������� ��� ����. ���. ������� ��� nullptr

			gtmp->pNext = newNode; // ����. ���. ������� ������ ��� ����� ����� (��������� �� ���� ��� ������� � ������� �������� ������ �� ���� newNode � ��)

			stmp = stmp->pNext; // ��������� �� ��������� ������� ������ �� �������� ��������
			gtmp = gtmp->pNext; // ��������� �� ��������� ������� ������ ������
		}
		pTail = new Node<T>;
		pTail->val = stmp->val;
		pTail->pNext = nullptr;

		gtmp->pNext = pTail;
	}
	else
	{
		pHead = nullptr;
		pTail = nullptr;
	}
}

template <class T>
bool LQueue<T>::operator==(const LQueue<T>& q) const
{
	if (this == &q) return true;

	Node<T>* tmp = pHead;
	Node<T>* stmp = q.pHead;

	while (stmp != nullptr && tmp != nullptr) {
		if (tmp->val != stmp->val)
			return false;
		tmp = tmp->pNext;
		stmp = stmp->pNext;
	}
	return tmp == stmp;
}

template <class T>
bool LQueue<T>::operator!=(const LQueue<T>& q) const
{
	return (!(*this == q));
}

template <class T>
bool LQueue<T>::isEmpty() const
{
	return pHead == nullptr;
}

template <class T>
bool LQueue<T>::isFull() const
{
	try {
		Node<T>* tmp = new Node<T>;
		delete tmp;
		return false; // ���� ��������� � ������������ ������ ������� �� ���� �� �������� 
	}
	catch (std::bad_alloc e) { // ���� �� �� ������� � ������� �� ����� �������� ������ �� ������������� ��� ��� ������ 
		return true;
	}
}

template <class T>
void LQueue<T>::clear()
{
	while (pHead != nullptr) {
		Node<T>* tmp = pHead;
		pHead = pHead->pNext;
		delete tmp;
	}
}

template <class T>
T LQueue<T>::back() const
{
	if (isEmpty())
		throw - 1;
	return pTail->val;;
}

template <class T>
T LQueue<T>::front() const
{
	if (isEmpty())
		throw - 1;
	return pHead->val;
}

template <class T>
int LQueue<T>::size() const
{
	int count = 0;
	Node<T>* tmp = pHead;
	while (tmp != nullptr) {
		count++;
		tmp = tmp->pNext;
	}
	return count;
}

template <class T>
void LQueue<T>::push(T element)
{
	Node<T>* newNode = new Node<T>;
	newNode->val = element;
	newNode->pNext = nullptr;

	if (isEmpty()) {
		pHead = newNode;
		pTail = newNode;
	}
	else {
		pTail->pNext = newNode;
		pTail = pTail->pNext;
	}
}

template <class T>
T LQueue<T>::pop()
{
	if (isEmpty())
		throw - 1;
	T element = pHead->val;
	Node<T>* tmp = pHead;
	pHead = pHead->pNext;
	delete tmp;
	return element;
}