#include <iostream>
#include <string>
#include <vector>

std::string shift(std::string& s, int a){
    if(a<=0)
        return s;
    std::string ans(a,'0');
    return s+ans;
}
std::string add_zeros(std::string& s, int a){
    if(a<=0)
        return s;
    std::string ans(a,'0');
    return ans+s;
}

std::string big_sum(std::string& s1, std::string& s2){
    if(s1.size()<s2.size())
        std::swap(s1,s2);
    int j = s1.size() - s2.size();
    std::string ans(s1.size()+1,'0');
    int q = 0;
    for(int i = s1.size()-1;i-j>=0;--i){
        int tmp = s1[i] + s2[i-j] - 2*'0';
        ans[i+ 1] = (tmp+q)%10+ '0';
        q= (tmp+q) /10;
    }
    for(int i = j-1; i>=0;--i){
        int tmp = s1[i]  - '0';
        ans[i+ 1] = (tmp+q)%10+ '0';
        q= (tmp+q) /10;
    }
    if(q==1){
        ans[0] = '1';
    }
    return ans;
}

std::string big_sub(std::string& s1, std::string& s2){
    std::string ans = s1;
    int q=0;
    s2 = add_zeros(s2, s1.size()-s2.size());
    for(int i = s1.size()-1;i>=0;--i){
        int tmp = 10+s1[i]-s2[i]-q;
        ans[i] = tmp%10 + '0';
        q = !(tmp/10);
    }
    return ans;
}

std::string big_mult(std::string& s, int m){
    if(m==0){
        return "0";
    }
    std::string ans(s.size()+1,'0');
    int q = 0;
    for(int i = s.size()-1;i>=0;--i){
        int tmp = (s[i]-'0')*m;
        ans[i+ 1] = (tmp+q)%10+ '0';
        q= (tmp+q) /10;
    }
    if(q!=0){
        ans[0] = q+'0';
    }
    return ans;
}

std::string big_mult(std::string s1, std::string s2){
    std::string ans(std::max(s1.size(),s2.size()),'0');
    for(int i = s1.size()-1; i>=0;--i){
        std::string tmp = big_mult(s2, s1[i]-'0');
        tmp = shift(tmp,s1.size()-i-1);
        //std::cout<<tmp<<'\n';
        tmp = add_zeros(tmp,ans.size() - tmp.size());
        //std::cout<<tmp<<'\n';
        ans = big_sum(ans,tmp);
        //std::cout<<ans<<'\n';;
    }
    return ans;
}

std::string remove_zeros(std::string& s){
    int i=0;
    while(s[i]=='0'){
        ++i;
    }
    s=s.substr(i,s.size()-i+1);
    if(s.size()==0){
        return "0";
    }
    return s;
}

std::string karatsuba(std::string a, std::string b){
    a = remove_zeros(a);
    b = remove_zeros(b);
    if(a.size()<b.size())
        std::swap(a,b);
    b = add_zeros(b, a.size() - b.size());
    
    if(a.size()<=100){
        std::string tmp = big_mult(a,b);
        return remove_zeros(tmp);
    }
    int l = (a.size())/2;
    std::string a1 = a.substr(0,l);
    std::string a0 = a.substr(l);
    std::string b1 = b.substr(0,l);
    std::string b0 = b.substr(l);

    std::string a0b0 = karatsuba(a0,b0);
    std::string a1b1 = karatsuba(a1,b1);
    std::string m3 = karatsuba(big_sum(a0,a1),big_sum(b0,b1));

    std::string s1 = shift(a1b1,2*(a.size()-l));
    std::string tmp = big_sub(m3, a1b1);
    tmp = big_sub(tmp, a0b0);
    std::string s2 = shift(tmp, a.size()-l);
    tmp = big_sum(s1,s2);

    return big_sum(tmp,a0b0);
}

int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    std::string s1,s2;
    std::cin>>s1>>s2;
    std::string tmp = karatsuba(s1,s2);
    std::cout<<remove_zeros(tmp);
    return 0;
}