#include<iostream>
using namespace std;
#include"Edge.h"
#include"Graphm.h"
#include"Graphl.h"
#include"Heap.h"
class DijkElem{
public:
	int vertex;
	double distance;
	DijkElem(){
		vertex = -1;
		distance = -1;
	}
	DijkElem(int v, int d){
		vertex = v;
		distance = d;
	}

};

class EdgeComp{
public:
	static  bool prior(DijkElem a, DijkElem b)  //return True if a>=b
	{
		return a.distance<b.distance;
	}
};

bool updateTrack(List<int> *l1, List<int> *l2,int tail){
	l1->clear();
	for (l2->moveToStart(); l2->currPos() < l2->length(); l2->next()){
		l1->append(l2->getValue());
	}
	l1->append(tail);
	return true;
}

template<class E>
void Dijkstra(Graph<E>* G, double *D, int s){

	List<int> **track = new List<int>*[G->n()];
	for (int i = 0; i < G->n(); i++)
		track[i] = new LinkedList<int>();
	
	int VISITED = -4;
	//int INFINITY=99999;
	int i, v, w;
	DijkElem temp;
	DijkElem*E = new DijkElem[G->e()];
	for (i = 0; i < G->n(); i++)
		D[i] = INFINITY;
	D[s] = 0;
	temp.vertex = s;
	temp.distance = 0;
	E[0] = temp;
	Heap<DijkElem, EdgeComp> heap(E,1,G->e());
	for (i = 0; i < G->n(); i++){
		do{
			if (heap.size() <= 0)
				return;
			temp=heap.removeFirst();
			v = temp.vertex;
		} while (G->getMark(v) == VISITED);
		if (D[v] == INFINITY)
			return;
		G->setMark(v, VISITED);
		for (w = G->first(v); w < G->n(); w = G->next(v, w)){
			if (D[w]>D[v] + G->weight(v, w)){
				D[w] = D[v] + G->weight(v, w);
				temp.vertex = w;
				temp.distance = D[w];
				heap.insert(temp);
				updateTrack(track[w], track[v],w);
			}
		}
	}

	for (int i = 0; i < G->n(); i++){
		cout << char(i+'A') << " : ";
		for (track[i]->moveToStart(); track[i]->currPos() < track[i]->length(); track[i]->next())
			cout << " -> " << char(track[i]->getValue()+'A');
		cout << endl;
	}
}


int main()
{
	Graph<double>* graph = new Graphl<double>(5);
	graph->setEdge(0, 1, 10);
	graph->setEdge(0, 2, 3);
	graph->setEdge(0, 3, 20);
	graph->setEdge(1, 3, 5);
	graph->setEdge(2, 1, 2);
	graph->setEdge(2, 4, 15);
	graph->setEdge(3, 4, 11);
	double D[5];
	Dijkstra(graph, D, 0);
	for (int i = 0; i < 5; i++)
		cout << char(i+'A') << " : " << D[i] << endl;
}
