#include<bits/stdc++.h>
using namespace std;

#define int long long
namespace MATRIX{

struct Matrix{
    static const int MAX = 100;
    static const int MOD = 1e9 + 7;
    int n, m;
    int mat[MAX][MAX];

    Matrix(){ _clear(); }
    Matrix(int _n, int _m): n(_n), m(_m){ _clear(); }
    Matrix(const vector<vector<int>>& arr){
        _clear(); _init(arr);
    }

    Matrix& operator = (const vector<vector<int>>& arr) { this->_init(arr); return *this; }
    bool operator == (const Matrix& other){
        if(n != other.n || m != other.m) return false;
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                if(mat[i][j] != other[i][j]) return false;
            }
        }

        return true;
    }

    void _clear(){
        memset(mat, 0, sizeof mat);
    }

    void _init(const vector<vector<int>>& arr){
        n = arr.size();
        m = arr[0].size();

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                mat[i][j] = arr[i][j];
            }
        }
    }

    static Matrix Identity(int n){
        Matrix I(n, n);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                I[i][j] = i == j;
            }
        }

        return I;
    }

    Matrix _M(int i, int j) const{
        Matrix sub(n - 1, m - 1);
        for(int ii = 0; ii < i; ++ii){
            for(int jj = 0; jj < j; ++jj){
                sub[ii][jj] = mat[ii][jj];
            }
            for(int jj = j + 1; jj < m; ++jj){
                sub[ii][jj - 1] = mat[ii][jj];
            }
        }
        for(int ii = i + 1; ii < n; ++ii){
            for(int jj = 0; jj < j; ++jj){
                sub[ii - 1][jj] = mat[ii][jj];
            }
            for(int jj = j + 1; jj < m; ++jj){
                sub[ii - 1][jj - 1] = mat[ii][jj];
            }
        }

        return sub;
    }

    // not recommended for large size
    int __cofactor(int i, int j) const{
        return ((i + j) % 2 ? -1 : 1) * _M(i, j).__det();
    }

    int __det() const{
        assert(n == m);
        if(n == 1 && m == 1) return mat[0][0];

        int res = 0;
        for(int j = 0; j < m; ++j){
            res += mat[0][j] * __cofactor(0, j);
        }

        return res;
    }

    Matrix __inv(){
        assert(n == m);
        Matrix res(n, m);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                res[i][j] = __cofactor(j, i);
            }
        }

        return res; // remember to divide by det()
    }

    Matrix Identity(){
        assert(n == m);
        return Matrix::Identity(n);
    }

    Matrix operator + (const Matrix& other) const{
        assert(n == other.n && m == other.m);
        Matrix res(n, m);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                res[i][j] = (this->mat[i][j] + other[i][j]) % MOD;
            }
        }

        return res;
    }

    Matrix operator - (const Matrix& other) const{
        assert(n == other.n && m == other.m);
        Matrix res(n, m);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                res[i][j] = (this->mat[i][j] - other[i][j]) % MOD;
            }
        }

        return res;
    }

    Matrix operator * (int k) const{
        Matrix res(n, m);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                res[i][j] = mat[i][j] * k % MOD;
            }
        }

        return res;
    }

    Matrix operator / (int k) const{
        Matrix res(n, m);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                res[i][j] = mat[i][j] / k; // use inverse modulo if necessary
            }
        }

        return res;
    }

    Matrix operator * (const Matrix& other) const{
        assert(m == other.n);
        Matrix res(n, other.m);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < other.m; ++j){
                for(int k = 0; k < m; ++k){
                    res[i][j] = (res[i][j] + mat[i][k] * other[k][j] % MOD) % MOD;
                }
            }
        }

        return res;
    }

    Matrix mul(int b){
        Matrix res(n, m);
        Matrix A = *this;

        while(b > 0){
            if(b & 1) res = res + A;
            A = A * 2;
            b >>= 1;
        }

        return res;
    }

    Matrix pow(int b){
        Matrix res = Identity();
        Matrix A = *this;

        while(b > 0){
            if(b & 1) res = res * A;
            A = A * A;
            b >>= 1;
        }

        return res;
    }

    void output(ostream& out = cerr) const{
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                out << mat[i][j] << ' ';
            }
            out << '\n';
        }
    }

    int* operator [] (int idx){ return mat[idx]; }
    const int* operator [] (int idx) const{ return mat[idx]; }
};

ostream& operator << (ostream& out, const Matrix& matrix){
    matrix.output(out);
    return out;
}

}
using namespace MATRIX;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    Matrix mat({
                {2, 4, 3},
                {5, 1, 6},
                {7, 2, 4}
               });

    cerr << mat * mat.__inv() / mat.__det() << '\n';

    return 0;
}
