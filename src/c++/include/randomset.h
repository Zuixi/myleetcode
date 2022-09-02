#include "utils.h"

class RandomizedSet {
private:
    std::vector<int> arr;
    // <key, val> == <index, val> 即索引-值的键值对
    std::unordered_map<int,int> mp;
public:
    RandomizedSet() {
        // do nothing
    }
    
    bool insert(int val) {
        if (!mp.count(val)) {
            arr.emplace_back(val);
            mp[val] = arr.size()-1;
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if (mp.count(val)) {
            auto index = mp[val];
            // 将最后一个元素的索引变为index
            mp[arr.back()] = index;
            std::swap(arr[index],arr.back());
            
            // 弹出元素且删除索引
            arr.pop_back();
            mp.erase(val);
            return true;
        } else {
            return false;
        }
    }
    
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};
