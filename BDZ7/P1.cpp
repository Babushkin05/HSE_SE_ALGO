#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adjMatrix; 

    bool bfs(int s, int t, vector<int>& parent) {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++) {
                if (!visited[v] && adjMatrix[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == t) {
                        return true;
                    }
                }
            }
        }
        return false; 
    }

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int u, int v, int capacity) {
        adjMatrix[u][v] = capacity;
    }

    int fordFulkerson(int source, int sink) {
        vector<int> parent(V); 
        int maxFlow = 0; 

        while (bfs(source, sink, parent)) {
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = min(pathFlow, adjMatrix[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                adjMatrix[u][v] -= pathFlow; 
                adjMatrix[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }
};

int main() {
    int n,k;
    std::cin>>n>>k;
    Graph g(n);

    for(size_t i = 0; i < n; ++i){
        int a,b,c;
        std::cin>>a>>b>>c;
        g.addEdge(a,b,c);
    }
    cout <<  g.fordFulkerson(0, n - 1) << endl;

    return 0;
}