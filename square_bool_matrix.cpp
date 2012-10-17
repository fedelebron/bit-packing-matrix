#include "square_bool_matrix.h"

#include <vector>

using std::vector;

vector<vector<int>> SquareBoolMatrix::square() const {
  vector<vector<int>> squared(n_, vector<int>(n_, 0));
  int m = n_/32;
  for(int i = 0; i < n_; ++i) {
    for(int j = 0; j <= i; ++j) {
      int sum = 0;
      for(int k = m-1; k >= 0; --k) {
        /*int z = 
        cout << "[" <<i << ", " << j << "] z = " << z << " (" << rows_[i][k] << " & " << rows_[j][k] << ")" << endl;
        */
        sum += __builtin_popcount(rows_[i][k] & rows_[j][k]);
      } 
      squared[i][j] = squared[j][i] = sum;
    }
  }
  return squared;
}
