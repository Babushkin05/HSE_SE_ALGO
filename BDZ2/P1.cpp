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
        return Interval(int2.left, std::min(int1.right,int2.right));
    }
    bool operator<(Interval& rhs){
        return this->right-rhs.right + this->length() - rhs.length() < 0;
    }
};

bool custom_comp(Interval& lhs,Interval& rhs){
        return lhs.right-rhs.right + lhs.length() - rhs.length() < 0;
}

std::vector<Interval> v;

void Sorting(int l, int r){
    if(l==r+2){
        if(v[l] < v[l+1]){
            std::swap(v[l],v[l+1]);
        }
        return;
    }
    int m = l+r >>1;
    Sorting()
}

Interval max_overlap(int l, int r){
    if(l+2==r){
        return v[l].overlap(v[l+1]);
    }
    if(l+1==r){
        return Interval{1,0};
    }
    int m = l+r >> 1;
    Interval a{max_overlap(l,m)};
    Interval b{max_overlap(m,r)};
    Interval c{v[m-1].overlap(v[m])};
    if(a.length() >= b.length() && a.length() >= c.length()){
        return a;
    }
    if(b.length() >= a.length() && b.length() >= c.length()){
        return b;
    }
    return c;
}



int main() {
    int n;
    std::cin>>n;
    v.reserve(n);
    for(size_t i = 0; i < n; ++i){
        int a,b;
        std::cin>>a>>b;
        v.emplace_back(a,b);
    }
    std::sort(v.begin(),v.end(),custom_comp);
    Interval res = max_overlap(0,n);
    std::cout<<res.length()<<'\n';
    if(res.length()!=0)
    std::cout<<res.left<<' '<<res.right;
}