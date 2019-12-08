#include <iostream>  
#include <fstream>
using namespace std;

class Adjacency
{
private:
	int* arr;
	int size;
public:
	Adjacency() {}
	Adjacency(int v) {
		arr = new int[v];
		size = 0;
	}
	void init(int v) {
		arr = new int[v];
		size = 0;
	}
	void push(int v) {
		arr[size] = v;
		size++;
	}
	void print() {
		for (int i = 0; i < size; i++) {
			cout << "-> " << arr[i];
		}
		cout << endl;
	}
	void printArray() {
		for (int i = 0; i < size - 1; i++) {
			cout << arr[i] << " ";
		}
		cout << arr[size - 1] << endl;
	}
	int getSize() { return size; }
	int getElement(int idx) { return arr[idx]; }
};

class Graph
{
private:
	int V;
	Adjacency* adj;

public:
	Graph(int V) {
		this->V = V;
		adj = new Adjacency[V];
		for (int i = 0; i < V; i++) {
			adj[i].init(V);
		}
	}

	void addEdge(int v, int w)
	{
		adj[v].push(w);
		adj[w].push(v);
	}

	void DFSUtil(int v, bool visited[], Adjacency* arr);
	Adjacency* DFS(int v);

	void printGraph() {
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}
};

void Graph::DFSUtil(int v, bool visited[], Adjacency* arr) {
	//Use Adjacency->push(...) to add v to Adjacency
	//Use Adjacency->getSize() to get number of element in Adjacency list
	//Use Adjacency->getElement(index) to access to Adjacency list
	// TODO
	visited[v] = true;

	arr->push(v);
	
	for (int i = 0; i < adj[v].getSize();i++)
	{
		if (!visited[adj[v].getElement(i)])
			DFSUtil(adj[v].getElement(i), visited, arr);
	}
	
}

Adjacency* Graph::DFS(int v) {
	Adjacency* arr = new Adjacency(V);

	bool* visited = new bool[V]{};
	DFSUtil(v, visited, arr);
	
	delete[] visited;
	visited = NULL;
	return arr;
}

int main(int argc, char* argv[]) {
	ifstream inFile;
	int V, visited;
	inFile.open("inp.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	inFile >> V >> visited;
	Graph g(V);
	Adjacency* arr = new Adjacency(V);
	int v, u;
	try {
		while (inFile >> u) {
			inFile >> v;
			g.addEdge(u, v);
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}
	g.printGraph();
	arr = g.DFS(visited);
	arr->printArray();
	inFile.close();
	return 0;
}