#include "../include/utils.h"

using namespace std;

class MinStack
{
private:
    stack<int> dataStack;
    stack<int> stackMin;
public:
    MinStack(/* args */);
    ~MinStack();

    void push(int x) {
        // Min栈空则直接同入两个栈
        if (this->stackMin.empty())
            this->stackMin.push(x);
        else {
            if (x <= this->getMin())
                this->stackMin.push(x);
        }
        this->dataStack.push(x);
    }

    int getMin() {
        return this->stackMin.top();
    }

    int pop() {
        if (this->dataStack.empty()) {
            return 0;
        }
        // 取得栈顶元素并且和stackMin的栈顶元素进行比较
        int x = this->dataStack.top();
        if (x == this->getMin()) {
            this->stackMin.pop();
        }
        this->dataStack.pop();
        return x;
    }
};

MinStack::MinStack(/* args */)
{
}

MinStack::~MinStack()
{
}

int main() {
    MinStack s;
    int test[] = {3,4,5,1,2,1};
    
    for (auto c : test) 
        s.push(c);
    
    cout << "min value is " << s.getMin() << endl;
    cout << "s.pop()\t" << s.pop() << endl;
    cout << "s.pop()\t" << s.pop() << endl;

    return 0;
}