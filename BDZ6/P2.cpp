#include <utility>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>

int n,m;
std::vector<std::vector<std::pair<int,int> > > edges;

int main() {
    std::cin>>n>>m;
    edges.resize(m);
    for(size_t i = 0; i < m; ++i){
        int a, b, c;
        std::cin>>a>>b>>c;
        edges[a - 1].push_back(std::make_pair( - c, b - 1));
        edges[b - 1].push_back(std::make_pair( - c, a - 1));
    }
    std::unordered_set<int> included{0};
    std::priority_queue<std::pair<int,int> > available;
    for(auto p : edges[0]){
        available.push(p);
    }
    int ans = 0;
    while (included.size() < n) {
        auto [c, a] = available.top();
        available.pop();
        if(included.contains(a))
            continue;
        included.insert(a);
        ans -= c;
        for(auto p : edges[a]){
            available.push(p);
        }
    }
    std::cout<<ans;
}