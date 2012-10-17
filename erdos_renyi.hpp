#include <random>
#include <chrono>

using namespace std::chrono;

template<typename Matrix> Matrix erdos_renyi(int n, double p) {
  Matrix m(n);
  time_point<system_clock> now = system_clock::now();
  int dur = duration_cast<milliseconds>(now.time_since_epoch()).count();

  std::default_random_engine re(dur);
  std::uniform_real_distribution<double> dist(0, 1);
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < i; ++j) {
      if(dist(re) <= p) {
        m.set(i, j, true);
        m.set(j, i, true);
      }
    }
  }
  return m;
}