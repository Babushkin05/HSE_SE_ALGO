#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Network {
    int V; 
    vector<vector<long long>> adjMatrix; 

    bool bfs(int s, int t, vector<int>& level) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0; 
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 0; v < V; v++) {
                if (level[v] == -1 && adjMatrix[u][v] > 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1; 
    }

    long long dfs(int u, int t, long long flow, vector<int>& level, vector<int>& ptr) {
        if (u == t) return flow; 

        for (int& v = ptr[u]; v < V; v++) { 
            if (level[v] == level[u] + 1 && adjMatrix[u][v] > 0) { 
                long long pushed = dfs(v, t, min(flow, adjMatrix[u][v]), level, ptr); 
                if (pushed > 0) {
                    adjMatrix[u][v] -= pushed;
                    adjMatrix[v][u] += pushed; 
                    return pushed;
                }
            }
        }
        return 0; 
    }

public:
    Network(int V) : V(V), adjMatrix(V, vector<long long>(V, 0)) {}

    void addEdge(int u, int v, long long capacity) {
        adjMatrix[u][v] = capacity;
    }

    long long dinic(int source, int sink) {
        long long maxFlow = 0;
        vector<int> level(V); 
        vector<int> ptr(V);  

        while (bfs(source, sink, level)) { 
            fill(ptr.begin(), ptr.end(), 0); 
            while (long long pushed = dfs(source, sink, LLONG_MAX, level, ptr)) { 
                maxFlow += pushed; 
            }
        }

        return maxFlow;
    }
};