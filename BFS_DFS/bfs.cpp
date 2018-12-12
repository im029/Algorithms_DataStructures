#include "helpers/graph.h"
#include <stdlib.h>

int main(void)
{
	std::cout << "How many vertices are there in graph?" << std::endl;
	int n; 
	std::cin >> n;

	graph g;
	
	for (int i = 0; i < n; i++)
	{
		std::string vertex_name = "V" + std::to_string(i + 1);
		g.add_vertex(vertex_name);
	}

	// get the edges (if any)
	std::cout << std::endl;
	std::cout << "We will now add edges. Please note that if the graph is undirected you have add the reciprocal edge manually";
	std::cout << "\nfor example if there is an edge 1 2, then you have to enter 2 1 manually in case of undirected graph." << std::endl;
	std::cout << "Do you want to add any edges to graph (Y/N)?";
	char  ch;
	std::cin >> ch;

	while (ch == 'Y' || ch == 'y')
	{
		std::cout << "Enter pair of connected vertices (1 2 if vertex 1 is connected to 2): ";

		int v1;
		std::cin >> v1;
		int v2;
		std::cin >> v2;

		// discard invalid edges
		if (v1 > n || v1 <= 0)
		{
			std::cout << "Invalid Edge. Vertex " << v1 << " is not in graph. Edge will be ignored" << std::endl;
			std::cout << "Enter more edges(Y/N)?";
			std::cin >> ch;
			continue;
		}
		if (v2 > n || v2 <= 0)
		{
			std::cout << "Invalid Edge. Vertex " << v2 << " is not in graph. Edge will be ignored" << std::endl;
			std::cout << "Enter more edges(Y/N)?";
			std::cin >> ch;
			return -1;
		}
		// add the edge
		g.add_edge(v1 - 1, v2 - 1);

		std::cout << "Enter more edges(Y/N)?";
		std::cin >> ch;
	}

	system("cls");

	std::cout << "\nWe will now do BFS on the graph. Please select a source node: ";
	int source;
	std::cin >> source;

	// check if source vertex is in graph
	if (source <= 0 || source > n)
	{
		std::cout << "Source Vertex not in graph. Exiting" << std::endl;
		system("pause");
		return -1;
	}

	system("cls");

	std::cout << "Adjancency List for graph" << std::endl;
	g.print();

	g.bfs(source);

	g.print_bfs();

	system("pause");
}