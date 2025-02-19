#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <algorithm>

std::vector<std::vector<int> > edges;
std::vector<std::vector<int> > invedges;
std::vector<int> f;
std::vector<bool> visited;

void dfs1(int node, int& cnt) {
    visited[node] = true;
    for (size_t i = 0; i < invedges[node].size(); ++i) {
        if (!visited[invedges[node][i]])
            dfs1(invedges[node][i], cnt);
    }
    ++cnt;
    f[node] = cnt;
}

std::vector<int> compn;

void dfs2(int node, int compnumber) {
    visited[node] = true;
    compn[node] = compnumber;
    for (size_t i = 0; i < edges[node].size(); ++i) {
        if (!visited[edges[node][i]])
            dfs2(edges[node][i], compnumber);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    edges.resize(n);
    invedges.resize(n);
    for (size_t i = 0; i < m; ++i) {
        int l, r;
        std::cin >> l >> r;
        edges[r - 1].push_back(l - 1);
        invedges[l - 1].push_back(r - 1);
    }
    visited.resize(n, false);
    f.resize(n);
    int cnt = 0;
    for (size_t i = 0; i < n; ++i) {
        if (!visited[i])
            dfs1(i, cnt);
    }

    std::vector<int> unf(n);
    for (size_t i = 0; i < n; ++i) {
        unf[n - f[i]] = i;  
    }

    for(size_t i = 0; i < n; ++i){
        visited[i] = false;
    }

    compn.resize(n);
    int compnumber = 1;
    for (int i = 0; i < n; ++i) {  
        if (!visited[unf[i]]) {
            dfs2(unf[i], compnumber++);
        }
    }

    // std::unordered_map<int, int> predstavitel;
    // std::unordered_map<int,int> updcomp;

    // for(size_t i = 0; i < n; ++i){
    //     if(!predstavitel.contains(compn[i])){
    //         predstavitel[compn[i]] = i;
    //         updcomp[i] = compn[i];
    //     }
    // }

    // std::unordered_map<int,std::unordered_set<int> > newg;
    // for(size_t i = 0; i < n; ++i){
    //     for(size_t j = 0; j < edges[i].size(); ++j){
    //         newg[predstavitel[compn[i]]].insert(predstavitel[compn[j]]);
    //     }
    // }




    // std::vector<std::pair<int,int> > ans;
    // for(size_t i = 0; i < n; ++i){
    //     ans.push_back(std::make_pair(i, compn[i]));
    // }

    // std::unordered_map<int, std::vector<int> > nodes_by_comp;
    // for(size_t i = 0; i < n; ++i){
    //     nodes_by_comp[compn[i]].push_back(i);
    // }
    // std::unordered_set<std::pair<int,int> > edges2;
    // for(size_t i = 0; i < m; ++i){
    //     for(size_t j = 0; j < edges[i].size(); ++i){
    //         edges2.insert(std::make_pair(i, edges[i][j]));
    //     }
    // }

    // std::unordered_map<int, int&> comp_by_nodes;
    // std::unordered_map<int, int&> comps;
    // for(size_t i = 0; i < n; ++i){
    //     if(!comps.contains(compn[i])){
    //         int a = compn[i];
    //         comp_by_nodes[i] = a;
    //     }
    //     else {
    //         comp_by_nodes[i] = comps[compn[i]];
    //     }
    // }

    // std::sort(ans.begin(), ans.end(), [](const std::pair<int,int> &l, const std::pair<int,int> &r){
    //     if(edges2.contains(std::make_pair(l.first,r.first))){
    //         if(l.second > r.second){
    //             std::swap(comp_by_nodes[l.first], comp_by_nodes[r.first]);
    //             return false;
    //         }
    //     }
    //     return true;
    // });

    std::cout<<compnumber - 1<<'\n';
    for (size_t i = 0; i < n; ++i) {
        std::cout << compn[i] << ' ';
    }
    return 0;
}