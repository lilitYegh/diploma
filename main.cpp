#include "graph.h"

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/ref.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/is_kuratowski_subgraph.hpp>
#include <vector>

#include <boost/graph/labeled_graph.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <sstream>

using namespace std;
using namespace boost;
int main(int argc, char** argv)
{


	using namespace boost;
	typedef adjacency_list<vecS,
                         vecS,
                         undirectedS,
                         property<vertex_index_t, int>,
                         property<edge_index_t, int>
                         > graph;

	ifstream inputGraph;
	inputGraph.open("graph.txt");
	int v = -1;
	string s,T;
	if(!inputGraph.eof())
	{
		getline(inputGraph, s);
		v = stoi(s);
	}
	if(v == -1)
	{
		std::cout << "File is empty\n";
		return 0;
	}
	Graph g(v);
	
	while(inputGraph.peek() != EOF)
	{
		getline(inputGraph, s);
		stringstream X(s);
		getline(X, T, ' ');
		int i = stoi(T);
		
		while (getline(X, T, ' ')) 
    		{  
        		g.addedge(i, stoi(T));

    		}  
	}
	g.print(); 
		
	inputGraph.close();
	
	Graph empty(v);
	Graph next_layer(v);
	next_layer = g;
	int c = 0;
	ofstream outputGraphs;
	outputGraphs.open("layers.txt");

          
	while(!next_layer.empty())
	{

		/*if(c!=0)
		{
			  for(int i = 0; i < next_layer.getSize(); i++)
			  {
			  	if(next_layer.adjlist[next_layer.index[i]].size() == 0)
			  	{
			  		next_layer.removevertix(next_layer.index[i]);

			  	}
			  }
	 		
		}*/
		g = next_layer;
		Graph empty(g.getSize());
		next_layer = empty;
		//g.print();
		//next_layer.print();
		std::cout<<"---------------Layer "<< ++c << "----------------\n";
		outputGraphs << "Layer " << c << "\n"; 
		graph temp(g.getSize());
		
	
		for(int i = 0; i < g.getSize(); i++)
		{
			for(auto it:g.adjlist[g.index[i]])
			{
				if(it > g.index[i])
				{
			       	add_edge(g.index[i], it, temp);
			       	if (boyer_myrvold_planarity_test(temp))
			       	{
						std::cout << "Graph is planar. ( " << g.index[i] << ", " << it <<") edge added."  << std::endl;
						outputGraphs << g.index[i] << " " << it << "\n";
					}
				
					else
					{	
						// Initialize the interior edge index
						std::cout << "Graph is not planar. ( " << g.index[i] << ", " << it <<") edge added."  << std::endl;
					  	property_map<graph, edge_index_t>::type e_index = get(edge_index, temp);
						graph_traits<graph>::edges_size_type edge_count = 0;
						graph_traits<graph>::edge_iterator ei, ei_end;
					  	for(boost::tie(ei, ei_end) = edges(temp); ei != ei_end; ++ei)
					  	{
						    		put(e_index, *ei, edge_count++);
						}

						  // Test for planarity - we know it is not planar, we just want to 
						  // compute the kuratowski subgraph as a side-effect
						typedef std::vector< graph_traits<graph>::edge_descriptor >  kuratowski_edges_t;
						kuratowski_edges_t kuratowski_edges;
						if (!boyer_myrvold_planarity_test(boyer_myrvold_params::graph = temp,
										   boyer_myrvold_params::kuratowski_subgraph = 
										       std::back_inserter(kuratowski_edges)))
						{
						      		//Input graph is not planar

						      	std::cout << "Edges in the Kuratowski subgraph: ";
						      	kuratowski_edges_t::iterator ki, ki_end;
						      	ki_end = kuratowski_edges.end();
						      	for(ki = kuratowski_edges.begin(); ki != ki_end; ++ki)
							{
							 	std::cout << *ki << " ";
							}
						      	std::cout << std::endl;
						      	next_layer.addedge(g.index[i], it);
						      	
							remove_edge(g.index[i], it, temp);
							
							std::cout<< "( " << g.index[i] << ", " << it <<") edge is moved to the layer " << c + 1 << " \n";
							
					
						}
					
					}
			   	}
			}
		}	

		if (boyer_myrvold_planarity_test(temp))
		{
			std::cout << "Graph is planar."  << std::endl;
		}
	
  	}
  	outputGraphs << v << " " << c;

return 0;
}

