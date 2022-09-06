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