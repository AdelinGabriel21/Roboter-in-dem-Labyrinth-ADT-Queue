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