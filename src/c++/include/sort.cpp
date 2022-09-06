#include "utils.h"

void bubbleSort(std::vector<int> &arr) {
    //冒泡排序每一轮只排序一个数
    // 从小到大
    for (int i = 0; i < arr.size() - 1; ++i) {
        // arr.size() - 1 - i, 即最后的数字就是排好的
        for (int j = 0; j < arr.size() - 1 - i; ++j) {
            if (arr[j] > arr[j+1])
                std::swap(arr[j], arr[j+1]);
        }
    }
}

int main() {
    using namespace std;
    vector<int> ans(4,0);

    for (int i = 0; i < 4; i++) {
        cin >> ans[i];
    }

    bubbleSort(ans);
    return 0;
}