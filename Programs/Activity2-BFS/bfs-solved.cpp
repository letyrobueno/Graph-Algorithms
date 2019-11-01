/* Breadth-First Search (BFS) Algorithm
	To compile it in Linux (terminal): g++ -o bfs-solved bfs-solved.cpp
	To run it in Linux (terminal): ./bfs-solved G1.in
*/

#include <stdlib.h>
#include<fstream>
#include<sstream>
#include<list>
#include<iostream>
using namespace std;

#define maxVert 50

typedef struct {
	list <int> Adj;		// to store adjacencies
	bool visited; 		// to indicate if a vertex is already visited through the BFS
	int predecessor;	// predecessor of the vertex in the BFS
	} VertexType;

// **************************** GENERAL-PURPOSE FUNCTIONS *******************************

// Convert string to integer
int GetStr2Int(string strConvert) {
	int intReturn;
	intReturn = atoi(strConvert.c_str());
	return(intReturn);
}

// Convert integer to string
string GetInt2Str(int intConvert) {
	stringstream out;
	out << intConvert;
	return(out.str());
}

// **************************** READING THE INPUT FILE *******************************

// Read the input file storing the vertices and their adjacencies in an adjacency list called Vet
// the variable n is sent by reference (not by value), because it's modified in the method
void readFileList(string fileName, int *n, VertexType Vet[]){
	string line;
	short v,u,i,temp;
	ifstream myfile; // open input file and points to the next element to be read
  	myfile.open (fileName.c_str(),ios::in);
	if (myfile.is_open()){
		i = 0;
		while (myfile.good()){
			i++;
			getline(myfile,line);
			if (i==1) *n=GetStr2Int(line); // number of vertices of the graph; convert string to integer
			else if (line.length()>0){ // vertices of the graph
				temp = line.find_first_of(":");
				v = GetStr2Int(line.substr(0,temp));
				line = line.substr(temp+1);
				while (line.length()>1){
					temp = line.find_first_of(",");
					u = GetStr2Int(line.substr(0,temp));
					line = line.substr(temp+1);
					Vet[v].Adj.push_back(u);
					Vet[u].Adj.push_back(v);
				}
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

// **************************** FUNCTIONS OVER THE ADJACENCY LIST *******************************

// Read the adjacency list Vet and "print" its content to the user
void writeGraphList(int n, VertexType Vet[]){
	int u;
	list<int>:: iterator it;
	for(int i=1;i<=n;i++){
		std::cout << "The vertex " << i << " is adjacent to: ";
		for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
			u = *it;
			std::cout << u << ", ";
		}
		std::cout << "\n";
	}
}

// **************************** BREADTH-FIRST SEARCH *******************************

// BFS starting from the vertex s
void bfs(int s, int n, VertexType Vet[]){
	int u;

	// set all vertices as not visited and without predecessor
    for(int i = 1; i <= n; i++){
        Vet[i].visited = false;
		Vet[i].predecessor = -1;
 	}
	Vet[s].predecessor = s; // the initial vertex is its predecessor itself

    // create a linked list to be used as queue
    list<int> queue;
 
    // set the current vertex as "visited"
    Vet[s].visited = true;
    queue.push_back(s); // enqueue a vertex, i.e., add the vertex at the end of the queue

   // it is iterator used to get all the adjacent vertices of a vertex
    list<int>:: iterator it;
 
    while(!queue.empty()){ // as long as the queue is not empty:
        // dequeue a vertex and print it
        s = queue.front(); // get the first element of the list
        queue.pop_front(); // remove it from the list
 
        // Get all adjacent vertices of the "dequeued" vertex
		for (it=Vet[s].Adj.begin(); it!=Vet[s].Adj.end(); it++){
			u = *it;
			// if the adjacent vertex is not visited, set it as visited and enqueue it
			if (!Vet[u].visited){
				Vet[u].visited = true; // set as visited
				Vet[u].predecessor = s; // store its predecessor vertex
				queue.push_back(u); // enqueue it
			}
		}
    }
}

// Using the BFS, print the shortest path from a vertex s to the other vertices also giving their lengths
void print_min_paths(int s, int n, VertexType Vet[]){
	int cont, m, p;

	// list all shortest paths from s (backwards)
    for(int i=1; i<=n; i++){ 
		// for all vertices, except the starting vertex since the shortest path to itself is 0
		if (i!=s){ 
			m = Vet[i].predecessor;
			cout << "Path: " << i << " " << m << " ";

			cont = 1;
			while (m!=s){
				p = Vet[m].predecessor;	
				cout << p << " ";
				m = p;
				cont++;
			}
			cout << " - Length of the path: " << cont << "\n";
		}
 	}
}

// Verify if a graph is connected
bool isConnected(int n, VertexType Vet[]){
    for(int i=1; i<=n; i++){
		if (!Vet[i].visited) return false;
	}
	return true;
}

// **************************** MAIN *******************************
int main(int argc, char * argv[ ]){
	int n; // number of vertices of the graph
	VertexType Vet[maxVert];

	string fileName = argv[1]; // it takes the name of the file as a parameter
	readFileList(fileName, &n, Vet);

	std::cout << "**********\n Adjacencies of the Graph \n**********\n\n";
	writeGraphList(n, Vet);

	std::cout << "**********\n Breadth-first search\n**********\n\n";
	bfs(1, n, Vet);
	print_min_paths(1, n, Vet);

	std::cout << "\n The graph is connected? " << ((isConnected(n,Vet)==1)?"Yes":"No") << "\n";

	return 0; 
}
