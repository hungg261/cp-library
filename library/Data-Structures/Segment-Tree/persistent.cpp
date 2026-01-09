/*
Checkers:
- https://cses.fi/problemset/task/1737
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Node{
    int value;
    Node *l, *r;

    Node(int _value = 0): value(_value), l(NULL), r(NULL){}
    Node(Node *_l, Node *_r): value(_l->value + _r->value), l(_l), r(_r){}
    Node(Node *node): value(node->value), l(node->l), r(node->r){}
};

const int MAXN = 2e5, MAXQ = 2e5;
int arr[MAXN + 5], n, q;
Node* nodes[MAXQ + 5];

Node *build(int l, int r){
    if(l == r){
        return new Node(arr[l]);
    }

    int mid = (l + r) >> 1;
    return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *node, int l, int r, int idx, int val){
    if(l == r){
        return new Node(val);
    }

    int mid = (l + r) >> 1;
    if(idx <= mid) return new Node(update(node->l, l, mid, idx, val), node->r);
    else return new Node(node->l, update(node->r, mid + 1, r, idx, val));
}

int get(Node *node, int l, int r, int u, int v){
    if(!node || r < u || v < l) return 0;
    if(u <= l && r <= v) return node->value;

    int mid = (l + r) >> 1;
    return get(node->l, l, mid, u, v) + get(node->r, mid + 1, r, u, v);
}

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    int cur = 0;
    nodes[++cur] = build(1, n);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int k, a, x;
            cin >> k >> a >> x;

            nodes[k] = update(nodes[k], 1, n, a, x);
        }
        else if(type == 2){
            int k, a, b;
            cin >> k >> a >> b;

            cout << get(nodes[k], 1, n, a, b) << '\n';
        }
        else{
            int k;
            cin >> k;

            nodes[++cur] = new Node(nodes[k]);
        }
    }

    return 0;
}
#endif
