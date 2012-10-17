#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
using std::boolalpha;

class SquareBoolMatrix {
 public:
  SquareBoolMatrix(int n) : n_(n), rows_(n, vector<int>(n/32, 0)) {
  }

  inline bool get(int i, int j) {
    return rows_[i][j >> 5] & (1 << (j & 0x1F));
  }

  inline bool set(int i, int j, bool b) {
    return rows_[i][j >> 5] = (rows_[i][j >> 5] & ~(1 << (j & 0x1F))) | (b << (j & 0x1F));
  }

  vector<vector<int>> square() const;

private:
  int n_;
  vector<vector<int>> rows_;
};