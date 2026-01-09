#include<bits/stdc++.h>
using namespace std;

const int MAXN = 10000;
int n, m;
vector<int> adj[MAXN + 5];

int low[MAXN + 5], tin[MAXN + 5], Time = 0;
int joint[MAXN + 5], bridges = 0;
void dfs_tree(int u, int prv){
    tin[u] = low[u] = ++Time;
    int child = 0;
    for(int v: adj[u]){
        if(v == prv) continue;

        if(!tin[v]){
            dfs_tree(v, u);
            low[u] = min(low[u], low[v]);

            if(low[v] > tin[u]) ++bridges; // (u, v) is a bridge
            if(prv == -1){
                ++child;
                if(child > 1) joint[u] = true;
            }
            else if(low[v] >= tin[u]) joint[u] = true;
        }
        else low[u] = min(low[u], tin[v]);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int u = 1; u <= n; ++u) dfs_tree(u, -1);

    int articulations = 0;
    for(int u = 1; u <= n; ++u) if(joint[u]) ++articulations;

    cout << articulations << ' ' << bridges << '\n';

    return 0;
}
