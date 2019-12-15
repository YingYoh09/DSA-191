#include <iostream>  
#include <fstream>
#include <list>
using namespace std;

class Adjacency
{
private:
	int* arr;
	int* weight;
	int size;
public:
	Adjacency() {}
	Adjacency(int v) {
		arr = new int[v];
		weight = new int[v];
		size = 0;
	}
	void init(int v) {
		arr = new int[v];
		weight = new int[v]{};
		size = 0;
	}
	void push(int v) {
		arr[size] = v;
		weight[size] = 1;
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
	int getWeight(int idx) { return weight[idx]; }
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

	void printGraph() {
		for (int v = 0; v < V; ++v)
		{
			cout << "\nAdjacency list of vertex " << v << "\nhead ";
			adj[v].print();
		}
	}

	int minDistance(int dist[], bool sptSet[]);
	
	void dijkstra(int src);
};

int Graph::minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;	
}


// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void Graph::dijkstra(int src)
{
	int *dist = new int[V]; // The output array.  dist[i] will hold the shortest 
	// distance from src to i 

	bool *sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized 

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0 
	dist[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not 
		// yet processed. u is always equal to src in the first iteration. 
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed 
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int j = 0; j < adj[u].getSize(); j++) {
			int v = adj[u].getElement(j);
			// Update dist[v] only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of dist[v] 
			if (!sptSet[v] && dist[u] != INT_MAX
				&& dist[u] + adj[u].getWeight(j) < dist[v])
				dist[v] = dist[u] + adj[u].getWeight(j);
		}
	}

	// print the constructed distance array 
	for (int i = 0; i < V; i++)
	{
		cout << i << " " << dist[i] << endl;
	}
}


int main(int argc, char* argv[]) {
	ifstream inFile;
	int V, source;

	inFile.open("inp.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	inFile >> V >> source;
	Graph g(V);
	Adjacency* arr = new Adjacency(V);
	int v, u;
	try {
		while (inFile >> u) {
			inFile >> v;
			g.addEdge(v, u);
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}
	g.printGraph();
	g.dijkstra(source);
	inFile.close();
	cin.get();
	return 0;
}