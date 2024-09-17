#include <stack>

class Queue{
    public:
        void push(int elem);
        int pop();
        int& front();
        int& back();
        int currentMin();

    private:
        std::stack<int> pushStack_;
        std::stack<int> popStack_;
        int min_ = INT_MAX;
        void toPop_();
        void toPush_();
};