#include <vector>

std::pair<int,int> index_by_key(std::vector<std::vector<int>> matrix, int n, int k){
    for(size_t i = 0; i < n; ++i){
        if(matrix[i][i] == k){
            return std::make_pair(i,i);
        }
        if(matrix[i][i] > k){
            for(size_t j = i - 1; j >= 0; --j){
                if(matrix[i][j] == k){
                    return std::make_pair(i,j);
                }
                if(matrix[i][j] < k){
                    break;
                }
            }

            for(size_t j = i - 1; j >= 0; --j){
                if(matrix[j][i] == k){
                    return std::make_pair(j,i);
                }
                if(matrix[j][i] < k){
                    break;
                }
            }
            break;
        }
    }
    return std::make_pair(-1,-1);
}