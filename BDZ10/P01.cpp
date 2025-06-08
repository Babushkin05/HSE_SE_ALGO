#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Story {
    long long c; 
    long long w;

    bool operator<(const Story& other) const {
        return (double)c / w > (double)other.c / other.w;
    }
};

int main() {
    int n;
    long long W;
    std::cin >> n >> W;

    std::vector<Story> stories(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> stories[i].c >> stories[i].w;
    }

    std::sort(stories.begin(), stories.end());

    double totalDiscussionDays = 0.0;
    long long remainingTime = W;

    for (int i = 0; i < n && remainingTime > 0; ++i) {
        if (stories[i].w <= remainingTime) {
            totalDiscussionDays += stories[i].c;
            remainingTime -= stories[i].w;
        } else {
            totalDiscussionDays += (double)stories[i].c * remainingTime / stories[i].w;
            remainingTime = 0;
        }
    }

    std::cout << std::fixed << std::setprecision(3) << totalDiscussionDays << "\n";

    return 0;
}
