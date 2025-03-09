#include <iostream>
#include <vector>

using namespace std;

bool dfs(int u, vector<bool>& visited, vector<int>& pairU, vector<int>& pairV, const vector<vector<int>>& graph) {
    if (visited[u]) return false;
    visited[u] = true;

    for (int v : graph[u]) {
        if (pairV[v] == -1 || dfs(pairV[v], visited, pairU, pairV, graph)) {
            pairU[u] = v;
            pairV[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1); 

    for (int u = 1; u <= n; ++u) {
        int v;
        while (cin >> v, v != 0) {
            graph[u].push_back(v);
        }
    }

    vector<int> pairU(n + 1, -1); 
    vector<int> pairV(m + 1, -1); 

    int matchingSize = 0;
    for (int u = 1; u <= n; ++u) {
        vector<bool> visited(n + 1, false);
        if (dfs(u, visited, pairU, pairV, graph)) {
            matchingSize++;
        }
    }

    cout << matchingSize << endl;
    for (int u = 1; u <= n; ++u) {
        if (pairU[u] != -1) {
            cout << u << " " << pairU[u] << endl;
        }
    }

    return 0;
}