/*
Checkers:
- https://judge.yosupo.jp/problem/point_add_range_sum
*/
#include<bits/stdc++.h>
using namespace std;

template<typename T = int>
struct SegmentTree{
    struct Node{
        T value;

        Node() = default;
        Node(T _value): value(_value){}

        static Node Identity(){
            return Node(0);
        }

        Node merge(const Node& other){
            return Node(value + other.value);
        }
    };

    int n;
    vector<Node> nodes;

    SegmentTree() = default;
    SegmentTree(int sz): n(sz){
        nodes.resize(n * 4 + 1);
    }

    void build(int id, int l, int r, const vector<T>& arr){
        if(l == r){
            nodes[id].value = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(id << 1, l, mid, arr);
        build(id << 1 | 1, mid + 1, r, arr);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    void update(int id, int l, int r, int idx, T val){
        if(r < idx || idx < l) return;
        if(l == r){
            nodes[id].value = val;
            return;
        }

        int mid = (l + r) >> 1;
        update(id << 1, l, mid, idx, val);
        update(id << 1 | 1, mid + 1, r, idx, val);
        nodes[id] = nodes[id << 1].merge(nodes[id << 1 | 1]);
    }

    Node get(int id, int l, int r, int u, int v){
        if(r < u || v < l) return Node::Identity();
        if(u <= l && r <= v) return nodes[id];

        int mid = (l + r) >> 1;
        return get(id << 1, l, mid, u, v).merge(get(id << 1 | 1, mid + 1, r, u, v));
    }

    void build(const vector<T>& arr){ build(1, 1, n, arr); }
    void update(int idx, T val){ update(1, 1, n, idx, val); }
    Node get(int u, int v){ return get(1, 1, n, u, v); }
};

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<long long> arr(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    SegmentTree<long long> segtree(n);
    segtree.build(arr);

    while(q--){
        int type;
        cin >> type;

        if(type == 0){
            int p;
            long long x;
            cin >> p >> x;

            ++p;

            long long cur = segtree.get(p, p).value;
            segtree.update(p, cur + x);
        }
        else{
            int l, r;
            cin >> l >> r;

            ++l;
            ++r;

            cout << segtree.get(l, r - 1).value << '\n';
        }
    }

    return 0;
}
#endif
