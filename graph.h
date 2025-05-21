//
// Created by nourh on 5/4/2025.
//

#ifndef GRAPH_H
#define GRAPH_H




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

// This is a specific implementation of the graph data structure in the limited scope of using dijkstra
// algorithim to find the shortest path from one city to another


class Graph {
public:
    Graph();
    ~Graph();

    void createGraph(const std::string& filename);
    void dijkstra(int src, int dest);
    void printLocation(int node) const;

private:
    int rows;
    std::vector<std::vector<int>> adjMatrix;

    int smallestUnknownVertex(const std::vector<int>& dist, const std::vector<bool>& known) const;
    void printPath(const std::vector<int>& dist, const std::vector<int>& path, int src, int dest) const;

};

#endif
// GRAPH_H

