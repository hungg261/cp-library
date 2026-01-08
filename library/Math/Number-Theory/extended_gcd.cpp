/*
Checkers:
- https://oj.hncode.edu.vn/problem/currency (personal)
*/
#include<bits/stdc++.h>
using namespace std;

#define int long long

int extended_gcd(int a, int b, int& x, int& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

//#define TEST
#ifdef TEST
bool check(int a, int b, int c){
    int x, y;
    int g = extended_gcd(a, b, x, y);

    if(c % g != 0){
        return false;
    }

    x *= c / g;
    y *= c / g;


    int tmin = ceil(-1.0 * x * g / b),
        tmax = floor(1.0 * y * g / a);

    return tmin <= tmax;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, a, b;
    int cnt = 0;

    cin >> n >> a >> b;
    for(int i = 1; i <= n; ++i){
        int c; cin >> c;
        cnt += check(a, b, c);
    }

    cout << cnt << ' ' << n - cnt << '\n';

    return 0;
}
#endif
