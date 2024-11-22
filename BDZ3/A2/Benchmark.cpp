#include "SmartSort.cpp"
#include "ArrayGenerator.cpp"
#include <chrono>
#include <fstream>
#include <string>
#include <vector>


class SortTester {
public:
  void run(std::string filename) {
    std::ofstream csv(filename);
    csv << "n;type;threshold;msec\n";
    std::vector<int> thresholds{0, 5, 10, 20, 30, 50};
    std::vector<std::string> types{"random", "reversed", "almost_sorted"};
    ArrayGenerator generator{};
    std::vector<std::vector<int>> data{generator.get_random_array(),
                                       generator.get_reverse_sorted_array(),
                                       generator.get_almost_sorted_array()};          
    for (int threshold : thresholds) {
      for (size_t type = 0; type < 3; ++type) {
        for (size_t n = 500; n <= 10000; n += 100) {
          auto start = std::chrono::high_resolution_clock::now();
          std::vector<int> v{data[type]};
          smart_merge_sort(0, n, v, threshold);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          csv << n << ";\"" << types[type] << "\";" << threshold << ';' << elapsed.count() << '\n';
        }
      }
    }
  }
};

int main(){

  SortTester tester{};

  tester.run("tested_data.csv");

  return 0;
}