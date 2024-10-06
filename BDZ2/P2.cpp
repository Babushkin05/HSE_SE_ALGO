#include <iostream>
#include <string>

std::string shift(std::string s, int a){
    std::string ans;
    for(int i = 0; i< a;++i){
        ans+="0";
    }
    return s+ans;
}
std::string add_zeros(std::string s, int a){
    std::string ans;
    for(int i = 0; i<a;++i){
        ans+="0";
    }
    return ans+s;
}

std::string big_sum(std::string s1, std::string s2){
    std::string ans;
    if(s1.size()<s2.size())
        std::swap(s1,s2);
    s2 = add_zeros(s2, s1.size() - s2.size());
    for(int i = 0; i<=s1.size();++i){
        ans+="0";
    }
    int q = 0;
    for(int i = s1.size()-1;i>=0;--i){
        int tmp = s1[i] + s2[i] - 2*'0';
        ans[i+ 1] = (tmp+q)%10+ '0';
        q= (tmp+q) /10;
    }
    if(q==1){
        ans[0] = '1';
    }
    return ans;
}

std::string big_sub(std::string s1, std::string s2){
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

std::string big_mult(std::string s, int m){
    if(m==0){
        return "0";
    }
    std::string ans;
    for(int i = 0; i<=s.size();++i){
        ans+="0";
    }
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
    std::string ans;
    for(int i = 0; i<= std::max(s1.size(),s2.size());++i){
        ans+="0";
    }
    for(int i = s1.size()-1; i>=0;--i){
        std::string tmp = shift(big_mult(s2, s1[i]-'0'),s1.size()-i-1);
        //std::cout<<tmp<<'\n';
        tmp = add_zeros(tmp,ans.size() - tmp.size());
        //std::cout<<tmp<<'\n';
        ans = big_sum(ans,tmp);
        //std::cout<<ans<<'\n';;
    }
    return ans;
}

std::string remove_zeros(std::string s){
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
    
    if(a.size()<=50){
        return remove_zeros(big_mult(a,b));
    }
    int l = (a.size())/2;
    std::string a1 = a.substr(0,l);
    std::string a0 = a.substr(l);
    std::string b1 = b.substr(0,l);
    std::string b0 = b.substr(l);

    //std::cout<<a<<' '<<b<<' '<<a1<<' '<<a0<<' '<<b1<<' '<<b0<<'\n';

    std::string a0b0 = karatsuba(a0,b0);
    std::string a1b1 = karatsuba(a1,b1);
    std::string m3 = karatsuba(big_sum(a0,a1),big_sum(b0,b1));

    std::string s1 = shift(a1b1,2*(a.size()-l));
    std::string s2 = shift(big_sub(big_sub(m3, a1b1), a0b0), a.size()-l);
    std::string s3 = a0b0;

    return big_sum(big_sum(s1,s2),s3);
}

int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    std::string s1,s2;
    std::cin>>s1>>s2;

    std::cout<<remove_zeros(karatsuba(s1,s2));
    return 0;
}