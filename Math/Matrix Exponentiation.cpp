//Matrix Exponentiation
typedef long long ll;
const ll mod = 1e9 + 7;
ll mod2 = mod * mod * 5;
const ll MAX = 105;

struct Matrix{
    ll row, col;
    ll m[MAX][MAX];
};

Matrix Multiply(Matrix A,Matrix B){
    Matrix ans;

    ans.row = A.row;
    ans.col = B.col;

    for(ll i=1;i<=A.row;i++){
        for(ll j=1;j<=B.col;j++){
            ans.m[i][j]=0;
            ll sm = 0;
            for(ll k=1;k<=A.col;k++){
                sm+=(A.m[i][k]*B.m[k][j]);
                if(sm >= mod2) sm -= mod2;
                ans.m[i][j]+=A.m[i][k]*B.m[k][j];
//              ans.m[i][j] = ans.m[i][j] % mod;
            }
            ans.m[i][j] = sm % mod;
        }
    }
    return ans;
}

Matrix Power(Matrix mat,ll p){
    Matrix res;
    Matrix ans;

    ans.row = res.row = mat.row;
    ans.col = res.col = mat.col;
    ll n = ans.row;

    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=n;j++){
            ans.m[i][j]=0;
            res.m[i][j]=mat.m[i][j];
        }
        ans.m[i][i]=1;
    }

    while(p){
        if(p%2==1) ans=Multiply(ans,res);
        res=Multiply(res,res);
        p=p/2;
    }
    return ans;
}
