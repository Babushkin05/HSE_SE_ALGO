#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <tuple>

int get_dist(std::tuple<int,int,int> &a, std::tuple<int,int,int> &b){
    return sqrt(pow(std::get<0>(a) - std::get<0>(b),2) + pow(std::get<1>(a) - std::get<1>(b),2) +  pow(std::get<2>(a) - std::get<2>(b),2));
}



