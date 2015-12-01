#ifndef HEAP_H
#define HEAP_H
template<typename E, typename Comp>
class Heap
{
private:
	E* heap;
	int maxSize;
	int n;

	void swap(int i, int j)
	{
		E temp = heap[i];
		heap[i] = heap[j];
		heap[j] = temp;
	}

	void siftDown(int pos)
	{
		int j = 0, rc = 0;
		while (!isLeaf(pos))
		{
			j = leftChild(pos);
			rc = rightChild(pos);
			if (rc < n&&Comp::prior(heap[rc], heap[j]))
			{
				j = rc;
			}
			if (Comp::prior(heap[j], heap[pos]))
			{
				swap(pos, j);
			}
			pos = j;
		}
	}

public:

	Heap(E* h, int num, int maxsize)
	{
		heap = h;
		n = num;
		maxSize = maxsize;

	}
	bool isLeaf(int pos) const       //True if pos is a leaf
	{
		return (pos >= n / 2) && (pos < n);
	}
	int leftChild(int pos) const
	{
		return 2 * pos + 1;
	}
	int rightChild(int pos)const
	{
		return 2 * pos + 2;
	}
	int parent(int pos)const
	{
		return (pos - 1) / 2;
	}
	void buildHeap()
	{
		for (int i = n / 2 - 1; i >= 0; i--)
			siftDown(i);
	}
	int size()const  //return current sum of the node
	{
		return n;
	}

	bool insert(E element)
	{
		if (n >= maxSize)
			return false;
		int curr = n++;
		heap[curr] = element;
		while (curr > 0 && Comp::prior(heap[curr], heap[parent(curr)]))
		{
			swap(curr, parent(curr));
			curr = parent(curr);
		}
		return true;
	}
	E removeFirst()
	{
		if (n <= 0)
			abort();
		swap(0, --n);
		if (n > 0)
			siftDown(0);
		return heap[n];
	}
	E remove(int pos)
	{
		if (n <= 0)
			abort();
		if (pos == n - 1)
			n--;
		else
		{
			swap(pos, --n);
			while (pos > 0 && Comp::prior(heap[pos], heap[parent(pos)]))
			{
				swap(pos, parent(pos));
				pos = parent(pos);
			}
			if (n != 0)
				siftDown(pos);
		}
		return heap[n];


	}
};

#endif