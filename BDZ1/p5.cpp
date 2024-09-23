#include <iostream>
#include <list>

int main(){
    //ios::sync_with_stdio(false);  // Отключить синхронизацию между iostream и stdio.
    std::cin.tie(nullptr);        // Отключить синхронизацию между std::cin и std::cout.

    std::list<int> l;
    auto mid = l.end();

    int times;
    std::cin>>times;
    while(times--){
        char c;
        std::cin>>c;
        if(c=='+'){
            int n;
            std::cin>>n;
            l.push_back(n);
            if(l.size()==1){
                mid = l.begin();
            }
            else if(l.size()%2 || l.size() == 2){
                ++mid;
            }
        }
        else if(c=='*'){
            int n;
            std::cin>>n;
            if(l.size()<2){
                l.push_back(n);
            }
            else
                l.insert(mid,n);

            if(l.size()==1){
                mid = l.begin();
            }
            else if(l.size()%2==0){
                --mid;
            }
        }
        else{
            std::cout<<l.front()<<'\n';
            l.pop_front();
            if(l.size()%2){
                ++mid;
            }
        }

        // for(auto x:l){
        //     std::cout<<x<<' ';
        // }std::cout<<"   "<<*mid<<'\n';

    }
}