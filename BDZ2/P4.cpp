#include <vector>
#include <iostream>
#include <iomanip>

int l, n;
std::vector<std::pair<int,int>> v;

bool is_correct(long double time){
    long double totaltime = 0;
    long double s1 = 0;
    long double s2 = 0;

    long double tmp = time;
    int i = 0;
    while(tmp>0){
        tmp-=v[i].first;
        s1+=v[i].first *v[i].second;
        totaltime+=v[i].first;
        ++i;
    }
    int j = 0;
    long double t1ost = std::abs(tmp);
    long double t2ost  = 0;
    if(t1ost>0){
        --i;
        s1-=v[i].second * t1ost;
        totaltime-=t1ost;
    }
    if(s1-s2<l)
            return false;

    //std::cout<<totaltime<<' '<<s1<<' '<<s2<<'\n';
    
    while(i<n && j<n){
        if(t2ost==0){
            if(v[j].first>t1ost){
                s1+=v[i].second*t1ost;
                s2+=v[j].second*t1ost;
                t2ost = v[j].first - t1ost;
                totaltime+=t1ost;
                t1ost = 0;
                ++i;
            }
            else if(v[j].first<t1ost){
                s1+=v[i].second * v[j].first;
                s2+=v[j].second * v[j].first;
                t1ost -= v[j].first;
                totaltime+=v[j].first;
                ++j;
            }
            else{
                s1+=v[i].second*t1ost;
                s2+=v[j].second*t1ost;
                totaltime+=t1ost;
                ++i;
                ++j;
                t1ost = 0;
            }
        }
        else{
            if(v[i].first>t2ost){
                s1+=v[i].second*t2ost;
                s2+=v[j].second*t2ost;
                t1ost = v[i].first - t2ost;
                totaltime += t2ost;
                t2ost = 0;
                ++j;
            }
            else if(v[i].first<t2ost){
                s1+=v[i].second * v[i].first;
                s2+=v[j].second * v[i].first;
                t2ost -= v[i].first;
                totaltime+=v[i].first;
                ++i;
            }
            else{
                s1+=v[i].second*t2ost;
                s2+=v[j].second*t2ost;
                totaltime+=t2ost;
                ++i;
                ++j;
                t2ost = 0;
            }
        }
        //std::cout<<totaltime<<' '<<s1<<' '<<s2<<'\n';
        if(s1-s2<l){
            return false;
        }
    }
    return true;
}

int main(){
    std::cin>>l>>n;
    v.reserve(n);
    long double right = 0.0L;
    for(size_t i = 0; i< n; ++i){
        int t, u;
        std::cin>>t>>u;
        v.emplace_back(t,u);
        right+= t;
    }
    long double left = 0.0L;
    if (right==0)
    {
        return 0;
    }
    
    while(left+0.001<right){
        long double m = (right+left)/2;
        if(is_correct(m)){
            right = m;
        }
        else{
            left = m;
        }
    }

    std::cout<<std::fixed<<std::setprecision(3)<<right<<'\n';
}