class SudokuSolver {
public:
  SudokuSolver();
  ~SudokuSolver();

  bool solveSudoku(SudokuMap& map, int row, int col);

private:
  bool isSafe(SudokuMap& map, int row, int col, int num);
};

SudokuSolver::SudokuSolver() {}

bool SudokuSolver::isSafe(SudokuMap& map, int row, int col, int num) {
  if (map.isNumberInRow(row, num))
    return false;

  if (map.isNumberInCol(col, num))
    return false;

  if (map.isNumberInPartial(row, col, num))
    return false;

  return true;
}

bool SudokuSolver::solveSudoku(SudokuMap& map, int row, int col) {
  if (row == map.width - 1 && col == map.width) {
    return true;
  }

  if (col == map.width) {
    ++row, col = 0;
  }

  if (map.isGridEmpty(row, col)) {
    return solveSudoku(map, row, col + 1);
  }

  for (int num = 1; num <= 9; ++num) {
    if (isSafe(map, row, col, num)) {
      map.assign(row, col, num);

      if (solveSudoku(map, row, col + 1))
        return true;
    }

    map.assign(row, col, 0);
  }

  return false;
}

SudokuSolver::~SudokuSolver() {}
