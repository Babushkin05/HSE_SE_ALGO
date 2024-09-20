#include <iostream>
#include <vector>
#include <set>

int main() {
    size_t n;
    std::cin>>n;
    std::vector<int> v(n);
    for(size_t i = 0;i<n;++i){
        std::cin>>v[i];
    }
    std::vector<std::set<std::vector<int>>> ans(n+1);
    for(size_t i = 0; i<n; ++i){
        size_t cnt = 0;
        std::vector<int> tmp;
        for(size_t j = 0; j < n; ++j){
            cnt += v[j]!=v[(j+i)%n];
            tmp.push_back(v[(i+j)%n]);
        }
        ans[cnt].insert(tmp);
        //std::cout<<i<<' '<<cnt<<'\n';
    }
    int ind = n;
    while(!ans[ind].size())
        --ind;
    std::cout<<ans[ind].size();
}