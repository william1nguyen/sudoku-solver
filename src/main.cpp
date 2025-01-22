#include <iostream>
#include <vector>

#include "includes/map.h"
#include "includes/solver.h"

int main() {
  std::vector < std::vector<int> > vecMap = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
  };

  SudokuMap map = SudokuMap(vecMap);
  SudokuSolver solver = SudokuSolver();

  bool valid = solver.solveSudoku(map, 0, 0);
  if (!valid) {
    std::cout << "There is no solution exist\n";
    return 1;
  }

  map.print();
  return 0;
}
