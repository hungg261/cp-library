#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int n, m;
vector<int> adj[MAXN + 5];
int low[MAXN + 5], tin[MAXN + 5], Time = 0;

void dfs_tree(int u, int prv){
    tin[u] = low[u] = ++Time;
    for(int v: adj[u]){
        if(v == prv) continue;

        if(!tin[v]){
            dfs_tree(v, u);
            low[u] = min(low[u], low[v]);
        }
        else low[u] = min(low[u], tin[v]);
    }
 }

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs_tree(1, -1);

    return 0;
}
#endif
