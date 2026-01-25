/**
 * Algorithm: Boruvka's Algorithm (MST)
 * Checker(s):
    - https://www.spoj.com/problems/MST
 * Notes:
    - Graph assumed to be connected
 */
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
        return par[v] == v ? v : par[v] = find_set(par[v]);
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

const int MAXN = 1e5;
int n, m;
struct Edge{
    int u, v, w;

    bool null(){
        return u == -1;
    }
};
vector<Edge> edges;
int best_edges[MAXN + 5];

long long Boruvka(){
    int components = n;
    DSU dsu(n);
    dsu.init();

    long long mst = 0;
    while(components > 1){
        for(int c = 1; c <= n; ++c)
            best_edges[c] = -1;

        for(int i = 0; i < m; ++i){
            const Edge& e = edges[i];
            int cu = dsu.find_set(e.u),
                cv = dsu.find_set(e.v);
            if(cu == cv) continue;

            if(best_edges[cu] == -1 || e.w < edges[best_edges[cu]].w) best_edges[cu] = i;
            if(best_edges[cv] == -1 || e.w < edges[best_edges[cv]].w) best_edges[cv] = i;
        }

        for(int c = 1; c <= n; ++c){
            if(dsu.find_set(c) != c) continue;

            const Edge& e = edges[best_edges[c]];
            if(!dsu.same(e.u, e.v)){
                dsu.union_sets(e.u, e.v);
                mst += e.w;

                --components;
            }
        }
    }

    return mst;
}
