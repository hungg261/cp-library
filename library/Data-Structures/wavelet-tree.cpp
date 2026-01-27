#include<bits/stdc++.h>
using namespace std;

#define int long long

struct WaveletTree{
    int lo, hi;
    vector<int> pref, psum;
    WaveletTree *l, *r;

    WaveletTree(int *from, int *to, int L, int R){
        lo = L; hi = R;
        l = r = nullptr;
        if(from >= to) return;

        int mid = (lo + hi) >> 1;
        auto f = [&mid](int x){ return x <= mid; };

        pref.push_back(0);
        psum.push_back(0);
        for(auto it = from; it != to; ++it){
            pref.push_back(pref.back() + f(*it));
            psum.push_back(psum.back() + *it);
        }

        if(lo == hi) return;

        auto pivot = stable_partition(from, to, f);
        l = new WaveletTree(from, pivot, lo, mid);
        r = new WaveletTree(pivot, to, mid + 1, hi);
    }

    int kth(int lq, int rq, int k){
        if(lq > rq) return -1;
        if(lo == hi) return lo;

        int inLeft = pref[rq] - pref[lq - 1];
        if(k <= inLeft) return l->kth(pref[lq - 1] + 1, pref[rq], k);
        else return r->kth(lq - pref[lq - 1], rq - pref[rq], k - inLeft);
    }

    int cnt_leq(int lq, int rq, int x){
        if(lq > rq) return 0;
        if(lo > x) return 0;
        if(hi <= x) return rq - lq + 1;

        return l->cnt_leq(pref[lq - 1] + 1, pref[rq], x) +
                r->cnt_leq(lq - pref[lq - 1], rq - pref[rq], x);
    }

    int sum_leq(int lq, int rq, int x){
        if(lq > rq) return 0;
        if(lo > x) return 0;
        if(hi <= x) return psum[rq] - psum[lq - 1];

        return l->sum_leq(pref[lq - 1] + 1, pref[rq], x) +
                r->sum_leq(lq - pref[lq - 1], rq - pref[rq], x);
    }

    int cnt_eq(int lq, int rq, int x){
        if(lq > rq || hi < x || x < lo) return 0;
        if(lo == hi) return rq - lq + 1;

        int mid = (lo + hi) >> 1;
        if(x <= mid) return l->cnt_eq(pref[lq - 1] + 1, pref[rq], x);
        else return r->cnt_eq(lq - pref[lq - 1], rq - pref[rq], x);
    }
};

const int MAXN = 1e5;
int arr[MAXN + 5], n;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> arr[i];

    WaveletTree wlt(arr + 1, arr + n + 1, -100, 100);

    int q;
    cin >> q;

    while(q--){
        int l, r, k;
        cin >> l >> r >> k;

        cout << wlt.sum_leq(l, r, k) << '\n';
    }

    return 0;
}
