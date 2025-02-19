
#include <_stdlib.h>
#include <cassert>
#include <cstring>
#include <iostream>

#include <sstream>
#include <sys/ioctl.h>
#include <sys/ttycom.h>
#include <unistd.h>

using namespace std;

void get_win_sz(struct winsize &ws) {
  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) < 0) {
    cerr << "Error: " << strerror(errno) << endl;
  }
  __builtin_dump_struct(&ws, printf);
}

void populate_distribution(vector<double> &v, const size_t n_bins,
                           size_t n_rand_sums, size_t repeat_count) {
  v.clear();
  v.resize(n_bins + 1);
  for (size_t k = 0; k < repeat_count; k++) {
    for (size_t i = 0; i < n_bins + 1; i++) {
      long double sum = 0;
      for (size_t j = 0; j < n_rand_sums; j++) {
        sum += drand48();
      }
      sum /= n_rand_sums; // Normalize to range between 0....0.999
      sum *= n_bins; // now normalize again to place in one of 0..n_bins - 1
      v[sum]++;
    }
  }
}

void print_vector_vals(const vector<double> &v, const size_t n_rand_sums) {
  const size_t n_bins = v.size();
  cout << "!"; // subplot title starts with '!'
  cout << "histogram for n_rand_sums: " << n_rand_sums << " ";
  cout << "n_bins: " << n_bins << endl;
  cout << "#"; // axes titles start with '#'
  cout << "x,counts" << endl;
  for (size_t i = 0; i < n_bins; i++) {
    cout << (double)i / n_bins << "," << v[i] << endl;
  }
  cout << endl;
}

int main(int argc, const char *argv[]) {
  vector<double> v;
  vector<int> rand_sums = {1, 2, 3, 50};
  size_t n_bins = 1024;
  size_t n_repeat_count = 1024;
  srand48((long)time(nullptr));
  // struct winsize w;
  // get_win_sz(w);
  for (auto i : rand_sums) {
    populate_distribution(v, n_bins, i, n_repeat_count);
    print_vector_vals(v, i);
  }

  return 0;
}

// OPTS: -Wall -O0 -ggdb -g3 -fsanitize=address -std=c++17
// COMPILER: clang++
