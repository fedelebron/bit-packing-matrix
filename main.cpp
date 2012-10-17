#include <iostream>
#include <vector>
#include <chrono>

#include "erdos_renyi.hpp"
#include "square_bool_matrix.h"

using namespace std;

int main(int argc, char** argv) {
  int n;
  if(argc >= 2) n = atoi(argv[1]);
  if(argc < 2 || n <= 0 || n & 0x1F) {
    cerr << "Usage: " << argv[0] << " n" << endl;
    cerr << "n must be a positive multiple of 32." << endl;
    return -1;
  }

  SquareBoolMatrix m = erdos_renyi<SquareBoolMatrix>(n, 0.5);
#ifdef ECHO
  cout << "Matrix:" << endl;
  cout << "-----------------------------" << endl << endl;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      cout << m.get(i, j) << " ";
    }
    cout << endl;
  }
#endif
  vector<vector<int>> normal(n, vector<int>(n, 0));
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      normal[i][j] = int(m.get(i, j));

  auto t1 = chrono::high_resolution_clock::now();
  vector<vector<int>> squared_normal(n, vector<int>(n, 0));
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j <= i; ++j) {
      int sum = 0;
      for(int k = 0; k < n; ++k) 
        sum += normal[i][k] * normal[j][k];
      squared_normal[i][j] = squared_normal[j][i] = sum;
    }
  } 
  auto t2 = chrono::high_resolution_clock::now();

#ifdef ECHO
  cout << endl << "Normal:" << endl;
  cout << "-----------------------------" << endl << endl;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      cout << squared_normal[i][j] << " ";
    }
    cout << endl;
  }
  
  cout << endl << "Compact:" << endl;
  cout << "-----------------------------" << endl << endl;
#endif

  auto t3 = chrono::high_resolution_clock::now();
  auto square = m.square();
  auto t4 = chrono::high_resolution_clock::now();

#ifdef ECHO
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      cout << square[i][j] << " ";
    }
    cout << endl;
  }
#endif
  cout << "Normal:\t\t" << duration_cast<duration<double>>(t2 - t1).count() << " seconds." << endl;
  cout << "Compact:\t" << duration_cast<duration<double>>(t4 - t3).count() << " seconds. " << endl;
}
