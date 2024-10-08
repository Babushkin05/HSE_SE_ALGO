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
        if(int1.left <= int2.right && int2.left <= int1.right){
            return Interval(std::max(int1.left, int2.left), std::min(int1.right,int2.right));
        }
        return Interval{1,0};
    }
    bool operator<(const Interval& rhs) const {
        return this->left<rhs.left || (this->left==rhs.left && this->right<rhs.right);
    }

    void print(){
        std::cout<<left<<' '<<right<<'\n';
    }
};

std::vector<Interval> v;

void merge(int l,int r){
    int m = (l+r)/2;
    int n1 = m-l;
    int n2 = r-m;
    std::vector<Interval> v1(n1,Interval{1,0}), v2(n2,Interval{1,0});

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

void merge_sort(int l, int r){
    if(l+1>=r){ 
        return;
    }
    int m = (l+r)/2;
    merge_sort(l,m);
    merge_sort(m,r);
    merge(l,r);
    return;
}

std::pair<Interval,int> biggest_overlap(int l, int r){

    if(l+1>=r){
        if(l==r) return std::make_pair(Interval{1,0},INT_MIN);
        return std::make_pair(Interval{1,0},v[l].right);
    }

    int m = (l+r)/2;
    std::pair<Interval, int>  left = biggest_overlap(l,m);
    std::pair<Interval, int>  right = biggest_overlap(m,r);
    Interval tmp = {v[m].left,left.second};
    Interval res = {1,0};
    for(int i = m; i<r;++i){
        Interval tt = v[i].overlap(tmp);
        if(res.length()<tt.length()){
            res = tt;
        }
    }

    //left.first.print();
    //right.first.print();
    //tmp.print();
    //std::cout<<'\n';

    if(res.length() <= left.first.length()){
        res = left.first;
    }
    if(res.length() < right.first.length()){
        res = right.first;
    }

    int rght = INT_MIN;
    for(int i = l;i<r;++i){
        rght = std::max(rght,v[i].right);
    }
    
    return std::make_pair(res,rght);
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

    // for(int i = 0; i< n;++i){
    //     for(int j = 0; j < n;++j){
    //         if(v1[i]<v1[j]){
    //             std::swap(v1[i],v1[j]);
    //         }
    //     }
    // }
    // v.push_back(v1[0]);
    // for(size_t i = 1; i< n;++i){
    //     if(v.back().right != v1[i].right){
    //         v.push_back(v1[i]);
    //     }
    //     else if(v.back().left >= v1[i].left){
    //         v.pop_back();
    //         v.push_back(v[i]);
    //     }
    // }
    // for(size_t i = 0; i< v.size() ;++i){
    //     v[i].print();
    // }std::cout<<'\n';

    merge_sort(0,n);
    Interval max_int = biggest_overlap(0,n).first;
    // Interval max_int{1,0};
    // for(size_t i = 0; i < v.size();++i){
    //     for(size_t j = i+1;j<v.size();++j){
    //         if(i==j)
    //         continue;
    //         Interval tmp = v[i].overlap(v[j]);
    //     if(tmp.length()>max_int.length()){
    //         max_int = tmp;
    //     }
    //     }
    // }

    std::cout<<max_int.length()<<'\n';
    if(max_int.length()>0){
        max_int.print();
    }
}