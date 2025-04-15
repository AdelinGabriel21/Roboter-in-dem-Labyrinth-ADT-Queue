//
// Created by Cz on 4/15/2025.
//

#include "ShortTestLabyrinth.h"
#include "Labyrinth.h"
#include <cassert>

using namespace std;


void test_all_labyrinth(){
     Labyrinth labyrinth(R"(C:\Users\Cz\Documents\Facultate\Sem2\DSA\Laborator\L3\Labyrinth\labyrinth.txt)");
     assert (labyrinth.hasPath() == true);

     try {
          Labyrinth lab(R"(C:\Users\Cz\Documents\Facultate\Sem2\DSA\Laborator\L3\Labyrinth\labyrinth.txt)");

          if (lab.hasPath()) {
               cout << "Path exists from start to exit.\n\n";

               vector<pair<int, int>> path = lab.getShortestPath();  // or lab.getPath()
               cout << "Shortest path (marked with 'o'):\n";
               lab.printPath(path);
          } else {
               cout << "No path exists.\n";
          }

     } catch (const exception& e) {
          cerr << "Error: " << e.what() << endl;
     }
}