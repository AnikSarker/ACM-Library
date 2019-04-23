//Gaussian Elimination
//format : (a[0]*x[0]+a[1]*x[1] ... a[m-1]*x[m-1]) % k = a[m], where 0 <= ai < k
//number of solution : k^(number of free variable) = k^(n-rank)

int gcdExtended(int a, int b, int& x, int& y){
    if(a==0) {x=0;y=1; return b;}
    int x1,y1;
    int gcd = gcdExtended(b%a,a,x1,y1);
    x=y1-(b/a)*x1;
    y=x1;
    return gcd;
}

int modinverse(int x,int y) {int a,b; gcdExtended(x,y,a,b); return a;}

//n equations (n rows), m variables (m+1 columns)
void Gauss(int n,int m,int k){
    int r,c;
    for(r=0,c=0;r<n && c<m;c++){
        for(int i=r+1;i<n;i++) if(abs(A[i][c])>abs(A[r][c])) swap(A[i],A[r]);
        if(!A[r][c]) continue;
        int s = modinverse(A[r][c],k);
        for(int i=r+1;i<n;i++) if(A[i][c]){
            int w = (s*A[i][c])%k;
            for(int j=c;j<=m;j++){A[i][j]-=(A[r][j]*w)%k; A[i][j]%=k; if(A[i][j]<0) A[i][j]+=k;}
        }
        r++;
    }
    //Rank = r
    for(int i=r;i<n;i++) if(A[i][m]) return;  //No solution

    //Unique Solution for r variables
    for(int i=r-1;i>=0;i--){
        x[i]=A[i][m];
        for(int j=i+1;j<m;j++) {x[i]-=(A[i][j]*x[j])%k; x[i]%=k; if(x[i]<0) x[i]+=k;}

        int inv=modinverse(A[i][i],k);
        x[i]=(x[i]*inv)%k; if(x[i]<0) x[i]+=k;
    }
}
