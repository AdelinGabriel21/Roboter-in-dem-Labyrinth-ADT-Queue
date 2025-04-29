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

          if (lab.hasPath()) { // d)
               cout << "Path exists from start to exit.\n\n";

               // e)
               vector<pair<int, int>> path = lab.getPath();
               cout << "Path (marked with 'o'):\n";
               lab.printPathPair(path);
               cout << "\n";
               lab.printPath(path);
               cout << "\n\n";

               // f)
               vector<pair<int, int>> path1 = lab.getShortestPath();  // or lab.getPath()
               cout << "Shortest path (marked with 'o'):\n";
               lab.printPathPair(path1);
               cout << "\n";
               lab.printPath(path1);
               cout << "\n\n";

               // extra - random path with DFS
               vector<pair<int, int>> path2 = lab.getPathDFS();
               cout << "A path (marked with 'o'):\n";
               lab.printPathPair(path2);
               cout << "\n";
               lab.printPath(path2);
          } else {
               cout << "No path exists.\n";
          }

     } catch (const exception& e) {
          cerr << "Error: " << e.what() << endl;
     }

     vector<vector<char>> grid = {
          {'X', 'X', 'X', 'X', 'X'},
          {'X', 'R', '*', '*', 'X'},
          {'X', '*', 'X', '*', 'X'},
          {'X', '*', '*', '*', 'X'},
          {'X', 'X', 'X', 'X', 'X'}
     };
     Labyrinth lab1 =Labyrinth(grid, {2, 2});
     assert (lab1.hasPath() == false);
}
