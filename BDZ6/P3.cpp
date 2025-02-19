#include <iostream>
#include <vector>
#include <set>
#include <stack>

struct Node{
    size_t value;
    Node *father;
    int size = 1;
};

class UNION_FIND {
public:
    UNION_FIND(size_t n_) : n{n_} {
        roots = std::vector<Node*>(n);
        for(size_t i = 0; i < n; ++i){
            roots[i] = new Node{i, nullptr};
        }
    }

    void Union(size_t l, size_t r) {
        Node* rfather = Find(r);
        Node* lfather = Find(l);

        if(rfather == lfather)
            return;
        
        if(lfather->size < rfather->size){
            std::swap(l, r);
        }
        rfather->father = lfather;
        lfather->size += rfather->size;
    }

    Node* Find(size_t key) {
        if(roots[key]->father == nullptr)
            return roots[key];
        return roots[key]->father = Find(roots[key]->father->value);
    }
private:
    size_t n;
    std::vector<Node*> roots;
};

int main(){
    int n, m, k;
    std::cin>>n>>m>>k;
    UNION_FIND uf(n);
    std::set<std::pair< size_t, size_t> > edges;
    for(size_t i = 0; i < m; ++i){
        int a, b;
        std::cin>>a>>b;
        edges.insert(std::make_pair(a - 1, b - 1));
        edges.insert(std::make_pair(b - 1, a - 1));
    }
    std::stack<std::tuple<bool, size_t, size_t>> operations;
    std::stack<std::pair<size_t, size_t>> to_add;

    for(size_t i = 0; i < k; ++i){
        std::string q;
        int l, r;
        std::cin>>q>>l>>r;
        if(q=="cut"){
            edges.erase(std::make_pair(l - 1, r - 1));
            edges.erase(std::make_pair(r - 1, l - 1));
            to_add.push(std::make_pair(l - 1, r - 1));
        }
        operations.push(std::make_tuple(q == "cut", l - 1, r - 1));
    }

    for(auto [l, r] : edges){
        uf.Union(l, r);
    }
    std::stack<std::string> ans;
    while (!operations.empty())
    {
        auto [q, l, r] = operations.top();
        operations.pop();
        if(q){
            uf.Union(l, r);
        }
        else{
            if(uf.Find(l) == uf.Find(r))
                ans.push("YES");
            else
                ans.push("NO");
        }
    }
    while (!ans.empty())
    {
        std::string to_print = ans.top();
        ans.pop();
        std::cout<<to_print<<'\n';
    }
    



    return 0;
}