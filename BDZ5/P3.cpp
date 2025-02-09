#include <iostream>
#include <vector>
#include <unordered_map>

std::unordered_map<uint64_t,std::vector<std::pair<size_t,size_t>>> mapa;
std::vector<int> v1;
std::vector<int> v2;

uint64_t hasher(int l, int r, bool isfirst){
    uint64_t ans = 0;
    uint64_t xor_ = 0;
    if(isfirst){
        for(size_t i = l; i < r; ++i){
            ans += v1[i] * v1[i] * v1[i];
            xor_ ^= v1[i];
        }
    }
    else{
        for(size_t i = l; i < r; ++i){
            ans += v2[i] * v2[i] * v2[i];
            xor_ ^= v2[i];
        }
    }

    return xor_ + ans * 1337;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin>>n;
    v1.resize(n);
    for(size_t i = 0; i < n; ++i)
        std::cin>>v1[i];
    int m;
    std::cin>>m;
    v2.resize(n);
    for(size_t i = 0; i < n; ++i)
        std::cin>>v2[i];
    
    for(size_t l = 0; l < n; ++l){
        for(size_t r = l + 1; r <= n; ++r){
            uint64_t hash = hasher(l, r, true);
            mapa[hash].push_back(std::make_pair<int,int>(l, r));
        }
    }
    int l1 = -1;
    int r1 = -1;
    int l2 = -1;
    for(size_t l = 0; l < m; ++l){
        for(size_t r = l + 1; r <= m; ++r){
            uint64_t hash = hasher(l, r, false);
            for(auto pair : mapa[hash]){
                if(pair.second - pair.first == r - l){
                    if(r - l > r1 - l1){
                        r1 = r;
                        l1 = l;
                        l2 = pair.first;
                    }
                }
            }
        }
    }
    if(r1 - l1 == 0)
        std::cout<<"0 -1 -1";
    else
        std::cout<<r1 - l1 <<' ' <<l2 + 1<<' '<<l1 + 1;
}