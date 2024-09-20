#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::stack<int> one;
    std::stack<int> tup;
    std::stack<int> two;
    std::vector<std::pair<int,int>> ans;

    int n;
    std::cin>>n;
    two.push(0);
    int m[n];
    for(size_t i = 0; i < n; ++i){
        int a;
        std::cin>>a;
        m[i]=a;
    }
    for(int i = n - 1; i >= 0; --i)
        one.push(m[i]);

    for(size_t i = 0; i< n; ++i){
        int a=one.top();
        one.pop();
        ans.push_back(std::make_pair(1,1));
        tup.push(a);
        while(tup.size()){
            if(tup.top()==two.top()+1){
                int b=tup.top();
                tup.pop();
                two.push(b);
                ans.push_back(std::make_pair(2,1));
            }
            else break;
        }
    }
    if(tup.size())
        std::cout<<0;
    else{
        for(size_t i = 0; i< 2*n;++i)
            std::cout<<ans[i].first<<' '<<ans[i].second<<'\n';
    }
    return 0;
}