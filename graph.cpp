#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;
// Defining a very large value to mimic infinity
const int INF = 1e9;

// constructor defining the number of dimensions of the matrix to zero by zero
Graph::Graph() : rows(0) {}

Graph::~Graph() {}

// this function reads the text file and according to the type of graph updates the adjacency matrix accordingly
void Graph::createGraph(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    getline(inputFile, line);
    bool weighted = (line.find("W") != string::npos || line.find("w") != string::npos);
    bool directed = (line.find("DG") != string::npos || line.find("dg") != string::npos);

    getline(inputFile, line);
    istringstream dimStream(line);
    dimStream >> rows;

    adjMatrix.assign(rows, vector<int>(rows, INF));

    
// read the weight if the graph is weighted
    while (getline(inputFile, line)) {
        istringstream edgeStream(line);
        int x, y, val = 1;
        if (weighted)
            edgeStream >> x >> y >> val;
        else
            edgeStream >> x >> y;

        if (x >= 0 && x < rows && y >= 0 && y < rows) {
            adjMatrix[x][y] = val;
            if (!directed)
                adjMatrix[y][x] = val;
        } else {
            cerr << "Invalid edge: " << x << " -> " << y << endl;
        }
    }
}

// the definition of the dijkstra algorithim

void Graph::dijkstra(int src, int dest) {
    // first initialzie the matrices
    vector<int> dist(rows, INF);
    vector<int> path(rows, -1);
    vector<bool> visited(rows, false);
    // define a min-heap priority queue: (distance, vertex) to find the closest neighbour easily
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    // Pop the root of the heap each time, and check the nodes connected to it.
    

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
// if they are visited dont go. if not explore them
 // explore the neigbours and update the distances to be the smallest possible       
        for (int v = 0; v < rows; ++v) {
            if (adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                path[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    printPath(dist, path, src, dest);
}

// using the previous predecessor vector we defined, we reconstruct the path between two nodes.

void Graph::printPath(const vector<int>& dist, const vector<int>& path, int src, int dest) const {
    if (dist[dest] == INF) {
        cout << "No path from ";
        printLocation(src);
        cout << " to ";
        printLocation(dest);
        cout << "\n";
        return;
    }

    vector<int> fullPath;
    for (int at = dest; at != -1; at = path[at])
        fullPath.push_back(at);

    cout << "\nRoute: ";
    for (auto it = fullPath.rbegin(); it != fullPath.rend(); ++it) {
        if (it != fullPath.rbegin()) cout << " --> ";
        printLocation(*it);
    }

    cout << "\n\n Distance covered is " << dist[dest] << " meters\n";
}

// a simple function to print the locations on AUC campus
void Graph::printLocation(int node) const {
    static const vector<string> nodeNames = {
        "AUC Library",                                // 0
        "School of Sciences and Engineering",         // 1
        "Prince Alwaleed Bin Talal Hall",             // 2
        "Hatem and Janet Mostafa Core Center",        // 3
        "Graduate School of Education",               // 4
        "Administration Building",                    // 5
        "Research Centers Building",                  // 6
        "AUC Center for the Arts",                    // 7
        "Bassily Auditorium",                         // 8
        "Moataz Al Alfi Hall",                        // 9
        "Allam Amphitheater",                         //10
        "University Residences",                      //11
        "Campus Center",                              //12
        "Conference & Visitor Center",                //13
        "AUC Sports Center",                          //14
        "Paul and Charlotte Corddry Park",            //15
        "University Garden",                          //16
        "Bruce Ludwig Family Square",                 //17
        "Pepsi Entrance",                             //18
        "Bus Terminal"                                //19
    };

    if (node >= 0 && node < (int)nodeNames.size())
        cout << nodeNames[node];
    else
        cout << "Unknown Location";
}

// The following function is no longer needed but kept for compatibility
int Graph::smallestUnknownVertex(const vector<int>&, const vector<bool>&) const {
    return -1;
}
