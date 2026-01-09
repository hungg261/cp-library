/**
 * Algorithm: Kruskal's Algorithm (MST)
 * Notes:
    - Graph assumed to be connected
 */
#include<bits/stdc++.h>
using namespace std;

#define int long long

struct DSU{
    int n;
    vector<int> sz, par;

    DSU(int _sz): n(_sz){
        sz.resize(n + 1);
        par.resize(n + 1);
    }

    void init(){
        for(int u = 0; u <= n; ++u){
            create(u);
        }
    }

    void create(int v){
        par[v] = v;
        sz[v] = 1;
    }

    int find_set(int v){
        return par[v] == v ? v : par[v] = find_set(par[v]);
    }

    bool union_sets(int a, int b){
        a = find_set(a);
        b = find_set(b);

        if(a != b){
            if(sz[a] < sz[b]) swap(a, b);

            par[b] = a;
            sz[a] += sz[b];
            return true;
        }

        return false;
    }
};

struct Edge{
    int u, v, w;

    bool operator < (const Edge& other) const{
        return this->w < other.w;
    }
};

int n, m;
vector<Edge> edges;

int kruskal(){
    sort(begin(edges), end(edges));
    int mst = 0;

    DSU dsu(n);
    dsu.init();
    for(const Edge& e: edges){
        if(dsu.union_sets(e.u, e.v)){
            mst += e.w;
        }
    }

    return mst;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;

        edges.push_back({a, b, c});
    }

    int mst = kruskal();
    cout << mst << '\n';

    return 0;
}
