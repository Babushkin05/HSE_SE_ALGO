#include <vector>

int fast_find_max_sum(const std::vector<int>& arr, int k) {
    int n = arr.size();
    int max_sum = INT_MIN;
    int cur_sum = 0;

    for(size_t i = 0; i < k; ++i){
        cur_sum+=arr[i];
    }

    max_sum = std::max(max_sum,cur_sum);

    for(size_t i = k; i< n; ++i){
        cur_sum-=arr[i-k];
        cur_sum+=arr[i];
        max_sum = std::max(max_sum,cur_sum);
    }

    return max_sum;
}