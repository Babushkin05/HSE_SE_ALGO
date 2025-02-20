#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            return (std::hash<int>()(p.first) << 1) ^ std::hash<int>()(p.second);
        }
    };
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    std::unordered_map<std::pair<int, int>, int> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[{u, v}] = w;
    }

    std::vector<long long> dist(n, LLONG_MAX);
    dist[0] = 0;

    for (int i = 0; i < n - 1; ++i) {
        for (auto const& [edge, weight] : edges) {
            int u = edge.first;
            int v = edge.second;
            if (dist[u] != LLONG_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    std::vector<bool> is_inf(n, false);

    for (auto const& [edge, weight] : edges) {
        int u = edge.first;
        int v = edge.second;
        if (dist[u] != LLONG_MAX && dist[u] + weight < dist[v]) {
            is_inf[v] = true;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (auto const& [edge, weight] : edges) {
            int u = edge.first;
            int v = edge.second;
            if (is_inf[u] && !is_inf[v]) {
                is_inf[v] = true;
                changed = true;
            }
        }
    }

    for (int i = 1; i < n; ++i) {
        if (is_inf[i]) {
            std::cout << "-inf\n";
        } else {
            std::cout << dist[i] << '\n';
        }
    }

    return 0;
}