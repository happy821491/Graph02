#ifndef GRAPHL_H
#define GRAPHL_H
#include"Edge.h"
#include"Graphm.h"
#include"LinkedList.h"
template<class E>
class Graphl :public Graph<E>
{
private:
	List<Edge> **vertex;  //List headers
	int numEdge, numVertex;
	int *mark;
	int UNVISITED;
public:
	Graphl(int numVert, int unvisited = -1) :UNVISITED(unvisited)
	{
		Init(numVert);
	}

	//Initialize a graph of n vertices
	virtual void Init(int n)
	{
		numVertex = n;
		numEdge = 0;
		mark = new int[numVertex];
		for (int i = 0; i < numVertex; i++)
			mark[i] = UNVISITED;
		vertex = new List<Edge>*[numVertex];
		for (int i = 0; i < numVertex; i++)
			vertex[i] = new LinkedList<Edge>();
	}

	//Return:the number of vertices and edges
	virtual const int n()
	{
		return numVertex;
	}
	virtual const int e()
	{
		return numEdge;
	}

	//Return v's first neighbor
	virtual int first(int v)
	{
		if (vertex[v]->length() <= 0)
			return numVertex;
		vertex[v]->moveToStart();
		Edge it = vertex[v]->getValue();
		return it.vertex();
	}

	//Return v's next neighbor
	virtual int next(int v, int w)
	{
		if (isEdge(v, w) && vertex[v]->currPos() + 1<vertex[v]->length())
		{
			vertex[v]->next();
			Edge it = vertex[v]->getValue();
			return it.vertex();
		}
		return numVertex;
	}

	//Set the weight for an edge
	//i,j: The vertices
	//wgt: Edge weight
	virtual void setEdge(int v1, int v2, int wght)
	{
		Edge temp;
		Edge it(v2, wght);
		if (isEdge(v1, v2))
		{ //Edge already exits in graph
			vertex[v1]->remove(temp);
			vertex[v1]->insert(it);
		}
		else
		{//Kepp neightbors sorted by vertex index
			numEdge++;
			for (vertex[v1]->moveToStart(); vertex[v1]->currPos() < vertex[v1]->length(); vertex[v1]->next())
			{
				temp = vertex[v1]->getValue();
				if (temp.vertex()>v2)
					break;
			}
			vertex[v1]->insert(it);
		}
	}

	//Delete an edge
	//i,j: The vertices
	virtual void delEdge(int v1, int v2)
	{
		if (isEdge(v1, v2))
		{
			numEdge--;
			Edge it;
			vertex[v1]->remove(it);
		}
	}

	//Determine if an edge is in the graph
	//i,j: The vertices
	//Return: true if edge i,j has non-zero weight
	virtual bool isEdge(int v1, int v2)
	{
		Edge it;
		for (vertex[v1]->moveToStart(); vertex[v1]->currPos() < vertex[v1]->length(); vertex[v1]->next())
		{
			it = vertex[v1]->getValue();
			if (it.vertex() == v2)
				return true;
		}
		return false;
	}

	//Return an edge's weight
	//i,j: The vertices
	//Return: The weight of edge i,j or zero
	virtual double weight(int v1, int v2)
	{
		if (isEdge(v1, v2))
		{
			Edge it = vertex[v1]->getValue();
			return it.weight();
		}
		return 0;
	}

	//Get and Set the mark value for a vertex
	//v: the vertex
	//val: The value to set
	virtual int getMark(int v)
	{
		return mark[v];
	}
	virtual void setMark(int v, int val)
	{
		mark[v] = val;
	}

};

#endif
