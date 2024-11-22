#include "ArrayGenerator.cpp"
#include "sortings.cpp"
#include <chrono>
#include <fstream>
#include <string>

class tester {
public:
  void run(std::string filename) {
    std::ofstream csv{filename};
    csv << "n;array_type;sorting_type;time\n";

    std::vector<std::string> types{"random", "reversed", "almost_sorted"};
    ArrayGenerator generator{};
    std::vector<std::vector<int>> data{generator.get_random_array(),
                                       generator.get_reverse_sorted_array(),
                                       generator.get_almost_sorted_array()};

    for (size_t type = 0; type < types.size(); ++type) {
      for (size_t n = 1000; n <= 100000; n += 1000) {
        std::vector<int> v{data[type]};
        auto start = std::chrono::high_resolution_clock::now();
        quick_sort(v, 0, n);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        csv << n << ";\"" << types[type] << ";\"quick\";" << elapsed.count()
            << '\n';
      }
    }

    for (size_t type = 0; type < types.size(); ++type) {
      for (size_t n = 1000; n <= 100000; n += 1000) {
        std::vector<int> v{data[type]};
        auto start = std::chrono::high_resolution_clock::now();
        intro_sort(v);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        csv << n << ";\"" << types[type] << ";\"intro\";" << elapsed.count()
            << '\n';
      }
    }
  }
};

int main() {
  tester test{};
  test.run("tested_data.csv");
}