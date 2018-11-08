#include<bits/stdc++.h>
using namespace std;
#define MAX 105
#define ll long long int
const ll MOD = 1e9 + 7;
const ll MOD2 = MOD * MOD * 3;

inline int bigMod(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=(res*a)%MOD;
        a=(a*a)%MOD; b>>=1;
    }
    return res;
}

inline int inv(ll n) {return bigMod(n,MOD-2);}
inline int Mul(ll a,ll b) {return (a*b)%MOD;}
inline int Div(ll a,ll b) {return Mul(a,inv(b));}

struct Matrix{
    int row, col;
    int m[4][4];
    Matrix() {row = col = 3; memset(m,0,sizeof(m));}
    Matrix(int r,int c) {row = r; col = c; memset(m,0,sizeof(m));}
};

Matrix Multiply(Matrix A,Matrix B){
    Matrix ans(A.row,B.col);

    for(int i=1;i<=A.row;i++){
        for(int j=1;j<=B.col;j++){
            ans.m[i][j]=0;
            ll sm = 0;
            for(int k=1;k<=A.col;k++){
                sm+=(A.m[i][k]*B.m[k][j]);
                if(sm >= MOD2) sm -= MOD2;
            }
            ans.m[i][j] = sm % MOD;
        }
    }
    return ans;
}

Matrix Power(Matrix mat,ll p){
    Matrix res(mat.row , mat.col);
    Matrix ans(mat.row , mat.col);

    int n = ans.row;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ans.m[i][j]=0;
            res.m[i][j]=mat.m[i][j];
        }
        ans.m[i][i]=1;
    }

    while(p){
        if(p&1) ans=Multiply(ans,res);
        res=Multiply(res,res);
        p=p/2;
    }
    return ans;
}

int Det(Matrix mat){
    assert(mat.row == mat.col);
    int n = mat.row;
    for(int i = 1; i <= n; i++)
        for (int j = 1; j <= n; ++j){
            mat.m[i][j] %= MOD;
            if(mat.m[i][j] < 0) mat.m[i][j] += MOD;
        }

    ll ret = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            while(mat.m[j][i]){
                int t = mat.m[i][i] / mat.m[j][i];
                for (int k = i; k <= n; ++k) {
                    mat.m[i][k] -= Mul(mat.m[j][k] , t);
                    if(mat.m[i][k] < 0) mat.m[i][k] += MOD;
                    swap(mat.m[j][k], mat.m[i][k]);
                }
                ret = MOD - ret;
            }
        if(mat.m[i][i] == 0) return 0;
        ret = Mul(ret , mat.m[i][i]);
    }
    if(ret < 0) ret += MOD;
    return ret;
}

//Freivalds algorithm : check whether AB = C
//Complexity : O(iteration * n^2)
int p[MAX],q[MAX],r[MAX];
bool Freivalds(Matrix A,Matrix B,Matrix C){
    srand(time(NULL));
    int n=A.row;
    int iteration=15;

    int Yes=0;
    for(int i=1;i<=iteration;i++){
        for(int i=1;i<=n;i++) r[i] = rand()%2;
        for(int i=1;i<=n;i++) p[i] = q[i] = 0;

        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
                p[i] += r[j] * A.m[i][j];
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
                q[i] += p[j] * B.m[i][j];
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
                q[i] -= r[j] * C.m[i][j];
        
        bool All = true;
        for(int i=1;i<=n;i++) if(q[i]) All=false;
        if(All) Yes++;
    }
    return Yes == iteration;
}
