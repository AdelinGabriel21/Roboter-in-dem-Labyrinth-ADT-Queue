//
// Created by Cz on 4/11/2025.
//
#include <iostream>
#include <fstream>
#include "Queue/App.h"
#include "Labyrinth/Labyrinth.h"

using namespace std;

int main(){
      main_queue();
      try {
            Labyrinth lab(R"(C:\Users\adeli\Documents\Adelin\Facultate\Anul I\Semestrul II\DSA\Laborator\L3\Labyrinth\labyrinth.txt)");

            if (lab.hasPath()) {
                  cout << "Path exists from start to exit.\n\n";

                  vector<pair<int, int>> path = lab.getShortestPath();  // or lab.getPath()
                  cout << "Shortest path (marked with 'o'):\n";
                  lab.printPath(path);
            } else {
                  cout << "No path exists.\n";
            }

      } catch (const std::exception& e) {
            cerr << "Error: " << e.what() << endl;
      }

      return 0;
}