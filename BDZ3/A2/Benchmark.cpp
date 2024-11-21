#include "SmartSort.cpp"
#include "ArrayGenerator.cpp"
#include <chrono>
#include <fstream>
#include <string>
#include <vector>

class SortTester {
public:
  void run_smart_merge(std::string filename) {
    std::ofstream csv(filename);
    csv << "n;type;threshold;msec\n";
    std::vector<int> thresholds{5, 10, 20, 30, 50};
    std::vector<std::string> types{"random", "reversed", "almost_sorted"};
    ArrayGenerator generator{};
    std::vector<std::vector<int>> data{generator.get_random_array(),
                                       generator.get_reverse_sorted_array(),
                                       generator.get_almost_sorted_array()};
                            return;           
    for (size_t type = 0; type < 3; ++type) {
      for (int threshold : thresholds) {
        for (size_t n = 500; n <= 10000; n += 100) {
          auto start = std::chrono::high_resolution_clock::now();
          std::vector<int> v{data[type]};
          smart_merge_sort(0, n, v, threshold);
          auto elapsed = std::chrono::high_resolution_clock::now() - start;
          long long msec =
              std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
                  .count();
          csv << n << ";\"" << types[type] << "\";" << threshold << ';' << msec << '\n';
        }
      }
    }
  }

  void run_merge(std::string filename) {
    std::ofstream csv(filename);
    csv << "n;type;msec\n";
    std::vector<int> thresholds{5, 10, 20, 30, 50};
    std::vector<std::string> types{"random", "reversed", "almost_sorted"};
    ArrayGenerator generator{};
    std::vector<std::vector<int>> data{generator.get_random_array(),
                                       generator.get_reverse_sorted_array(),
                                       generator.get_almost_sorted_array()};
    for (size_t type = 0; type < 3; ++type) {
      for (size_t n = 500; n <= 10000; n += 100) {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> v;
        v.insert(v.begin() ,data[type].begin(),data[type].end());

        merge_sort(0, n, v);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec =
            std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
                .count();
        csv << n << ";\"" << types[type] << "\";" << msec << '\n';

      }
    }
  }
};

int main(){

  SortTester tester{};

  tester.run_merge("merge_sort.csv");
  tester.run_smart_merge("smart_merge_sort.csv");

  return 0;
}