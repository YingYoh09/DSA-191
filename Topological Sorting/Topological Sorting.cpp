#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<list>
using namespace std;

class Graph
{
	int V;

	list<int>* adj;

	vector<int> indegree;

	void alltopologicalSortUtil(vector<int>& res, bool visited[]);

public:
	Graph(int V);

	void addEdge(int v, int w);

	void alltopologicalSort();
	Graph() {
		V = 0;
		adj = NULL;
	}
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	for (int i = 0; i < V; i++)
		indegree.push_back(0);
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);

	indegree[w]++;
}

void Graph::alltopologicalSortUtil(vector<int>& res, bool visited[])
{
	// TODO
	list<int> queue;
	for (int i = 0; i < V; i++)
	{
		if (indegree[i] == 0)
		{
			queue.push_back(i);
		}
	}
	
	while (!queue.empty())
	{
		int v = queue.front();
		queue.pop_front();
		visited[v] = true;
		
		for (auto i: adj[v])
		{
			--indegree[i];
			if (indegree[i] == 0)
			{
				queue.push_back(i);
			}
		}
	}
}

void Graph::alltopologicalSort()
{
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	vector<int> res;
	alltopologicalSortUtil(res, visited);
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

	cout << "All Topological sorts\n";

	g.alltopologicalSort();

	return 0;
}
