/*
Checkers:
- https://judge.yosupo.jp/problem/primality_test
- https://www.spoj.com/problems/PON
*/
#include<bits/stdc++.h>
using namespace std;

namespace Rabin_Miller{

#define int long long
int mulmod(int a, int b, int m){
    return (__int128)a * b % m;
    // return a * b % m;
}

int powmod(int a, int b, int m){
    a %= m;
    int res = 1;

    while(b > 0){
        if(b & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        b >>= 1;
    }

    return res;
}

bool check(int a, int n, int s, int d){
    int x = powmod(a, s, n);
    if(x == 1 || x == n - 1) return true;

    while(d--){
        x = mulmod(x, x, n);
        if(x == n - 1) return true;
    }

    return false;
}

bool rabin_miller(int n){
    if(n < 2) return false;
    if(n == 2 || n == 3 || n == 5 || n == 7) return true;
    if(n % 2 == 0) return false;
    if(n % 3 == 0) return false;
    if(n % 5 == 0) return false;
    if(n % 7 == 0) return false;

    int s = n - 1, d = 0;
    while(s % 2 == 0){
        s /= 2;
        ++d;
    }

    vector<int> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
    for(int a: bases){
        if(a >= n) break;

        if(!check(a, n, s, d)){
            return false;
        }
    }

    return true;
}

}
using namespace Rabin_Miller;

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int Q;
    cin >> Q;

    while(Q--){
        int n;
        cin >> n;

        cout << (rabin_miller(n) ? "Yes" : "No") << '\n';
    }

    return 0;
}
#endif
