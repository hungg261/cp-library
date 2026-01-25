#include<bits/stdc++.h>
using namespace std;

struct FenwickTree2D{
    int n, m;

    vector<int> Xvalues, Yvalues;

    vector<vector<int>> BIT;
    int sz_n, sz_m;

    FenwickTree2D() = default;
    FenwickTree2D(int _n, int _m): n(_n), m(_m){}

    void fake_point(int x, int y){
        for(int i = x; i <= n; i += i & -i){
            Xvalues.push_back(i);

            for(int j = y; j <= m; j += j & -j){
                Yvalues.push_back(j);
            }
        }
    }

    void fake_rect(int x1, int y1, int x2, int y2){
        fake_point(x2, y2);
        fake_point(x1 - 1, y2);
        fake_point(x2, y1 - 1);
        fake_point(x1 - 1, y1 - 1);
    }

    int vx(int v){ return lower_bound(begin(Xvalues), end(Xvalues), v) - begin(Xvalues) + 1; }
    int vy(int v){ return lower_bound(begin(Yvalues), end(Yvalues), v) - begin(Yvalues) + 1; }

    void build(){
        Xvalues.push_back(0);
        Yvalues.push_back(0);

        sort(begin(Xvalues), end(Xvalues));
        Xvalues.erase(unique(begin(Xvalues), end(Xvalues)), end(Xvalues));
        sz_n = Xvalues.size();

        sort(begin(Yvalues), end(Yvalues));
        Yvalues.erase(unique(begin(Yvalues), end(Yvalues)), end(Yvalues));
        sz_m = Yvalues.size();


        BIT.resize(sz_n + 1, vector<int>(sz_m + 1, 0));
    }

    void add(int x, int y, int val){
        for(int i = vx(x); i <= sz_n; i += i & -i){
            for(int j = vy(y); j <= sz_m; j += j & -j){
                BIT[i][j] += val;
            }
        }
    }

    int get(int x, int y){
        int res = 0;
        for(int i = vx(x); i > 0; i -= i & -i){
            for(int j = vy(y); j > 0; j -= j & -j){
                res += BIT[i][j];
            }
        }

        return res;
    }

    int get(int x1, int y1, int x2, int y2){
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);



    return 0;
}
