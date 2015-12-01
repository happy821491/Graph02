#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
template<typename E>
class DoubleLinkedList :public List<E>
{
private:
	Link<E>* head;
	Link<E>* curr;
	Link<E>* tail;
	int cnt;
	int currIndex;
	void init()
	{
		head = curr = new Link<E>;
		tail = new Link<E>;
		head->next = tail;
		tail->pre = head;
		cnt = 0;
		currIndex = 0;
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
	DoubleLinkedList(int size = defaultSize)
	{
		init();
	}
	~DoubleLinkedList()
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

		if (curr == tail)
		{
			Link<E>* p = new Link<E>(item, tail, curr->pre);
			tail->pre = p;
		}
		else
		{
			Link<E>* p = new Link<E>(item, curr->next, curr);
			curr->next->pre = p;
			curr->next = p;
		}
		cnt++;
		return true;
	}

	bool append(const E& item)
	{
		Link<E>* p = new Link<E>(item);
		tail->pre = tail->pre->next = new Link<E>(item, tail, tail->pre);
		cnt++;
		return true;
	}

	bool remove(E& e)
	{
		if (curr->next == tail||curr==tail)
		{
			return false;
		}
		Link<E>* p = curr->next;
		E element = p->element;
		curr->next = curr->next->next;
		curr->next->pre = curr;
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
		curr = curr->pre;
		currIndex--;
		return true;
	}

	bool next()
	{
		if (curr == tail)
			return false;
		curr = curr->next;
		currIndex++;
		return true;
	}
	int length() const
	{
		return cnt;
	}
	int currPos() const
	{
		return currIndex;
	}

	bool moveToPos(int Pos)
	{
		if (Pos<0 || Pos>cnt)
			return false;
		currIndex = Pos;
		for (curr = head; Pos > 0; Pos--)
			curr = curr->next;
		return true;
	}

	const E& getValue() const
	{
		assert(curr!=tail&&curr->next != tail);
		return curr->next->element;
	}

};


#endif