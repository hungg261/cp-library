#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 5e5;
int nodes[MAXN * 4 + 5];

void update(int id, int l, int r, int idx, int val){
    if(r < idx || idx < l) return;
    if(l == r){
        nodes[id] = val;
        return;
    }

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, idx, val);
    update(id << 1 | 1, mid + 1, r, idx, val);
    nodes[id] = nodes[id << 1] + nodes[id << 1 | 1];
}

int get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return nodes[id];

    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; ++i){
        int cur;
        cin >> cur;

        update(1, 1, n, i, cur);
    }

    while(q--){
        int type;
        cin >> type;

        if(type == 0){
            int p, x;
            cin >> p >> x;
            ++p;

            int cur = get(1, 1, n, p, p);
            update(1, 1, n, p, cur + x);
        }
        else{
            int l, r;
            cin >> l >> r;
            ++l; ++r;

            cout << get(1, 1, n, l, r - 1) << '\n';
        }
    }

    return 0;
}
#endif
