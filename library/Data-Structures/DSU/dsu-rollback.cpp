#include<bits/stdc++.h>
using namespace std;

struct DSU_Rollback{
    int n;
    vector<int> par, sz, sum;
    vector<tuple<int, int, int>> sta;
    int components;

    DSU_Rollback() = default;
    DSU_Rollback(int _sz): n(_sz){
        par.resize(n + 1, -1);
        sz.resize(n + 1);
        sum.resize(n + 1);
        components = 0;
    }

    void init(){
        for(int v = 1; v <= n; ++v)
            create(v);
    }

    void create(int v){
        if(par[v] == -1) ++components;

        par[v] = v;
        sz[v] = 1;
        sum[v] = 0;
    }

    int find(int v){ return par[v] == v ? v : find(par[v]); }
    int Sum(int u){ return sum[find(u)]; }
    int Size(int u){ return sz[find(u)]; }

    void add(int u, int k){
        u = find(u);
        sum[u] += k;
    }

    void pop(){
        if(sta.empty()) return;

        int u, siz, s; tie(u, siz, s) = sta.back();
        sta.pop_back();

        if(u == -1) return;

        sum[par[u]] = s;
        sz[par[u]] = siz;
        par[u] = u;
        ++components;
    }

    void unite(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b){
            sta.emplace_back(-1, -1, -1);
            return;
        }

        if(sz[a] < sz[b]) swap(a, b);

        sta.emplace_back(b, sz[a], sum[a]);
        par[b] = a;
        sz[a] += sz[b];
        sum[a] += sum[b];
        --components;
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    DSU_Rollback dsu(n);
    dsu.init();

    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        dsu.add(i, cur);
    }

    while(q--){
        int type; cin >> type;

        if(type == 0){
            int u, v;
            cin >> u >> v;

            dsu.unite(u, v);
        }
        else if(type == 1){
            dsu.pop();
        }
        else if(type == 2){
            int u, k;
            cin >> u >> k;

            dsu.add(u, k);
        }
        else if(type == 3){
            cout << dsu.components << '\n';
        }
        else if(type == 4){
            int u;
            cin >> u;

            cout << dsu.Size(u) << '\n';
        }
        else if(type == 5){
            int u;
            cin >> u;

            cout << dsu.Sum(u) << '\n';
        }
    }

    return 0;
}
