#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H
#include"LinkedList.h"
template<typename E>
class CircularLinkedList:public LinkedList<E>
{
public:
	CircularLinkedList()
	{
		head->next = head;
	}
	bool append(const E& item)
	{
		LinkedList<E>::append(item);
		tail->next = head;
		return true;
	}
	bool insert(const E& item)
	{
		LinkedList<E>::insert(item);
		tail->next = head;
		return true;
	}
	bool remove(E& e)
	{
		if (curr==tail)
		{
			return false;
		}
		if (curr->next == tail)
		{
			tail = curr;
		}
		Link<E>* p = curr->next;
		E element = p->element;
		curr->next = curr->next->next;
		e = element;
		delete p;
		cnt--;
		return true;
	}

	bool next()
	{
		curr = curr->next;
		return true;
	}

	bool prev()
	{
		Link<E>* temp = curr;
		while (curr->next != temp)
			curr = curr->next;
		return true;
	}

};

#endif