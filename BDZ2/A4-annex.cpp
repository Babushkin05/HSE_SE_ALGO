#include <vector> 

std::vector<int> v;

void merge(int l,int r){
    int m = (l+r)/2;
    int n1 = m-l;
    int n2 = r-m;
    std::vector<int> v1(n1,0), v2(n2,0);

    for (int i = 0; i < n1; ++i)
        v1[i] = v[l + i];
    for (int j = 0; j < n2; ++j)
        v2[j] = v[m + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (v1[i] < v2[j]) {
            v[k] = v1[i];
            ++i;
        } else {
            v[k] = v2[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        v[k] = v1[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        v[k] = v2[j];
        ++j;
        ++k;
    }
}

int count_inversions(int l, int r){
    int res = 0;
    int m = (l+r)/2;
    int i = l;
    int j = m;
    while(i < m && j < r){
        if(v[i]>v[j]){
            res += j - m + 1;
            ++j;
        }
        else{
            ++i;
        }
    }

    return res;
}

int extended_merge_sort(int l, int r){
    if(l+1>=r){ 
        return 0;
    }
    int m = (l+r)/2;
    int ans = 0;
    ans += extended_merge_sort(l,m);
    ans += extended_merge_sort(m,r);
    ans += count_inversions(l,r);
    merge(l,r);
    return ans;
}
