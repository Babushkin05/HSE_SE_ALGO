#include <iostream>
#include <vector>

int main() {

    int n, m;
    std::cin>>n>>m;
    std::vector<std::vector<long long>> matrix(n, std::vector<long long>(n, 1e11));

    for(size_t i = 0; i < n; ++i)
        matrix[i][i] = 0;
    for(size_t i = 0; i < m; ++i){
        int u, v;
        long long w;
        std::cin>>u>>v>>w;
        matrix[u][v] = w;
    }

    for(size_t k = 0; k < n; ++k){
        for(size_t i = 0; i < n; ++i){
            for(size_t j = 0; j < n; ++j){
                matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < n; ++j){
            if(i == j)
                continue;
            std::cout<<i<<' '<<j<<' ';
            if(matrix[i][j] == 1e11)
                std::cout<<"-1\n";
            else
                std::cout<<matrix[i][j] <<'\n';
        }
    }

    return 0;
}