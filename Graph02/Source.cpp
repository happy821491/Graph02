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
		return a.distance < b.distance;
	}
};

bool updateTrack(List<int> *l1, List<int> *l2, int tail){
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
	Heap<DijkElem, EdgeComp> heap(E, 1, G->e());
	for (i = 0; i < G->n(); i++){
		do{
			if (heap.size() <= 0)
				return;
			temp = heap.removeFirst();
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
				updateTrack(track[w], track[v], w);
			}
		}
	}

	for (int i = 0; i < G->n(); i++){
		cout << char(i + 'A') << " : ";
		for (track[i]->moveToStart(); track[i]->currPos() < track[i]->length(); track[i]->next())
			cout << " -> " << char(track[i]->getValue() + 'A');
		cout << endl;
	}
}



void printPrimMst(int *V, double *D, int size){
	double sum = 0;
	for (int i = 0; i < size; sum += D[i], i++)
		cout << V[i] << " -> " << i << " weight: " << D[i] << endl;
	cout << "the total sum of MST : " << sum << endl;
}

template<typename E>
void Prim(Graph<E>* G, double *D, int startVertex){
	for (int i = 0; i < G->n(); i++)
		D[i] = INFINITY;
	D[startVertex] = 0;
	int VISITED = -4;
	DijkElem *E = new DijkElem[G->e()];
	int *V = new int[G->n()];    //V[i]表示以第i个节点为尾节点连接距离最短的节点
	for (int i = 0; i < G->n(); i++)
		V[i] = i;
	//V[startVertex] = startVertex;
	DijkElem temp;
	temp.distance = 0;
	temp.vertex = startVertex;
	E[0] = temp;
	Heap<DijkElem, EdgeComp> heap(E, 1, G->e());
	int v = 0;
	double distance = 0;
	for (int i = 0; i < G->n(); i++)
	{
		do{
			if (heap.size() <= 0)
				return;
			temp = heap.removeFirst();
			distance = temp.distance;
			v = temp.vertex;
		} while (G->getMark(v) == VISITED);
		G->setMark(v, VISITED);
		for (int w = G->first(v); w < G->n(); w = G->next(v, w)){
			if (G->getMark(w) == VISITED)
				continue;
			if (D[w]>G->weight(v, w)){
				D[w] = G->weight(v, w);
				V[w] = v;
				temp.vertex = w;
				temp.distance = D[w];
				heap.insert(temp);
			}
		}
	}
	printPrimMst(V, D, G->n());

}

void testPrimMst()
{
	Graph<double>* graph = new Graphl<double>(6);
	graph->setEdge(0, 2, 7);
	graph->setEdge(2, 0, 7);
	graph->setEdge(2, 1, 5);
	graph->setEdge(1, 2, 5);
	graph->setEdge(2, 3, 1);
	graph->setEdge(3, 2, 1);
	graph->setEdge(2, 5, 2);
	graph->setEdge(5, 2, 2);
	graph->setEdge(3, 5, 2);
	graph->setEdge(5, 3, 2);
	graph->setEdge(1, 5, 6);
	graph->setEdge(5, 1, 6);
	graph->setEdge(0, 4, 9);
	graph->setEdge(4, 0, 9);
	graph->setEdge(4, 5, 1);
	graph->setEdge(5, 4, 1);
	double D[6];
	Prim(graph, D, 2);
}


int main()
{
	testPrimMst();
	//Dijkstra(graph, D, 0);
	//for (int i = 0; i < 5; i++)
	//	cout << char(i+'A') << " : " << D[i] << endl;

}
