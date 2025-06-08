#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>  
#include <cstdio>   
#include <cmath>    

struct Interval {
    double start;
    double end;
    double weight;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::scanf("%d", &n);

    std::vector<Interval> intervals(n);

    for (int i = 0; i < n; ++i) {
        double b, e, w;
        std::scanf("%lf %lf %lf", &b, &e, &w);
        intervals[i] = {b, e, w};
    }


    std::sort(intervals.begin(), intervals.end(),
              [](const Interval& a, const Interval& b) {
                  return a.end < b.end;
              });

    std::vector<double> ends(n);
    for (int i = 0; i < n; ++i) {
        ends[i] = intervals[i].end;
    }

    auto find_previous = [&](int i) -> int {
        double start_i = intervals[i].start;
        auto it = std::upper_bound(ends.begin(), ends.end(), start_i);
        int pos = int(it - ends.begin()) - 1;
        return pos;
    };

    std::vector<double> dp(n + 1, 0.0);
    for (int i = 1; i <= n; ++i) {
        int j = find_previous(i - 1);
        double option1 = dp[i - 1];
        double option2 = (j >= 0 ? dp[j + 1] : 0.0) + intervals[i - 1].weight;
        dp[i] = std::max(option1, option2);
    }

    std::printf("%.6f\n", dp[n]);

    return 0;
}
