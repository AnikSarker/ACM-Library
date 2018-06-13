//Matrix Exponentiation
int n;
struct Matrix{int m[MAX][MAX];};

Matrix Multiply(Matrix A,Matrix B){
    Matrix ans;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ans.m[i][j]=0;
            for(int k=1;k<=n;k++){
                ans.m[i][j]+=A.m[i][k]*B.m[k][j];
            }
        }
    }
    return ans;
}

Matrix Power(Matrix mat,int p){
    Matrix res;
    Matrix ans;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
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
