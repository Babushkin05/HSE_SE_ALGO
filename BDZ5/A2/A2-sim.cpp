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

void insert_to_table(int key, std::vector<int> &table, bool iscubo){
    int ind  = key;
    int i = 1;
    while(table[ind] != 0){
        if(iscubo){
            ind = hash2(key, i) % table.size();
        }
        else{
            ind = hash1(key, i) % table.size();
        }
        ++i;
        //if(table[ind] != 0 && table[ind] != key)
        //    std::cout<<table[ind]<<' '<<key<<' '<<iscubo<<'\n';
    }
    table[ind] = key;

}

int main(){
    size_t M = 32;
    std::vector<int> v1(M, 0);
    std::vector<int> v2(M, 0);

    std::vector<int> keys{1,3,2,4,2,3,1,2,3,2,4,3,2,3,1};

    for(size_t i = 0; i < keys.size(); ++i){
        insert_to_table(keys[i], v1, false);
        insert_to_table(keys[i], v2, true);
    }
    std::cout<<"quadro:\n";
    coutvec(v1);
    std::cout<<"cubo:\n";
    coutvec(v2);

    return 0;
}