#include <iostream>
#include <string>

std::string big_sum(std::string s1, std::string s2){
    std::string ans;
    for(size_t i = 0; i<=s1.size();++i){
        ans+="0";
    }
    int q = 0;
    for(size_t i = s1.size()-1;i>=0;--i){
        std::cout<<i<<' ';
        int tmp = s1[i] + s2[i] +q - 2*'0';
        q= tmp /10;
        ans[i+ 1] = tmp%10 + '0';
    }
    if(q==1){
        ans[0] = '1';
    }
    return ans;
}

int main(){
    std::string s1,s2;
    std::cin>>s1>>s2;
    std::cout<<big_sum(s1,s2);
    return 0;
}