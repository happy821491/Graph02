#ifndef LIST_H
#define LIST_H
#include <assert.h>
#define defaultSize  100
template <typename E>
class List
{
private:
	void operator=(const List&){}
	List(const List&){}
public:
	List(){}
	virtual ~List(){};
	virtual void clear()=0;
	virtual bool insert(const E& item) = 0;
	virtual bool append(const E& item) = 0;
	virtual bool remove(E& item) = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual bool prev() = 0;
	virtual bool next() = 0;
	virtual int length() const= 0;
	virtual int currPos() const = 0;
	virtual bool moveToPos(int Pos) = 0;
	virtual const E& getValue() const = 0;
};

#endif