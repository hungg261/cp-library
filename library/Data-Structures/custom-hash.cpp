#include <bits/stdc++.h>
using namespace std;

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename K, typename V>
using umap = unordered_map<K, V, chash>;

#define TEST
#ifdef TEST
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int Q;
    cin >> Q;

    umap<long long, long long> mp;
    while(Q--) {
        int type;
        cin >> type;

        if(type == 0) {
            long long k, v;
            cin >> k >> v;

            mp[k] = v;
        }
        else {
            long long k;
            cin >> k;

            cout << mp[k] << '\n';
        }
    }


    return 0;
}
#endif
