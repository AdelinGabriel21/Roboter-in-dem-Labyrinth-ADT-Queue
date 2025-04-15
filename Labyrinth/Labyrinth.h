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

    bool isValid(int r, int c);
    bool isExit(int r, int c);

    bool bfs(vector<pair<int, int>>* pathVec = nullptr);
    bool dfs(int r, int c, vector<vector<bool>>& visited, vector<pair<int, int>>& path);

public:
    Labyrinth(const string& fileName);

    bool hasPath();
    vector<pair<int, int>> getPath();
    vector<pair<int, int>> getPathDFS();
    vector<pair<int, int>> getShortestPath();

    void printPath(const vector<pair<int, int>>& path);
    void printPathPair(const vector<pair<int, int>>& path);
};



#endif //LABYRINTH_H
