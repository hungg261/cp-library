/*
Checkers:
- https://judge.yosupo.jp/problem/point_add_range_sum
*/

#include<bits/stdc++.h>
using namespace std;

#define int long long
struct Node{
    int value;
    Node *l, *r;

    Node(int _value = 0): value(_value), l(NULL), r(NULL){}

    static int Identity(){
        return 0;
    }

    void create_children(){
        if(!this->l) this->l = new Node();
        if(!this->r) this->r = new Node();
    }

    void merge(){
        value = l->value + r->value;
    }
};

void update(Node *node, int l, int r, int idx, int val){
    if(r < idx || idx < l) return;
    if(l == r){
        node->value = val;
        return;
    }

    node->create_children();

    int mid = (l + r) >> 1;
    update(node->l, l, mid, idx, val);
    update(node->r, mid + 1, r, idx, val);
    node->merge();
}

int get(Node *node, int l, int r, int u, int v){
    if(!node || r < u || v < l) return Node::Identity();
    if(u <= l && r <= v){
        return node->value;
    }

    int mid = (l + r) >> 1;
    return get(node->l, l, mid, u, v) + get(node->r, mid + 1, r, u, v);
}

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    Node *root = new Node();

    int n, Q;
    cin >> n >> Q;

    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        update(root, 1, n, i, cur);
    }
    while(Q--){
        int type;
        cin >> type;

        if(type == 0){
            int p, x;
            cin >> p >> x;

            ++p;
            int cur = get(root, 1, n, p, p);
            update(root, 1, n, p, cur + x);
        }
        else{
            int l, r;
            cin >> l >> r;

            ++l; ++r;
            int res = get(root, 1, n, l, r - 1);

            cout << res << '\n';
        }
    }

    return 0;
}
#endif
