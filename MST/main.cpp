#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <limits>

class Graph
{
private:
	int no_vertices;
	std::list<std::pair<int, int>> *lst;

public:
	Graph(int v)
	{
		no_vertices = v;
		lst = new std::list<std::pair<int, int>>[v];
	}

	void add_edge(int u, int v, int weight);
	void MST(int r);
};

void Graph::add_edge(int u, int v, int weight)
{
	lst[u].push_back(std::make_pair(v, weight));
	lst[u].push_back(std::make_pair(u, weight));
}

void Graph::MST(int r)
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > q;

	std::vector<bool> visited(no_vertices, false);
	std::vector<int> key(no_vertices, std::numeric_limits<int>::max());
	std::vector<int> parent(no_vertices, -1);

	int u;

	key[r] = 0;
	q.push(std::make_pair(r, 0));

	while (!q.empty())
	{
		u = q.top().first;
		q.pop();

		visited[u] = true;

		std::list<std::pair<int, int>>::iterator i;
		for (i = lst[u].begin(); i != lst[u].end(); i++)
		{
			int v = (*i).first;
			int weight = (*i).second;

			if (!visited[v] && weight < key[v])
			{
				key[v] = weight;
				q.push(std::make_pair(v, key[v]));
				parent[v] = u;
			}
		}
	}

	std::cout << std::endl << "Minimum Spanning Tree:" << std::endl;
	for (int i = 1; i < no_vertices; i++)
		std::cout << "Edges b/w Vertex " << parent[i] + 1 << " - " << i + 1 << std::endl;
}

int main()
{
	std::cout << "Enter number of vertices: ";
	int n;
	std::cin >> n;

	Graph g(n);

	std::cout << std::endl << "Enter edge and weight";
	std::cout << std::endl << "Ex: If there is a edge between vertex 1 and vertex 2 with Weight 4 then enter 1 2 4" << std::endl;
	char ch;
	do {
		std::cout << std::endl << "Edge with Weight: ";
		int u, v, w;
		std::cin >> u >> v >> w;

		// Set the Edge in the Graph along with the Weight
		g.add_edge(u - 1, v - 1, w);

		std::cout << std::endl << "Add more Edges (Y/N): ";
		std::cin >> ch;

	} while (ch == 'Y' || ch == 'y');

	std::cout << std::endl << "Enter source Vertex: ";
	int src;
	std::cin >> src;

	g.MST(src);
}