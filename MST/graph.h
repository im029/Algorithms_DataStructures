#include <string>
#include <vector>
#include <list>
#include <limits>
#include <iostream>
#include <utility>
#include <queue>
#include <functional>
/**
	graph.h
	purpose: class to represent a graph using adjacency list and implements BFS and DFS
	@author: Ishant Malik; 16/CS/034
	@version: 1.0.0 03/04/2018
*/

/** 
	class graph
	purpose: represents a graph using adjacency list
	private members:
		class vertex - represents vertex of graph

		
*/
class graph
{
private:
	/*	class to represent vertex in the graph
		
		@members:
		color - String - represents the color during traversal
		name - String  - name of vertex
		distance - int - level of vertex in bfs/dfs
		is_start - bool - denotes if vertex is source vertex
		connected_vertices - list - stores pointers to connected vertices
	*/
	class vertex
	{
	public:
		std::string name;
		int key;
		vertex *pi;
		bool is_start;
		std::list<std::pair<vertex *, int>> connected_vertices;

		// constructor to initalize variables
		vertex(std::string namex, bool is_startx = false)
		{
			key = std::numeric_limits<int>::max();
			pi = NULL;
			name = namex;
			is_start = is_startx;
		}

		bool operator > (vertex v)
		{
			return key > v.key ? true : false;
		}
	};

	// ajacency list to reprsent graphs
	std::vector<vertex *> adjacency_list;
	int time;

public: 
	graph(): time(0){}

	// add vertes to graph
	void add_vertex(std::string id, bool is_start = false)
	{
		adjacency_list.push_back(new vertex(id, is_start));
	}
	
	// add an edge
	void add_edge(int v1, int v2, int w)
	{
		adjacency_list.at(v1)->connected_vertices.push_back(std::make_pair(adjacency_list.at(v1), w));
	}

	// print adjacency list
	void print()
	{
		std::cout << "Adjacency_list" << std::endl;

		for (unsigned int i = 0; i < adjacency_list.size(); i++)
		{
			std::cout << adjacency_list[i]->name << ": ";
			for (std::list<std::pair<vertex *, int>>::iterator it = adjacency_list[i]->connected_vertices.begin(); it != adjacency_list[i]->connected_vertices.end(); ++it)
				std::cout << "-> " << (*it).first->name;
			std::cout << std::endl;
		}
	}

	//MST PRIM
	void MST_prim()
	{
		adjacency_list[0]->connected_vertices.front().first->key = 0;
		std::priority_queue<vertex *, std::vector<vertex *>, std::greater<vertex>> q;

		for (int i = 0; i < adjacency_list.size(); i++)
			q.push(adjacency_list[i]);

		std::vector<vertex *> seen;
 		
		while (!q.empty())
		{
			vertex *temp = q.top();
			seen.push_back()
			q.pop();

			for (std::list<std::pair<vertex *, int>>::iterator it = adjacency_list[i]->connected_vertices.begin(); it != adjacency_list[i]->connected_vertices.end(); ++it)
			{
				if ((*it).second < (*it).first->key)
				{
					(*it).first->pi = temp;
					(*it).first->key = (*it).second;
				}
			}
		}
	}

	// manage leftovers
	~graph()
	{
		for (std::vector<vertex *>::iterator it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
			free(*it);
	}
};