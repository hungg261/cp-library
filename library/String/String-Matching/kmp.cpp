/*
Checkers:
- https://oj.vnoi.info/problem/substr
*/
#include<bits/stdc++.h>
using namespace std;

vector<int> KMP(const string& S){
    int n = S.size();

    vector<int> pi(n);
    pi[0] = 0;
    for(int i = 1; i < n; ++i){
        int j = pi[i - 1];
        while(j > 0 && S[j] != S[i]){
            j = pi[j - 1];
        }

        if(S[j] == S[i]) ++j;
        pi[i] = j;
    }

    return pi;
}

//#define TEST
#ifdef TEST
signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    string A, B;
    cin >> A >> B;

    vector<int> pi = KMP(B + "#" + A);
    int sz = pi.size();

    int sz_b = B.size();
    for(int i = sz_b + 1; i < sz; ++i){
        if(pi[i] == sz_b){
            cout << i - sz_b * 2 + 1 << ' ';
        }
    }

    return 0;
}
#endif
