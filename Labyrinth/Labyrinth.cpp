//
// Created by Cz on 4/11/2025.
//

#include "Labyrinth.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <fstream>

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
            cout << cell << '\t';
        }
        cout << endl;
    }
}