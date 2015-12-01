#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include"List.h"

template<typename E>
class ArrayList :public List<E>
{
private:
	int maxSize;
	int listSize;
	int curr;
	E* listArray;
public:
	ArrayList(int size = defaultSize)
	{
		maxSize = size;
		listSize = 0;
		curr = 0;
		listArray = new E[maxSize];
	}
	~ArrayList()
	{
		if (listArray != NULL)
		{
			delete[]listArray;
		}
		listArray = NULL;
		listSize = 0;
		maxSize = 0;
		curr = 0;
	}
	void clear()
	{
		if (listArray != NULL)
		{
			delete[]listArray;
		}
		listSize = 0;
		curr = 0;
		listArray = new E[maxSize];
	}
	bool insert(const E& item)
	{
		if (listSize >= maxSize)
			return false;
		for (int i = listSize; i > curr; i--)
		{
			listArray[i] = listArray[i - 1];
		}
		listArray[curr] = item;
		listSize++;
		return true;
	}

	bool append(const E& item)
	{
		if (listSize >= maxSize)
			return false;
		listArray[listSize] = item;
		listSize++;
		return true;
	}

	bool remove(E& e)
	{
		E item = listArray[curr];
		for (int i = curr; i < listSize - 1; i++)
		{
			listArray[i] = listArray[i + 1];
		}
		listSize--;
		e = item;
		return true;
		//return item;
	}

	void moveToStart()
	{
		curr = 0;
	}

	void moveToEnd()
	{
		curr = listSize - 1;
		if (curr < 0)
			curr = 0;
	}

	bool prev()
	{
		if (curr <= 0)
			return false;
		curr--;
		return true;
	}

	bool next()
	{
		if (curr >= listSize - 1)
			return false;
		curr++;
		return true;
	}

	int length() const
	{
		return listSize;
	}

	int currPos() const
	{
		return curr;
	}

	bool moveToPos(int Pos)
	{
		if (Pos < 0 || Pos >= listSize)
		{
			return false;
		}
		curr = Pos;
		return true;
	}

	const E& getValue() const
	{
		return listArray[curr];
	}


};
#endif