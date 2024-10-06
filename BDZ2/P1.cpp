#include <vector>
#include <iostream>
#include <algorithm>

struct Interval {
    int left;
    int right;

    Interval(int a, int b) : left(a), right(b) {}

    std::size_t length(){
        return right - left + 1;
    }
    Interval overlap(const Interval& other){
        Interval int1 = *this;
        Interval int2 = other;
        if(int1.left > int2.left){
            std::swap(int1,int2);
        }
        if(int1.right < int2.left){
            return Interval(1,0);
        }
        return Interval(int2.left, std::min(int1.right,int2.right));
    }
    bool operator<(Interval& rhs){
        return this->right<rhs.right || (this->right==rhs.right && this->left<rhs.left);
    }
};

std::vector<Interval> v;

void merge(int l,int r){
    int m = (l+r)/2;
    int n1 = m-l;
    int n2 = r-m;
    std::vector<Interval> v1, v2;

    for (int i = 0; i < n1; ++i)
        v1.push_back(v[l + i]);
    for (int j = 0; j < n2; ++j)
        v2.push_back(v[m + j]);

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

void merge_sort(int l, int r){
    if(l+1==r){
        return;
    }
    int m = (l+r)/2;
    merge_sort(l,m);
    merge_sort(m,r);
    merge(l,r);
    return;
}
 

int main() {
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);

    int n;
    std::cin>>n;
    v.reserve(n);
    for(size_t i = 0; i < n; ++i){
        int a,b;
        std::cin>>a>>b;
        v.emplace_back(a,b);
    }

    merge_sort(0,n);

    Interval max_int{1,0};
    for(size_t i = 1; i < n;++i){
        Interval tmp = v[i-1].overlap(v[i]);
        if(tmp.length()>max_int.length()){
            max_int = tmp;
        }
    }

    std::cout<<max_int.length()<<'\n';
    if(max_int.length()>0){
        std::cout<<max_int.left<<' '<<max_int.right<<'\n';
    }
}