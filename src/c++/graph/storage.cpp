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