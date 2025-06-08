#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::pair<int, int>> segments(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> segments[i].first >> segments[i].second;
    }

    std::sort(segments.begin(), segments.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });

    std::vector<int> points;
    int last_point = -1;

    for (int i = 0; i < n; ++i) {
        if (last_point < segments[i].first) {
            last_point = segments[i].second;
            points.push_back(last_point);
        }
    }

    std::cout << points.size() << "\n";
    for (std::size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << (i + 1 < points.size() ? " " : "\n");
    }

    return 0;
}
