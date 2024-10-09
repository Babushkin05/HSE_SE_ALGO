#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>
#include <tuple>
#include <map>

struct Point{
    double x;
    double y;
    double z;

    Point(double _x, double _y, double _z) : x{_x}, y{_y}, z{_z} {}

    double get_dist(const Point& other){
        return sqrt(pow(x - other.x,2) + pow(y - other.y,2) +  pow(z - other.z,2));
    } 

    bool operator<(const Point& rhs) const{
        return x < rhs.x || (x == rhs.x && y < rhs.y) || (x == rhs.x && y == rhs.y && z < rhs.z);
    }

};

std::ostream& operator<<(std::ostream& sout, const Point& p){
        sout<<p.x<<' '<<p.y<<' '<<p.z;
        return sout;
    }  

std::pair<int,int> closest_pair_3d(std::vector<Point>& v) {

    if(v.size()<=3){
        std::pair<int,int> tmp = {0,v.size()-1};
        for(size_t i = 1; i< v.size();++i){
            for(size_t j = i+1;j<v.size();++j){
                double d = v[i].get_dist(v[j]);
                if(d<v[tmp.first].get_dist(v[tmp.second])){
                    tmp = std::make_pair(i,j);
                }
            }
        }
        return tmp;
    }
    std::map<Point,int> mp;
    for(size_t i = 0; i<v.size();++i){
        mp[v[i]] = i;
    }

    std::sort(v.begin(), v.end(), [](const Point& lht, const Point& rht){
        return lht.x < rht.x || (lht.x == rht.x && lht.y < rht.y) || (lht.x == rht.x && lht.y == rht.y && lht.z < rht.z);
    });


    int l = v[v.size()/2].x;
    std::vector<Point> v1,v2;
    for(size_t i = 0; i< v.size();++i){
        if(i <v.size()/2){
            v1.push_back(v[i]);
        }
        else{
            v2.push_back(v[i]);
        }
    }
    std::pair<int,int> res1 = closest_pair_3d(v1);
    if(res1.first == res1.second){
        res1 = std::make_pair(0,v.size()-1);
    }
    std::pair<int,int> res2 = closest_pair_3d(v2);
    if(res2.first == res2.second){
        res2 = std::make_pair(0,(v.size()-1)/2);
    }
    res2 = std::make_pair(res2.first+v.size()/2, res2.second + v.size()/2);
    double delta = std::min(v[res1.first].get_dist(v[res1.second]), v[res2.first].get_dist(v[res2.second]));
    std::pair<int,int> res = delta == v[res1.first].get_dist(v[res1.second]) ? res1 : res2;
    //std::cout<<v[res.first].get_dist(v[res.second])<<' '<<v[res.first]<<' '<<v[res.second]<<'\n';

    

    std::vector<std::pair<Point,int>> tmp;
    for(size_t i = 0; i<v.size();++i){
        if(std::abs(v[i].x-l)<delta){
            tmp.push_back(std::make_pair(v[i],i));
        }
    }
    double minY = INT_MAX;
    double maxY = INT_MIN;
    for(size_t i = 0; i<tmp.size();++i){
        minY = std::min(minY,tmp[i].first.y);
        maxY = std::max(maxY,tmp[i].first.y);
    }

    std::vector<std::vector<std::pair<Point,int>>> lines(static_cast<int>((maxY-minY+delta)/delta)); // split for lines with width delta
    for(size_t i = 0; i<tmp.size();++i){
        lines[static_cast<int>((tmp[i].first.y-minY)/delta)].push_back(tmp[i]);
    }

    for(int i = 0; i< lines.size();++i){
        for(int j = 0;j<lines[i].size();++j){
            for(int k = std::max(0,j-17);k<j;++k){ // 17 = (3^2) - 1
                if(lines[i][j].first.get_dist(lines[i][k].first) < v[res.first].get_dist(v[res.second])){
                    res = std::make_pair(lines[i][j].second,lines[i][k].second);
                }
            }
        }
    }

    return std::make_pair(mp[v[res.first]],mp[v[res.second]]);

}


int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    std::vector<Point> v;

    for(size_t i=0; i< n; ++i){
        double x,y,z;
        std::cin>>x>>y>>z;
        v.emplace_back(x,y,z);
    }
    

    std::cout<<std::setprecision(10);

    std::vector<Point> v2(v);
    std::pair<int,int> ans = closest_pair_3d(v);
    

    std::cout<<v2[ans.first].get_dist(v2[ans.second])<<'\n';
    std::cout<<ans.first+1<<' '<<ans.second+1;
}
