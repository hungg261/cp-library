/*
Checkers:
- https://judge.yosupo.jp/problem/unionfind
*/
#include<bits/stdc++.h>
using namespace std;

struct DSU{
    int n;
    vector<int> par, sz;

    DSU() = default;
    DSU(int _sz): n(_sz){
        par.resize(n + 1);
        sz.resize(n + 1);
    }

    void init(){
        for(int u = 0; u <= n; ++u)
            create(u);
    }

    void create(int v){
        par[v] = v;
        sz[v] = 1;
    }

    int find_set(int v){
        return par[v] == v ? v : find_set(par[v]);
    }

    bool same(int u, int v){
        return find_set(u) == find_set(v);
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

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, Q;
    cin >> n >> Q;

    DSU dsu(n);
    dsu.init();
    while(Q--){
        int type, u, v;
        cin >> type >> u >> v;

        if(type == 0){
            dsu.union_sets(u, v);
        }
        else{
            bool ok = dsu.same(u, v);
            cout << (ok ? "1" : "0") << '\n';
        }
    }

    return 0;
}
#endif
