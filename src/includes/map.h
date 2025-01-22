class SudokuMap {
public:
  int width = 9;
  int partialWidth = 3;

  SudokuMap();
  SudokuMap(std::vector< std::vector<int> >& _Grid);
  ~SudokuMap();

  void print();
  bool isGridEmpty(int row, int col);
  void assign(int row, int col, int num);

  bool isMapValid();
  bool isNumberInRow(int row, int num);
  bool isNumberInCol(int col, int num);
  bool isNumberInPartial(int row, int col, int num);

private:
  std::vector< std::vector<int> > Grid;
};

SudokuMap::SudokuMap() {};

SudokuMap::SudokuMap(std::vector< std::vector<int> >& _Grid) {
  (*this).Grid = _Grid;
}

void SudokuMap::print() {
  for (int i = 0, mapWidth = (*this).width; i < mapWidth; ++i) {
    for (int j = 0; j < mapWidth; ++j) {
      std::cout << (*this).Grid[i][j] << " \n"[j == mapWidth - 1];
    }
  }
}

bool SudokuMap::isGridEmpty(int row, int col) {
  return (*this).Grid[row][col];
}

void SudokuMap::assign(int row, int col, int num) {
  (*this).Grid[row][col] = num;
}

bool SudokuMap::isNumberInRow(int row, int num) {
  for (int j = 0; j < (*this).width; ++j) {
    if ((*this).Grid[row][j] == num) return true;
  }
  return false;
}

bool SudokuMap::isNumberInCol(int col, int num) {
  for (int i = 0; i < (*this).width; ++i) {
    if ((*this).Grid[i][col] == num) return true;
  }
  return false;
}

bool SudokuMap::isNumberInPartial(int row, int col, int num) {
  const int partialWidth = (*this).partialWidth;

  int startRow = row - row % partialWidth;
  int startCol = col - col % partialWidth;

  for (int i = 0; i < partialWidth; ++i)
      for (int j = 0; j < partialWidth; ++j) {
        if ((*this).Grid[startRow + i][startCol + j] == num)
          return true;
      }
  return false;
}

bool SudokuMap::isMapValid() {
  const int mapWidth = (*this).width;

  std::vector<bool> existed(10, true);

  auto isRowValid = [&](int i) {
    existed.clear();

    for (int j = 0; j < mapWidth; ++j) {
      int gridIJValue = (*this).Grid[i][j];

      if (existed[gridIJValue]) return false;
      existed[gridIJValue] = true;
    }
    return true;
  };

  auto isColumnValid = [&](int j) {
    existed.clear();

    for (int i = 0; i < mapWidth; ++i) {
       int gridIJValue = (*this).Grid[i][j];

       if (existed[gridIJValue]) return false;
       existed[gridIJValue] = true;
    }
    return true;
  };

  auto isPartialStartPoint = [&](int i, int j) {
    return i % partialWidth == 0  && j % partialWidth == 0;
  };

  auto isPartialValid = [&](int i, int j) {
    existed.clear();

    for (int u = i; u < i + partialWidth; ++u)
      for (int v = j; v < j + partialWidth; ++v) {
        int gridUVValue = (*this).Grid[u][v];

        if (existed[gridUVValue]) return false;
        existed[gridUVValue] = true;
      }

    return true;
  };

  for (int i = 0; i < mapWidth; ++i) {
    if (!isRowValid(i)) return false;
  }

  for (int j = 0; j < mapWidth; ++j) {
    if (!isColumnValid(j)) return false;
  }

  for (int i = 0; i < mapWidth; ++i) {
    for (int j = 0; j < mapWidth; ++j) {
      if (!isPartialStartPoint(i, j)) continue;
      if (!isPartialValid(i, j)) return false;
    }
  }

  return true;
}

SudokuMap::~SudokuMap() {}
