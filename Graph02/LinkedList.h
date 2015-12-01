#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include"List.h"
#include"Link.h"
template<typename E>
class LinkedList :public List<E>
{
private:
	
	void init()
	{
		head = tail = curr = new Link<E>;
		cnt = 0;
	}

	void removeAll()
	{
		Link<E>* p = NULL;
		while (head)
		{
			p = head;
			head = head->next;
			delete p;
		}
		curr = tail = head = NULL;
	}
public:
	int cnt;
	Link<E>* head;
	Link<E>* tail;
	Link<E>* curr;
	LinkedList(int size = defaultSize)
	{
		init();
	}
	~LinkedList()
	{
		removeAll();
	}

	void clear()
	{
		removeAll();
		init();
	}

	bool insert(const E& item)
	{
		Link<E>* p = new Link<E>(item, curr->next);
		curr->next = p;
		if (curr == tail)
		{
			tail = p;
		}
		cnt++;
		return true;
	}

	bool append(const E& item)
	{
		Link<E>* p = new Link<E>(item);
		tail->next = p;
		tail = p;
		cnt++;
		return true;
	}
	bool remove()
	{
		if (curr->next == NULL)
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
		delete p;
		cnt--;
		return true;;
	}

	bool remove(E& e)
	{
		if (curr->next == NULL)
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
	void moveToStart()
	{
		curr = head;
	}
	void moveToEnd()
	{
		curr = tail;
	}

	bool prev()
	{
		if (curr == head)
			return false;
		Link<E>* p = head;
		while (p->next != curr)
		{
			p = p->next;
		}
		curr = p;
		return true;
	}

	bool next()
	{
		if (curr == tail)
			return false;
		curr = curr->next;
		return true;
	}

	int length() const
	{
		return cnt;
	}

	int currPos() const
	{
		int time = 0;
		for (Link<E>* p = head; p != curr; time++)
			p = p->next;
		return time;
	}

	bool moveToPos(int Pos)
	{
		if (Pos<0 || Pos>cnt)
			return false;
		for (curr = head; Pos > 0; Pos--)
			curr = curr->next;
		return true;
	}

	const E& getValue() const
	{
		assert(curr->next != NULL);
		return curr->next->element;
	}


	void reverse()
	{
		Link<E>* p1=head->next;
		Link<E>* p2 = p1->next;
		Link<E>* p3 = NULL;
		while (p2)
		{
			p3 = p2->next;
			p2->next = p1;
			p1 = p2;
			p2 = p3;
		}
		p3 = head->next;
		head->next = tail;
		tail = p3;
	}

	void merge(LinkedList<E>& secondList)
	{
		Link<E>* p1 = head;
		Link<E>* p2 = secondList.head;
		while (p1->next&&p2->next)
		{
			if (p1->next->element <= p2->next->element)
			{
				p1 = p1->next;
			}
			else
			{
				Link<E>* temp = p2->next->next;
				p2->next->next = p1->next;
				p1->next = p2->next;
				p1 = p1->next;
				p2->next = temp;
				
			}
		}
		if (p2->next)
		{
			p1->next = p2->next;
			tail = secondList.tail;
		}
			
		/*while (p2->next)
		{
			p1->next = p2->next;
			p1 = p1->next;
			p2 = p2->next;
			cnt++;
		}*/
		cnt += secondList.length();
		delete secondList.head;
		secondList.head = NULL;
		moveToStart();

	}

};

#endif