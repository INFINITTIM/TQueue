#pragma once

#include <iostream>

using namespace std;

template <class T>
class TQueue
{
	T* pMem;
	int mem_size;
	int element_counter;
	int tail;
	int head;

	T operator[](int index) const;
public:
	//������������
	TQueue(int size);
	TQueue(const TQueue& other_queue);
	~TQueue();

	//���������� ����������
	TQueue& operator=(const TQueue& other_queue);
	bool operator==(const TQueue& other_queue) const;
	bool operator!=(const TQueue& other_queue) const;
	
	//�������
	void push(T element);
	T pop();
	bool isEmpty() const;
	bool isFull() const;
	void clear();
	T front() const;
	T back() const;

	//���������� ������ + ����������


	friend ostream& operator<<(ostream& out, const TQueue& queue)
	{
		for (int i = 0; i < queue.element_counter; i++) {
			out << queue[i] << " ";
		}
		return out;
	}
};

//---------------------------------------------------------//
//                     ������������                        //
//---------------------------------------------------------//

template <class T>
TQueue<T>::TQueue(int size)
{
	mem_size = size;
	pMem = new T[mem_size];
	head = 0;
	tail = -1;
	element_counter = 0;
}

template <class T>
TQueue<T>::TQueue(const TQueue& other_queue)
{
	mem_size = other_queue.mem_size;
	head = other_queue.head;
	tail = other_queue.tail;
	element_counter = other_queue.element_counter;
	pMem = new T[mem_size];
	if (tail >= head)
	{
		for (int i = head; i <= tail; i++)
		{
			pMem[i] = other_queue.pMem[i];
		}
	}
	else
	{
		for (int i = head; i <= mem_size; i++)
		{
			pMem[i] = other_queue.pMem[i];
		}
		for (int i = 0; i < tail; i++)
		{
			pMem[i] = other_queue.pMem[i];
		}
	}
}

template <class T>
TQueue<T>::~TQueue()
{
	delete[] pMem;
}

//---------------------------------------------------------//
//                        ���������                        //
//---------------------------------------------------------//

template <class T>
TQueue<T>& TQueue<T>::operator=(const TQueue& q) {
	if (this == &q) return *this;
	if (mem_size != q.mem_size) {
		mem_size = q.mem_size;
		delete[] pMem;
		pMem = new T[mem_size];
	}
	element_counter = q.element_counter;
	head = q.head;
	tail = q.tail;
	if (q.tail >= q.head) {
		for (int i = 0; head + i <= tail; i++) {
			pMem[head + i] = q.pMem[head + i];
		}
	}
	else {
		for (int i = 0; i <= tail; i++) {
			pMem[i] = q.pMem[i];
		}
		for (int i = head; i < size; i++) {
			pMem[i] = q.pMem[i];
		}
	}
	return *this;
}

template <class T>
bool TQueue<T>::operator==(const TQueue& other_queue) const
{
	if (mem_size != other_queue.mem_size || element_counter != other_queue.element_counter) 
		return false;
	if (element_counter == 0) 
		return true;
	for (int i = 0; i < element_counter; i++) {
		if (pMem[(head + i) % mem_size] != other_queue.pMem[(other_queue.head + i) % mem_size]) 
			return false;
	}
	return true;
}

template <class T>
bool TQueue<T>::operator!=(const TQueue& other_queue) const
{
	return (!(*this == other_queue));
}

template <class T>
T TQueue<T>::operator[](int index) const {
	return pMem[(head + index) % mem_size];
}

//---------------------------------------------------------//
//                         �������                         //
//---------------------------------------------------------//

template <class T>
void TQueue<T>::push(T element)
{
	if (isFull()) throw - 1;
	tail = tail % mem_size;
	pMem[++tail] = element;
	element_counter++;
}

template <class T>
T TQueue<T>::pop()
{
	if (isEmpty()) throw - 1;
	T result = pMem[head];
	head++;
	head = head % mem_size;
	element_counter--;
	return result;
}

template<class T>
bool TQueue<T>::isFull() const {
	return element_counter == mem_size;
}

template<class T>
bool TQueue<T>::isEmpty() const {
	return element_counter == 0;
}

template<class T>
void TQueue<T>::clear()
{
	head = 0;
	tail = -1;
	element_counter = 0;
}

template<class T>
T TQueue<T>::front() const
{
	if (isEmpty()) throw - 1;
	return pMem[head];
}

template<class T>
T TQueue<T>::back() const
{
	if (isEmpty()) throw - 1;
	return pMem[tail];
}