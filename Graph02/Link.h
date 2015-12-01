#ifndef LINK_H
#define LINK_H
template<typename E>
class Link
{
private:
	static Link* freeList;
public:
	E element;
	Link* next;
	Link* pre;

	Link(Link* n=NULL,Link* p=NULL)
	{
		next = n;
		pre = p;
	}

	Link(const E& e, Link* n = NULL,Link* p=NULL)
	{
		element = e;
		next = n;
		pre = p;
	}

	void* operator new(size_t)
	{
		if (freeList == NULL)
		{
			return ::new Link<E>;
		}
		Link<E>* p = freeList;
		freeList = freeList->next;
		return p;
	}

	void operator delete(void* p)
	{
		((Link<E>*)p)->next = freeList;
		freeList = (Link<E>*)p;
	}

};
template<typename E>
Link<E>* Link<E>::freeList = NULL;
#endif