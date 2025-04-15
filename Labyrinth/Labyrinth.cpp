//
// Created by Cz on 4/11/2025.
//

#include "Labyrinth.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>

#include "Queue.h"

using namespace std;

Labyrinth::Labyrinth(const string& filename) {
    ifstream file;
    file.open(filename);
    if (!file) {
        throw std::runtime_error("File not found: " + filename);
    }

    string line;
    vector<vector<char>> tempGrid;
    bool startFound = false;
    int rowIdx = 0;

    while (getline(file,line)) {
        vector<char> row;
        stringstream ss(line);
        string cell;
        int colIdx = 0;

        while (getline(ss, cell, '\t')) {
            if (cell.empty()) continue;
            char symbol = cell[0];
            row.push_back(symbol);

            if (symbol == 'R') {
                start = {rowIdx, colIdx};
                startFound = true;
            }
            colIdx++;
        }

        if (!row.empty()) {
            tempGrid.push_back(row);
            rowIdx++;
        }
    }
    file.close();

    if (tempGrid.empty()) {
        throw std::runtime_error("Labyrinth is empty");
    }
    if (!startFound) {
        throw std::runtime_error("Start position R not found");
    }

    grid = tempGrid;
    rows = grid.size();
    cols = grid[0].size();
}

bool Labyrinth::isValid(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols && (grid[r][c] == '*' || grid[r][c] == 'R')) {
        return true;
    }
    return false;
}

bool Labyrinth::isExit(int r, int c){
    if (grid[r][c] != '*') {
        return false;
    }
    if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
        return true;
    }
    return false;
}

bool Labyrinth::bfs(vector<pair<int, int>>* pathVec) {
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    Queue q;
    int startRow = start.first;
    int startCol = start.second;
    q.push(startRow*cols + startCol);
    visited[startRow][startCol] = true;

    int directionRow[] = {-1, 1, 0, 0};
    int directionCol[] = {0, 0, -1, 1};

    while (!q.isEmpty()) {
        int encodedElem = q.pop();
        int r = encodedElem / cols;
        int c = encodedElem % cols;

        if (isExit(r, c)) {
            if (pathVec) {
                vector<pair<int, int>> path;
                pair<int, int> current = {r, c};
                while (current != make_pair(-1, -1)) {
                    path.push_back(current);
                    current = parent[current.first][current.second];
                }
                reverse(path.begin(), path.end());
                *pathVec = path;
            }
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int newRow = r + directionRow[i];
            int newCol = c + directionCol[i];

            if (isValid(newRow, newCol) && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = {r, c};
                q.push(newRow * cols + newCol);
            }
        }
    }

    return false;
}

bool Labyrinth::dfs(int r, int c, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    if (!isValid(r, c) || visited[r][c]) {
        return false;
    }

    visited[r][c] = true;
    path.emplace_back(r, c);

    if (isExit(r, c)) {
        return true;
    }

    int directionRow[] = {-1, 1, 0, 0};
    int directionCol[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int newRow = r + directionRow[i];
        int newCol = c + directionCol[i];

        if (dfs(newRow, newCol, visited, path)) {
            return true;
        }
    }

    // Backtrack if no path was found through this cell
    path.pop_back();
    return false;
}

bool Labyrinth::hasPath() {
    return bfs(nullptr);  // Just check if a path exists
}

vector<pair<int, int>> Labyrinth::getPath() {
    vector<pair<int, int>> path;
    bfs(&path); // Fills path if one exists
    return path;
}

vector<pair<int, int>> Labyrinth::getPathDFS() {
    vector<pair<int, int>> path;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    dfs(start.first, start.second, visited, path);
    return path;
}

vector<pair<int, int>> Labyrinth::getShortestPath() {
    return getPath();  // In BFS, the first found path is the shortest
}

void Labyrinth::printPath(const vector<pair<int, int>>& path) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    vector<vector<char>> gridCopy = grid;

    for (const auto& [r, c] : path) {
        if (grid[r][c] == 'R') {
            continue;
        }
        gridCopy[r][c] = 'o';
    }

    for (const auto& row : gridCopy) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

void Labyrinth::printPathPair(const vector<pair<int, int>>& path) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    cout << "Path (" << path.size() << " steps):" << endl;
    for (const auto& [r, c] : path) {
        cout << "(" << r << ", " << c << ")" << endl;
    }
}