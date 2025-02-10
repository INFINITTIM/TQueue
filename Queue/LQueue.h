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
	Node<T>* stmp = q.pHead; // указатель на первый элемент исходной очереди 
	Node<T>* stmp2 = q.pTail; // указатель на последний элемент исходной очереди 
	if (stmp != nullptr)
	{
		pHead = new Node<T>; // выделяем память под первый элемент новой очереди
		pHead->val = stmp->val; // присваиваем значение первого элемента исходной очереди
		pHead->pNext = nullptr; // присваиваем указателю на след вып элемент nullptr

		if (stmp == stmp2) // если один элемент в очереди когда 
		{
			pTail = new Node<T>;
			pTail->val = stmp->val;
			pTail->pNext = nullptr;
		}
		else
		{
			stmp = stmp->pNext; // переставляем указатель на второй элемент исходной очереди

			Node<T>* gtmp = pHead; // указатель на первый элемент новой очереди

			while (stmp != stmp2) // пока указатель на элемент исходной очереди не будет равен указателю на последний элемент исходной очереди 
			{
				Node<T>* newNode = new Node<T>; //создаем новый элемент новой очереди
				newNode->val = stmp->val; // копируем в него значение
				newNode->pNext = nullptr; // записываем его след. вып. элемент как nullptr

				gtmp->pNext = newNode; // след. вып. элемент теперь это новое звено (указатель на след вып элемент у первого элемента теперь на этот newNode и тд)

				stmp = stmp->pNext; // переходим на следующий элемент списка из которого копируем
				gtmp = gtmp->pNext; // переходим на следующий элемент нового списка
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
		pHead = new Node<T>; // выделяем память под первый элемент новой очереди
		pHead->val = stmp->val; // присваиваем значение первого элемента исходной очереди
		pHead->pNext = nullptr; // присваиваем указателю на след вып элемент nullptr

		if (stmp == stmp2) // если один элемент в очереди когда 
		{
			pTail = new Node<T>;
			pTail->val = stmp->val;
			pTail->pNext = nullptr;
		}
		stmp = stmp->pNext; // переставляем указатель на второй элемент исходной очереди

		Node<T>* gtmp = pHead; // указатель на первый элемент новой очереди

		while (stmp != stmp2) // пока указатель на элемент исходной очереди не будет равен указателю на последний элемент исходной очереди 
		{
			Node<T>* newNode = new Node<T>; //создаем новый элемент новой очереди
			newNode->val = stmp->val; // копируем в него значение
			newNode->pNext = nullptr; // записываем его след. вып. элемент как nullptr

			gtmp->pNext = newNode; // след. вып. элемент теперь это новое звено (указатель на след вып элемент у первого элемента теперь на этот newNode и тд)

			stmp = stmp->pNext; // переходим на следующий элемент списка из которого копируем
			gtmp = gtmp->pNext; // переходим на следующий элемент нового списка
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
		return false; // если выделение и освобождение прошло успешно то стек не заполнен 
	}
	catch (std::bad_alloc e) { // если же не успешно и система не может выделить память то выбрасывается вот эта ошибка 
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