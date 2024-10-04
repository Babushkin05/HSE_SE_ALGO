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
        if(int1.left > int2.right){
            std::swap(int1,int2);
        }
        if(int1.right < int2.left){
            return Interval(1,0);
        }
        return Interval(std::max(int2.left,int1.left), std::min(int1.right,int2.right));
    }
    bool operator<(Interval& rhs){
        return this->right<rhs.right;
    }
};

std::vector<Interval> v;

void merge_sort(int l, int r){
    if(l+1==r){
        return;
    }
    int m = (l+r) >>1;
    merge_sort(l,m);
    merge_sort(m,r);
    for(size_t k = m; k < r; ++k){
        int i = k;
        while(i > l && v[i]<v[i-1]){
            std::swap(v[i],v[i-1]);
            --i;
        }
    }
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