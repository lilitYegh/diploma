#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
#include<list>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
private:

	int vertex;
	
public:
   	list<int> *adjlist;
   	vector<int> index; 
	Graph() = default;
	Graph(int v);

   	void addedge(int u,int v);


	void print();
	bool empty();	
   	void removevertix(int v);
	int getSize();
};



#endif // GRAPH_H
