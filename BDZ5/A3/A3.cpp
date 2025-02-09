#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> allnulls(int p){
    if(std::abs(p) < 2)
        return std::vector<std::string>();
    std::vector<std::string> ans;

    for(char i = '0'; i <= '9'; ++i){
        if(-26 * p <= (i - 'a' + 1) && (i - 'a' + 1) <= -1 * p && (i - 'a' + 1) % p == 0){
            std::string s;
            s+=i;
            s+='a' - (i - 'a' + 1)/p - 1;
            ans.push_back(s);
        }
    }
    for(char i = 'A'; i <= 'Z'; ++i){
        if(-26 * p <= (i - 'a' + 1) && (i - 'a' + 1) <= -1 * p && (i - 'a' + 1) % p == 0){
            std::string s;
            s+=i;
            s+='a' - (i - 'a' + 1)/p - 1;
            ans.push_back(s);
        }
    }

    return ans;
}

void coutvec(std::vector<std::string> &v){
    for(auto s : v){
        std::cout<<s<<' ';
    }
    std::cout<<'\n';
}

int main(){
    std::vector<std::string> v = allnulls(2);
    coutvec(v);
    return 0;
}