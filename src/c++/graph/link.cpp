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