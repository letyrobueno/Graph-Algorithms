/* Depth-First Search (DFS) Algorithm
   To compile it in Linux (terminal): g++ -o dfs dfs.cpp
   To run it in Linux (terminal): ./dfs G3.in
*/

#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<list>
#include<iostream>
#include<climits> // for using INT_MAX
using namespace std;

#define maxVert 50 // define the maximum number of vertices

typedef struct {
    list <int> Adj; // store adjacencies of each vertex
    bool visited;   // to indicate if a vertex is already visited through the DFS
    int p;          // parent/predecessor of the vertex in the DFS
    int d;          // DFS number: the order in which the vertices were visited
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
    short v, u, i, temp;
    ifstream myfile; // open input file and points to the next element to be read
    myfile.open (fileName.c_str(), ios::in);
    if (myfile.is_open()){
        i = 0;
        while (myfile.good()){
            i++;
            getline(myfile,line);
            if (i==1) *n = GetStr2Int(line); // number of vertices of the graph; convert string to integer
            else if (line.length()>0){ // vertices of the graph
                temp = line.find_first_of(":");
                v = GetStr2Int(line.substr(0,temp));
                line = line.substr(temp+1);
                while (line.length()>1){
                    temp = line.find_first_of(",");
                    u = GetStr2Int(line.substr(0,temp));
                    line = line.substr(temp+1);
                    Vet[v].Adj.push_back(u);
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
    for(int i=1; i<=n; i++){
        cout << "The vertex " << i << " is adjacent to: ";
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u = *it;
            cout << u << ", ";
        }
        cout << "\n";
    }
}

// **************************** DEPTH-FIRST SEARCH *******************************

// DFS starting from vertex s
void dfs(int u, int n, VertexType Vet[], int *cont){
    int v;

    Vet[u].visited = true;
    Vet[u].d = *cont;
    cout << "DFS called for the vertex " << u << " - Value of cont: " << Vet[u].d << "\n";

    // it is iterator used to get all the adjacent vertices of a vertex
    list<int>:: iterator it;
 
    // Get all adjacent vertices of vertex u
    for (it=Vet[u].Adj.begin(); it!=Vet[u].Adj.end(); it++){
        v = *it;
        // if adjacent vertex is still not visited, mark as visited and calls recursion
        if (!Vet[v].visited){
            Vet[v].p = u; // mark as visited
            (*cont)++;
            dfs(v, n, Vet, cont);
        }
    }
}

// **************************** MAIN *******************************
int main( int argc, char * argv[ ]){
    int n; // number of vertices of the graph
    VertexType Vet[maxVert];
    
    string fileName = argv[1]; // it takes the name of the file as a parameter
    readFileList(fileName, &n, Vet);

    cout << "**********\n Adjacencies of the Graph \n**********\n\n";
    writeGraphList(n, Vet);

    // mark all vertices as unvisited and with no predecessor
    for(int i = 1; i<=n; i++){
        Vet[i].visited = false;
        Vet[i].p = -1;
        Vet[i].d = INT_MAX;
    }
    int cont = 1;

    cout << "\n**********\n Depth-First Search \n**********\n\n";
    dfs(1, n, Vet, &cont);
    cout << "\n\n";

    return 0; 
}
