//
// Created by Cz on 4/11/2025.
//

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
#include <vector>

using namespace std;

class Labyrinth {
private:
    vector<vector<char>> grid;
    int rows, cols;
    pair<int, int> start;

    // Checks if a position is valid
    bool isValid(int r, int c);
    // Checks if a position is an exit
    bool isExit(int r, int c);

    // Breadth-first search algorithm
    bool bfs(vector<pair<int, int>>* pathVec = nullptr);
    // Depth-first search algorithm
    bool dfs(int r, int c, vector<vector<bool>>& visited, vector<pair<int, int>>& path);

public:
    Labyrinth(const vector<vector<char>>& grid, const pair<int, int>& start);
    Labyrinth(const string& fileName);

    // Reads the grid from a file
    vector<vector<char>> read_grid_from_file(const string& fileName);

    // Checks if a path exists
    bool hasPath();
    // Returns a path (uses BFS -> always shortest path)
    vector<pair<int, int>> getPath();
    // Returns a path (uses DFS -> not necessarily shortest path)
    vector<pair<int, int>> getPathDFS();
    // Returns the shortest path
    vector<pair<int, int>> getShortestPath();

    //  Prints the path on the grid with 'o' marking the path
    void printPath(const vector<pair<int, int>>& path);
    // Prints the path as pairs of coordinates
    void printPathPair(const vector<pair<int, int>>& path);
};



#endif //LABYRINTH_H
