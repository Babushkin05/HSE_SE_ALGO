#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
    int V;
    vector<vector<long long>> adjMatrix;

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
    Graph(int V) : V(V), adjMatrix(V, vector<long long>(V, 0)) {}

    void addEdge(int u, int v, long long capacity) {
        adjMatrix[u][v] = capacity;
    }

    long long fordFulkerson(int source, int sink) {
        vector<int> parent(V);
        long long maxFlow = 0;

        while (bfs(source, sink, parent)) {
            long long pathFlow = LLONG_MAX; 
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
    int n, k;
    cin >> n >> k;
    Graph g(n);

    for (int i = 0; i < k; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g.addEdge(a - 1, b - 1, c);
    }

    cout << g.fordFulkerson(0, n - 1) << endl;

    return 0;
}