#include <vector>
#include <iostream>

class heap{
    public:
        heap(std::vector<int> &vec){ // buildMaxHeap
            data.resize(4*vec.size());
            for(size_t i = 0; i < vec.size();++i){
                push(vec[i]);
            }
        }
        void push(int a){
            data[last_ind] = a;
            swim_up(last_ind);
            ++last_ind;
        }

        std::vector<int> heapSort(){
            int n = last_ind;
            
            for(size_t i = last_ind-1; i>1; --i){
                // for(size_t i = 1; i<n;++i){
                //     std::cout<<data[i]<<' ';
                // }std::cout<<'\n';
                std::swap(data[i], data[1]);
                --last_ind;
                sink_down(1);
            }
            std::vector<int> ans;
            for(size_t i = 1; i < n; ++i){
                ans.push_back(data[i]);
            }
            return ans;
        }
    private:
        std::vector<int> data;
        int last_ind=1;

        void swim_up(int ind){ // heapify
            while(ind/2>0 && data[ind]>data[ind/2]){
                std::swap(data[ind], data[ind/2]);
                ind/=2;
            }
        }

        void sink_down(int ind){ // heapify
            while(2*ind +1 <= last_ind){
                int j = 2 * ind;
                if((j+1<last_ind) && (data[j]<data[j+1])) ++j;
                if(!(data[ind]<data[j])) break;
                std::swap(data[ind], data[j]);
                ind = j;
            }
        }

};

int main(){
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);
    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    std::vector<int> v(n);
    for(size_t i = 0; i< n;++i){
        std::cin>>v[i];
    }
    heap h{v};
    std::vector<int> ans = h.heapSort();
    for(size_t i = 0 ;i<n;++i){
        std::cout<<ans[i]<<' ';
    }

    return 0;
}