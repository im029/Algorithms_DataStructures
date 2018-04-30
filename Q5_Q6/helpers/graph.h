#include <string>
#include <vector>
#include <list>
#include <limits>
#include <iostream>

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
		std::string color;
		std::string name;
		int distance;
		int finish;
		vertex *pi;
		bool is_start;
		std::list<vertex *> connected_vertices;

		// constructor to initalize variables
		vertex(std::string namex, bool is_startx = false)
		{
			color = "white";
			distance = std::numeric_limits<int>::max();
			pi = NULL;
			name = namex;
			is_start = is_startx;
			finish = NULL;
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
	void add_edge(int v1, int v2)
	{
		adjacency_list.at(v1)->connected_vertices.push_back(adjacency_list.at(v2));
	}

	// print adjacencyh list
	void print()
	{
		std::cout << "Adjacency_list" << std::endl;

		for (unsigned int i = 0; i < adjacency_list.size(); i++)
		{
			std::cout << adjacency_list[i]->name << ": ";
			for (std::list<vertex *>::iterator it = adjacency_list[i]->connected_vertices.begin(); it != adjacency_list[i]->connected_vertices.end(); ++it)
				std::cout << "-> " << (*it)->name;
			std::cout << std::endl;
		}
	}

	// Breadth First search
	void bfs(int start_vertex)
	{
		start_vertex = start_vertex - 1;
		adjacency_list[start_vertex]->distance = 0;
		adjacency_list[start_vertex]->color = "gray";
		adjacency_list[start_vertex]->is_start = true;

		std::list<vertex *> queue;

		queue.push_back(adjacency_list[start_vertex]);

		while (!queue.empty())
		{
			vertex *current = queue.front();
			queue.pop_front();

			for (std::list<vertex *>::iterator it = current->connected_vertices.begin(); it != current->connected_vertices.end(); ++it)
			{
				if ((*it)->color.compare("white") == 0)
				{
					(*it)->color = "gray";
					(*it)->distance = current->distance + 1;
					(*it)->pi = current;
					queue.push_back(*it);
				}
			}
		}
	}

	// print bfs
	void print_bfs()
	{
		std::cout << "\n";
		std::cout << "Vertex\tParent\tLevel\tSource" << std::endl;
		for (unsigned int i = 0; i < adjacency_list.size(); i++)
		{
			std::cout << adjacency_list[i]->name << "\t" << ((adjacency_list[i]->pi) ? adjacency_list[i]->pi->name : "NULL") << "\t"; 
			std::cout << adjacency_list[i]->distance << "\t" << (adjacency_list[i]->is_start ? "Yes" : "No") << std::endl;
		}
	}

	void dfs_visit(vertex *u)
	{
		time = time + 1;
		u->distance = time;
		u->color = "gray";
		for (std::list<vertex *>::iterator it = u->connected_vertices.begin(); it != u->connected_vertices.end(); ++it)
		{
			if ((*it)->color.compare("white") == 0)
			{
				(*it)->pi = u;
				dfs_visit(*it);
			}
		}
		time = time + 1;
		u->finish = time;
	}

	void dfs(int start_vertex)
	{
		start_vertex = start_vertex - 1;
		for (int i = start_vertex; i < adjacency_list.size(); i++)
			if (adjacency_list[i]->color.compare("white") == 0)
			{
				adjacency_list[i]->is_start = true;
				dfs_visit(adjacency_list[i]);
			}
		for (int i = 0; i < adjacency_list.size(); i++)
			if (adjacency_list[i]->color.compare("white") == 0)
			{
				adjacency_list[i]->is_start = true;
				dfs_visit(adjacency_list[i]);
			}
	}

	void print_dfs()
	{
		std::cout << "\n";
		std::cout << "Vertex\t\tParent\t\tDiscovery\tFinish\t\tSource   ";
		for (unsigned int i = 0; i < adjacency_list.size(); i++)
		{
			adjacency_list[i]->is_start ? (std::cout << "\n") : (std::cout << "");
			std::cout << adjacency_list[i]->name << "\t\t" << ((adjacency_list[i]->pi) ? adjacency_list[i]->pi->name : "NULL") << "\t\t";
			std::cout << adjacency_list[i]->distance << "\t\t" << adjacency_list[i]->finish << "\t\t" << (adjacency_list[i]->is_start ? "Yes" : "No") << std::endl;
		}
	}

	// manage leftovers
	~graph()
	{
		for (std::vector<vertex *>::iterator it = adjacency_list.begin(); it != adjacency_list.end(); ++it)
			free(*it);
	}
};