/* Example of how to read a graph from an input file (the format is set by the programmer) and 
store it into an adjacency list and into an adjacency matrix.
    To compile in Linux (terminal): g++ -o program program.cpp
    To run in Linux (terminal): ./program G1.in
*/

#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cmath>
#include<list>
#include<iostream>
using namespace std;

#define maxVert 50

typedef struct {
    list <int> Adj; // to store adjacencies
    } VertexType;

VertexType Vet[maxVert];
int M[maxVert][maxVert];
int n;

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

// **************************** ADJACENCY LIST *******************************

// Read the input file
void readFileList(string fileName){
    string line;
    short v,u,i,temp;
    ifstream myfile; // open input file and points to the next element to be read
    myfile.open (fileName,ios::in);
    if (myfile.is_open()){
        i = 0;
        while (myfile.good()){
            i++;
            getline(myfile,line);
            if (i==1) n = GetStr2Int(line); // number of vertices of the graph; convert string to integer
            else if (line.length()>0){ // vertices of the graph
                temp = line.find_first_of(":");
                v = GetStr2Int(line.substr(0,temp));
                line = line.substr(temp+1);
                while (line.length() > 1){
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

// Write the graph stored in the adjacency list
void writeGraphList(){
    int u;
    list<int>:: iterator it;
    for(int i=1; i<=n; i++){
        cout << "Vertex " << i << " is adjacent to ";
        for (it=Vet[i].Adj.begin(); it!=Vet[i].Adj.end(); it++){
            u = *it;
            cout << u << ", ";
        }
        cout << "\n";
    }
}


// **************************** ADJACENCY MATRIX *******************************
void readFileMatrix(string fileName){
    string line;
    short v,u,i,temp;
    ifstream myfile; // open input file and points to the next element to be read
    myfile.open(fileName,ios::in);
    
    // initialize the matrix with 0's
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            M[i][j] = 0;
        }
    }

    if (myfile.is_open()){
        i = 0;
        while (myfile.good()){
            i++;
            getline(myfile, line);
            if (i==1) n = GetStr2Int(line); // number of vertices of the graph; convert string to integer
            else if (line.length() > 0){ // vertices of the graph
                temp = line.find_first_of(":");
                v = GetStr2Int(line.substr(0,temp));
                line = line.substr(temp+1);
                while (line.length() > 1){
                    temp = line.find_first_of(",");
                    u = GetStr2Int(line.substr(0,temp));
                    line = line.substr(temp+1);
                    M[v][u] = 1;
                    M[u][v] = 1;
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

// Write the graph stored in the adjacency matrix
void writeGraphMatrix(){
    for(int i=1; i<=n; i++){
        cout << "Vertex " << i << " is adjacent to ";
        for(int j=1; j<=n; j++){
            if (M[i][j]==1){
                cout << j << ", ";
            }
        }
        cout << "\n";
    }
}

// **************************** MAIN *******************************
int main( int argc, char * argv[ ]){
    string fileName = argv[1]; // it takes the name of the file as a parameter

    cout << "**********\n Graph from the adjacency list:\n**********\n\n";
    readFileList(fileName);
    writeGraphList();

    cout << "\n**********\n Graph from the adjacency matrix:\n**********\n\n";
    readFileMatrix(fileName);
    writeGraphMatrix();
    return 0; 
}
