#include<iostream> 
#include <list> 
#include <limits.h> 
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

class Graph
{
	int V;
	list<int>* adj;
	bool isCyclicUtil(int v, bool visited[], bool* rs);
public:
	Graph(int V);
	void addEdge(int v, int w);
	bool isCyclic();
	Graph() {
		V = 0;
		adj = NULL;
	}
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
	if (visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack 
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex 
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if (!visited[*i] && isCyclicUtil(*i, visited, recStack))
				return true;
			else if (recStack[*i])
				return true;
		}

	}
	recStack[v] = false;  // remove the vertex from recursion stack 
	return false;
}

bool Graph::isCyclic()
{
	// TODO
	bool* visited = new bool[V] {};
	bool* recStack = new bool[V] {};
	for (int i = 0; i < V; i++)
	{
		bool res = false;
		if (!visited[i] && isCyclicUtil(i, visited, recStack))
			return true;
	}
	return false;
}

int main(int argc, char** argv)
{
	ifstream inFile;
	string input;

	inFile.open("inp.txt");

	if (!inFile)
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}

	Graph g;
	int numNodes;
	int count = 0;
	while (getline(inFile, input))
	{
		if (count == 0) { numNodes = stoi(input); g = (numNodes); count++; continue; }
		stringstream s(input);
		int src, dst;
		s >> src >> dst;
		g.addEdge(src, dst);
	}

	if (g.isCyclic())
		cout << "Graph contains cycle";
	else
		cout << "Graph doesn't contain cycle";

	return 0;
}
