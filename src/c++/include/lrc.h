#include "utils.h"

using namespace std;

typedef struct Node {
	int key, val;
	struct Node* prev;
	struct Node* next;

	Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
}Node;


class LRU
{
private:
	// 头尾虚节点
	Node* head, * tail;
	// 元素的个数
	int size = 0;

public:
	LRU() {
		head = new Node(0, 0);
		tail = new Node(0, 0);
		head->next = tail;
		tail->prev = head;
		size = 0;
	}

	// 参数链表中的X节点（X一定存在）
	// 
	void remove(Node *x) {
		x->prev->next = x->next;
		x->next->prev = x->prev;
		size--;
	}

	void add(Node* x) {
		tail->prev->next = x;
		x->prev = tail->prev;
		x->next = tail;
		tail->prev = x;
		size++;
	}

	// 移除链表第一个元素
	Node* removeFirst() {
		if (head->next == tail)
			return nullptr;
		
		head->next->next->prev = head;
		auto t = head->next;
		head->next = t->next;
		size--;
		return t;
	}

	int length() {
		return this->size;
	}
};

// 需要同时在LRU和Node链表中维护数据，即删除Node，也需要在map中删除key，缺一不可
class LRUCache {
private:
	// <int, Node> 即key, Node<key,val>
	std::unordered_map<int, Node*> mp;
	// Node<key,val> <-> Node<key,val> ...
	LRU cache;

	// 最大容量
	int capacity = 0;
	
	// 将某个key提升为最近使用的
	void makeRecently(int key) {
		if (this->mp.count(key)) {
			auto x = mp[key];
			cache.remove(x);
			// 重新插入到链表末尾
			cache.add(x);
			// 为key重新赋值
			mp[key] = x;
		}
	}

	void addRecently(int key, int val) {
		Node* x = new Node(key, val);
		cache.add(x);
		// 字典中添加映射key-Node
		mp[key] = x;
	}

	// 删除某一个key
	void deleteNode(int key) {
		if (mp.count(key)) {
			auto x = mp[key];
			cache.remove(x);
			mp.erase(key);
		}
		else {
			std::cout << "key not exist!\n";
		}
	}
	// 删除最近未使用的一个元素
	void removeLastRecently() {
		auto x = cache.removeFirst();
		// 删除之后需要在mp中删除对应的key
		mp.erase(x->key);
	}

public:
	LRUCache(const int cap) {
		this->capacity = cap;
		cache = LRU();
	}

	// 更新元素
	int get(int key) {
		if (mp.count(key)) {
			makeRecently(key);
			return mp[key]->val;
		}
		else {
			return -1;
		}
	}

	void put(int key, int val) {
		if (mp.count(key)) {
			// 若已经存在key，则需要更新val
			deleteNode(key);
			addRecently(key, val);
		}
		else {
			// 判断是否size已满
			if (cache.length() == this->capacity) {
				removeLastRecently();
				addRecently(key, val);
			}
			else {
				addRecently(key, val);
			}
		}
	}
};