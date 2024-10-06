#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

int get_dist(std::pair<int,int> a, std::pair<int,int> b){
    return sqrt(pow(a.first-b.first,2) + pow(a.second - b.second,2));
}

int closest_pair_2d(std::vector<std::pair<int,int>> &v){
    std::sort(v.begin(), v.end());
    // for(size_t i = 0; i<v.size();++i){
    //     std::cout<<v[i].first<<' '<<v[i].second<<"\t";
    // }std::cout<<'\n';
    if(v.size()<=2){
        int delta = INT_MAX;
        for(size_t i = 1; i< v.size();++i){
            int d = get_dist(v[i-1],v[i]);
            delta = std::min(delta, d);
        }
        return delta;
    }
    int l = v[v.size()/2].first;
    std::vector<std::pair<int,int>> v1,v2;
    for(int i = 0; i < v.size();++i){
        if(i<v.size()/2){
            v1.push_back(v[i]);
        }
        else{
            v2.push_back(v[i]);
        }
    }
    int delta1 = closest_pair_2d(v1);
    int delta2 = closest_pair_2d(v2);
    int delta = std::min(delta1,delta2);
    std::vector<std::pair<int,int>> tmp;
    for(size_t i = 0; i<v.size();++i ){
        if(std::abs(v[i].first-l)<delta){
            tmp.push_back(v[i]);
        }
    }
    std::sort(tmp.begin(),tmp.end(), [](std::pair<int,int> a, std::pair<int,int> b){
        return a.second < b.second;
    }); 
    // for(size_t i = 0; i<tmp.size();++i){
    //     std::cout<<tmp[i].first<<' '<<tmp[i].second<<'\n';
    // } 
    for(int i = 1; i < tmp.size(); ++i){
        for(int j = std::max(i-6,0); j < i; ++j){
            delta = std::min(delta,get_dist(tmp[i],tmp[j]));
        }
    }
    return delta;
}

int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    std::vector<std::pair<int,int>> v;
    int a,b;
    while(std::cin>>a>>b){
        v.emplace_back(a,b);
    }
    std::cout<<closest_pair_2d(v);
}