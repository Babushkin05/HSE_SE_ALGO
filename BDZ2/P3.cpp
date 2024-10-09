#include <vector> 
#include <iostream>

std::vector<std::vector<int64_t>> matrix_sum(std::vector<std::vector<int64_t>>& A, std::vector<std::vector<int64_t>>& B){
    int n = A.size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(n));
    for(size_t i = 0; i < n; ++i){
        for(size_t j =0; j< n;++j){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}


std::vector<std::vector<int64_t>> matrix_mul(std::vector<std::vector<int64_t>>& A, std::vector<std::vector<int64_t>>& B){
    int n = A.size();
    std::vector<std::vector<int64_t>> C(n, std::vector<int64_t>(n));
    if(n<=64){
        for(size_t i = 0; i< n;++i){
            for(size_t j = 0; j< n;++j){
                int64_t sum = 0;
                for(size_t k = 0; k<n;++k){
                    sum+=A[i][k] * B[k][j];
                }
                C[i][j]=sum;
            }
        }
    }

    else {
        std::vector<std::vector<int64_t>> A11(n/2, std::vector<int64_t>(n/2));
        for(size_t i = 0; i< n/2; ++i){
            for(size_t j = 0; j< n/2;++j){
                A11[i][j] = A[i][j];
            }
        }
        std::vector<std::vector<int64_t>> A12(n/2, std::vector<int64_t>(n/2));
        for(size_t i = 0; i< n/2; ++i){
            for(size_t j = n/2; j< n;++j){
                A12[i][j-n/2] = A[i][j];
            }
        }
        std::vector<std::vector<int64_t>> A21(n/2, std::vector<int64_t>(n/2));
        for(size_t i = n/2; i< n; ++i){
            for(size_t j = 0; j< n/2;++j){
                A21[i-n/2][j] = A[i][j];
            }
        }
        std::vector<std::vector<int64_t>> A22(n/2, std::vector<int64_t>(n/2));
        for(size_t i = n/2; i< n; ++i){
            for(size_t j = n/2; j< n;++j){
                A22[i-n/2][j-n/2] = A[i][j];
            }
        }
        std::vector<std::vector<int64_t>> B11(n/2, std::vector<int64_t>(n/2));
        for(size_t i = 0; i< n/2; ++i){
            for(size_t j = 0; j< n/2;++j){
                B11[i][j] = B[i][j];
            }
        }
        std::vector<std::vector<int64_t>> B12(n/2, std::vector<int64_t>(n/2));
        for(size_t i = 0; i< n/2; ++i){
            for(size_t j = n/2; j< n;++j){
                B12[i][j-n/2] = B[i][j];
            }
        }
        std::vector<std::vector<int64_t>> B21(n/2, std::vector<int64_t>(n/2));
        for(size_t i = n/2; i< n; ++i){
            for(size_t j = 0; j< n/2;++j){
                B21[i-n/2][j] = B[i][j];
            }
        }
        std::vector<std::vector<int64_t>> B22(n/2, std::vector<int64_t>(n/2));
        for(size_t i = n/2; i< n; ++i){
            for(size_t j = n/2; j< n;++j){
                B22[i-n/2][j-n/2] = B[i][j];
            }
        }

        std::vector<std::vector<int64_t>> C11 = matrix_mul(A11,B11);
        std::vector<std::vector<int64_t>> tmp = matrix_mul(A12,B21);
        C11 = matrix_sum(C11,tmp);

        std::vector<std::vector<int64_t>> C12 = matrix_mul(A11,B12);
        tmp = matrix_mul(A12,B22);
        C12 = matrix_sum(C12,tmp);

        std::vector<std::vector<int64_t>> C21 = matrix_mul(A21,B11);
        tmp = matrix_mul(A22,B21);
        C21 = matrix_sum(C21,tmp);

        std::vector<std::vector<int64_t>> C22 = matrix_mul(A21,B12);
        tmp = matrix_mul(A22,B22);
        C22 = matrix_sum(C22,tmp);

        for(size_t i = 0 ;i<n;++i){
            for(size_t j = 0; j<n;++j){
                if(i<n/2){
                    if(j<n/2){
                        C[i][j] = C11[i][j];
                    }
                    else{
                        C[i][j] = C12[i][j-n/2];
                    }
                }
                else{
                    if(j<n/2){
                        C[i][j] = C21[i-n/2][j];
                    }
                    else{
                        C[i][j] = C22[i-n/2][j-n/2];
                    }
                }
            }
        }
    }

    return C;
}

int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    std::vector<std::vector<int64_t>> A(n, std::vector<int64_t>(n));
    std::vector<std::vector<int64_t>> B(n, std::vector<int64_t>(n));

    for(size_t i = 0; i<n;++i){
        for(size_t j = 0; j<n;++j){
            std::cin>>A[i][j];
        }
    }

    for(size_t i = 0; i<n;++i){
        for(size_t j = 0; j<n;++j){
            std::cin>>B[i][j];
        }
    }

    std::vector<std::vector<int64_t>> C = matrix_mul(A,B);

    for(size_t i = 0; i<n;++i){
        for(size_t j = 0; j<n;++j){
            std::cout<<C[i][j]<<' ';
        }
        std::cout<<'\n';
    }

}