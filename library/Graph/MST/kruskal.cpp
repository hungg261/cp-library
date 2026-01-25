/**
 * Algorithm: Kruskal's Algorithm (MST)
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

    int find(int v){
        return par[v] == v ? v : par[v] = find(par[v]);
    }

    bool same(int u, int v){
        return find(u) == find(v);
    }

    bool unite(int a, int b){
        a = find(a);
        b = find(b);

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

long long kruskal(){
    sort(begin(edges), end(edges));
    long long mst = 0;

    DSU dsu(n);
    dsu.init();
    for(const Edge& e: edges){
        if(dsu.unite(e.u, e.v)){
            mst += e.w;
        }
    }

    return mst;
}
