#ifndef GRAPHM_H
#define GRAPHM_H
#include "Graph.h"
//Implementation for the adjacency matrix representation
template<class E>
class Graphm :public Graph<E>
{
private:
	int UNVISITED;    //flag for unvisited mark
	int numVertex;    //Store number of vertices
	int numEdge;      //Store number of edges
	int **matrix;     //Pointer to adjacency matrix
	int *mark;        //Pointer to mark array;
	E   *elements;    //Pointer to elements array;

public:
	Graphm(int numVert = 0, int flag = -1) :UNVISITED(flag)
	{
		numVertex = numVert;
		numEdge = 0;
	}
	~Graphm()
	{
		delete[]mark;
		for (int i = 0; i < numVertex; i++)
			delete[]matrix[i];
		delete[]matrix;
		if (elements != NULL)
			delete elements;
	}

	//Initialize a graph of n vertices
	virtual void Init(int n)
	{
		mark = new int[n];
		for (int i = 0; i < n; i++)
			mark[i] = UNVISITED;
		matrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			matrix[i] = new int[n];
			for (int j = 0; j < n; j++)
				matrix[i][j] = 0;
		}
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
		for (int i = 0; i < numVertex; i++)
		{
			if (matrix[v][i] != 0)
				return i;
		}
		return numVertex;   //Return n if none
	}

	//Return v's next neighbor
	virtual int next(int v, int w)
	{
		for (int i = w + 1; i < numVertex; i++)
		if (matrix[v][i] != 0)
			return i;
		return numVertex;      //Return n if none
	}

	//Set the weight for an edge
	//i,j: The vertices
	//wgt: Edge weight
	virtual void setEdge(int v1, int v2, int wght)
	{
		if (matrix[v1][v2] == 0)
			numEdge++;
		matrix[v1][v2] = wght;
	}

	//Delete an edge
	//i,j: The vertices
	virtual void delEdge(int v1, int v2)
	{
		if (matrix[v1][v2] != 0)
			numEdge--;
		matrix[v1][v2] = 0;
	}

	//Determine if an edge is in the graph
	//i,j: The vertices
	//Return: true if edge i,j has non-zero weight
	virtual bool isEdge(int v1, int v2)
	{
		return matrix[v1][v2] != 0;
	}

	//Return an edge's weight
	//i,j: The vertices
	//Return: The weight of edge i,j or zero
	virtual double weight(int v1, int v2)
	{
		return matrix[v1][v2];
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