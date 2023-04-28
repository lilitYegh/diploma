#include "graph.h"
Graph::Graph(int v)
	{
		adjlist = new list<int> [v];
		vertex = v;
		for(int i = 0; i < v; ++i)
        	{
        		index.push_back(i);
        	}
	}

void Graph::addedge(int u,int v)
{
	adjlist[u].push_back(v);
	adjlist[v].push_back(u);
	
}


void Graph::print()
{

	for(int i = 0; i < index.size(); i++)
	{
           	cout << this->index[i] << "-->";
		for(auto it:adjlist[i])
		{
		      	cout << it << " ";
		}
			cout << endl;
		
	}
}
bool Graph::empty()
{
   	bool e = true;
   	for(int i = 0; i < this->index.size(); i++)
	{
		if(!adjlist[i].empty())
		{
			e = false;
		}
	}

       return e;
}	
   	void Graph::removevertix(int v)
   	{
   		//list<int>::iterator it = adjlist->begin();
   		//std::advance(it, v);
   		//adjlist->erase(it);
   		
   		index[v] = 0;
   		//vector<int>::iterator new_end;
    		//new_end = remove(index.begin(), index.end(), v);
	}
	int Graph::getSize()
	{
		int size = index.size();
		for(int i = 1; i< index.size(); ++i)
		{
			if(index[i] == 0)
				size--;
		}
		return index.size();
	}

