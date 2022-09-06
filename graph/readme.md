### 图的存储结构
1. **直接存边**

    使用一个**数组来存边**，数组中的**每个元素都包含一条边的起点与终点**（带边权的图还包含边权）

    ```
    #include <iostream>
    #include <vector>

    using namespace std;

    typedef struct Edge{
        int u,v;
    }Edge;

    int n, m;
    vector<Edge> e;
    vector<bool> vis;

    bool find_edge(int u, int v) {
        for (auto itr : e)
            if (itr.u == u && itr.v == v)
                return true;
        return false;
    }

    void dfs(int u) {
        if (vis[u])
            return;
        vis[u] = true;

        for (int i = 1; i <= n; i++){
            if (e[i].u == u) {
                dfs(e[i].v);
            }
        }
    }

    int  main(){
        // n个节点，m条边
        cin >> n >> m;
        vis.resize(n+1,false);
        e.resize(m+1);

        for (int i = 1; i <= n; i++)
            cin >> e[i].u >> e[i].v;
        return 0;
    }
    ```

    **复杂度：**

    * 查询是否存在某条边：`O(m)`

    * 遍历一个点的所有出边: `O(m)`

    * 遍历整张图：`O(nm)`

    * 空间复杂度：`O(n)`

2. **邻接矩阵**

    使用一个二维数组`adj`来存边，其中`adj[u][v]`为1表示存在`u到v`的边，为0表示不存在。如果是带边权的图，可以在`adj[u][v]`中存储`u到v`的边的边权。

    ```
    #include <iostream>
    #include <vector>

    using namespace std;

    int n,m;
    vector<bool> vis;
    vector<vector<int>> adj;

    bool find_edge(int u, int v) {
        return adj[u][v];
    }

    void dfs(int u) {
        if (vis[u])
            return;
        vis[u] = true;
        for (int v = 1; v <= n; v++){
            if (adj[u][v])
                dfs(v);
    }

    int main() {
        cin >> n >> m;
        ajd.resize(n+1,vector<int>(n+1, 0));
        vis.resize(n+1,false);

        for (int i = 1; i <= m; i++) {
            int u,v;
            cin >> u >> v;
            adj[u][v]=1;
        }

        return 0;
    }
    ```

    **复杂度:**

    * 查询是否存在某条边：`o(1)`

    * 遍历一个点的所有出边：`o(n)`

    * 遍历整张图：`o(n^2)`

    * 空间复杂度: `o(n^2)`

3. **邻接表**

    使用一个**支持动态增加元素的数据结构构成的数组**，如`vector<int> adj[n + 1]`来**存边**，其中`adj[u]`存储的是`点u`的**所有出边**的相关信息（终点、边权等）

    ```
    #include <iostream>
    #include <vector>

    using namespace std;

    int n, m;
    vector<bool> vis;
    vector<vector<int>> adj;

    // adj[u]存的是节点u的所有出度节点
    bool find_edge(int u,int v) {
        for (int i = 0; i <adj[u].size(); i++){
            if (adj[u][i] == v)
                return true;
        }
        return false;
    }

    void dfs(int u) {
        if (vis[u])
            return;
        vis[u] = true;
        for (int i = 0; i < adj[u].size(); i++){
            // adj[u][i]是存放的节点
            dfs(adj[u][i]);
        }
    }

    int main() {
        cin >> n >> m;
        vis.resize(n+1, false);
        adj.resize(n+1);
        
        for (int i = 0; i < m; i++){
            int u,v;
            cin >> u >> v;
            adj[u].emplace_back(v);
        }
        return 0;
    }
    ```
    **复杂度:**

    * 查询是否存在某条边：`o(1)`

    * 遍历一个点的所有出边：`o(n)`

    * 遍历整张图：`o(n+m)`

    * 空间复杂度: `o(n)`

    **适用场景：**

    > 存各种图都很适合，除非有特殊需求（如需要快速查询一条边是否存在，且点数较少，可以使用邻接矩阵）

    > 尤其适用于需要**对一个点的所有出边进行排序的场合**

### 拓扑排序

**拓扑排序要解决的问题是给一个图的所有节点排序**

比如学习大学课程中有：单变量微积分，线性代数，离散数学概述，概率论与统计学概述，语言基础，算法导论，机器学习。当我们想要学习 算法导论 的时候，就必须先学会离散数学概述和概率论与统计学概述，不然在课堂就会听的一脸懵逼。当然还有一个更加前的课程单变量微积分。**这些课程就相当于几个顶点u**, 顶点之间的有向边`(u,v)`就相当于学习课程的顺序。

**拓扑排序的目标是将所有节点排序，使得排在前面的节点不能依赖于排在后面的节点**

**Kahn算法：**

**初始状态**下，集合`S`装着所有入度为`0`的点，是一个空列表；

每次从`S`中取出一个点u`可以随便取`放入 , 然后将`u`的所有边`<u,v1>,<u,v2>,...,<u,vn>`删除。对于边`<u,v>`，若将该边删除后点`v`的入度变为0，则将`v`放入`S`中。

不断重复以上过程，直到集合`S`为空。**最后检查图中是否存在任何边，如果有，那么这个图一定有环路**，否则返回`L`，`L`中顶点的顺序就是拓扑排序的结果

**伪代码实现：**
```
L ← Empty list that will contain the sorted elements
S ← Set of all nodes with no incoming edges
while S is not empty do
    remove a node n from S
    insert n into L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S
if graph has edges then
    return error (graph has at least one cycle)
else
    return L (a topologically sorted order)
```
> 核心在于维持一个入度为0的集合

**例子：**
<img src="https://myimages-wqz.oss-cn-shanghai.aliyuncs.com/intern/202209060007398.png"/>

拓扑排序结果为：
2 -> 8 -> 0 -> 3 -> 7 -> 1 -> 5 -> 6 -> 9 -> 4 -> 11 -> 10 -> 12

**时间复杂度：**`O(E+V)`

**代码实现：**
```
// C++ Version
vector<int> G[MAXN];  // vector 实现的邻接表
int c[MAXN];          // 标志数组
vector<int> topo;     // 拓扑排序后的节点

bool dfs(int u) {
  c[u] = -1;
  for (int v : G[u]) {
    if (c[v] < 0)
      return false;
    else if (!c[v])
      if (!dfs(v)) return false;
  }
  c[u] = 1;
  topo.push_back(u);
  return true;
}

bool toposort() {
  topo.clear();
  memset(c, 0, sizeof(c));
  for (int u = 0; u < n; u++)
    if (!c[u])
      if (!dfs(u)) return false;
  reverse(topo.begin(), topo.end());
  return true;
}

```

**拓扑排序的应用：**
* 拓扑排序可以用来**判断图中是否有环**

* 还可以用来**判断图是否是一条链**

---
### 最短路

**最短路的定义：**
* `路径`
* 最短路
* `有向图`中的最短路、`无向图`中的最短路
* `单源`最短路、`每对结点`之间的最短路