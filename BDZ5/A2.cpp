#include <iostream>
#include <vector>

std::hash<int> hasher{};

size_t hash1(int a, size_t i){
    return hasher(a) + i/2 + i*i/2;
}

size_t hash2(int a, size_t i){
    return hasher(a) + i + 2*i*i*i;
}

inline void coutvec(std::vector<int> &v){
    for(size_t i = 0; i < v.size(); ++i){
        std::cout<<v[i]<<' ';
    }
    std::cout<<'\n';
}

int main(){
    size_t M = 256;
    std::vector<int> v1(M, 0);
    std::vector<int> v2(M, 0);

    for(size_t i = 0; i < 100; ++i){
        v1[hash1(1, i) % M] += 1;
        v2[hash2(1, i) % M] += 1;
        std::cout<<"quadro:\n";
        coutvec(v1);
        std::cout<<"cubo:\n";
        coutvec(v1);
    } 
    return 0;
}