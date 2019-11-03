/* Topological sorting Algorithm
    To compile it in Linux (terminal): g++ -o topsorting topsorting.cpp
    To run it in Linux (terminal): ./topsorting G4.in
*/

#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<list>
#include<iostream>

using namespace std;

#define maxVert 50 // define the maximum number of vertices

typedef struct {
    list <int> Adj; // store adjacencies of each vertex
    bool visited;   // to indicate if a vertex is already visited through the program
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
void readFileList(string arquivo, int *n, VertexType Vet[]){
    string line;
    short v,u,i,temp;
    ifstream myfile; // open input file and points to the next element to be read
    myfile.open (arquivo.c_str(),ios::in);
    if (myfile.is_open()){
        i = 0;
        while (myfile.good()){
            i++;
            getline(myfile,line);
            if (i==1) *n=GetStr2Int(line); // number of vertices of the graph; convert string to integer
            else if (line.length()>0){ // vertices of the graph
                temp=line.find_first_of(":");
                v=GetStr2Int(line.substr(0,temp));
                line=line.substr(temp+1);
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
        std::cout << "The vertex " << i << " is adjacent to: ";
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u = *it;
            std::cout << u << ", ";
        }
        std::cout << "\n";
    }
}

// **************************** TOPOLOGICAL SORTING *******************************

// topological sorting based on the DFS
// Also possible to implement it using a structure similar to the adjacency list
void topsorting(int u, int n, VertexType Vet[], list<int> *L){
    int v;

    Vet[u].visited = true;

    // it is iterator used to get all the adjacent vertices of a vertex
    list<int>:: iterator it;
 
    // Get all adjacent vertices of vertex u
    for (it=Vet[u].Adj.begin(); it!=Vet[u].Adj.end(); it++){
        v = *it;
        // if adjacent vertex is still not visited, mark as visited and calls recursion
        if (!Vet[v].visited){
            topsorting(v, n, Vet, L);
        }
    }
    (*L).push_front(u); 
}

// **************************** MAIN *******************************
int main( int argc, char * argv[ ]){
    int n; // number of vertices of the graph
    VertexType Vet[maxVert];
    string arquivo="G4.in";

    readFileList(arquivo,&n,Vet);

    std::cout << "**********\n Adjacencies of the Graph \n**********\n\n";
    writeGraphList(n,Vet);

    std::cout << "\n**********\n Topological Sorting \n**********\n\n";

    // mark all vertices as unvisited
    for(int i = 1; i <= n; i++){
        Vet[i].visited = false;
    }

    // declare a linked list to store the topological sorting
    list<int> L;

    // check if all vertices were already visited
    for(int i = 1; i <= n; i++){
        if (!Vet[i].visited){
            topsorting(i, n, Vet, &L);
        }
    }

    list<int>:: iterator it;
    int v;
 
    // Print the topological sorting of the vertices of the graph
    for (it=L.begin(); it!=L.end(); it++){
        v = *it;
        cout << v << " ";
    }

    std::cout << "\n\n";

    return 0; 
}
