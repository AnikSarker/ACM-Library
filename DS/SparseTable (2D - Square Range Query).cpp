#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int LOGN = 10;
int A[MAXN][MAXN];
int M[MAXN][MAXN][LOGN];

//O(n^2 logn)
//Supports Square Query
void Build2DSparse(int n){
    for(int k=0; (1<<k) <= n; k++){
        for(int i=1; i+(1<<k)-1 <= n; i++){
            for(int j=1; j+(1<<k)-1 <= n; j++){
                if(k==0) M[i][j][k] = A[i][j];
                else{
                    int add = 1<<(k-1);
                    int ret1 = max(M[i][j][k-1], M[i+add][j][k-1]);
                    int ret2 = max(M[i][j+add][k-1], M[i+add][j+add][k-1]);
                    M[i][j][k] = max(ret1, ret2);
                }
            }
        }
    }
}

//returns max of all A[i][j], where p<=i<=p+s-1 and q<=j<=q+s-1
int Query(int p, int q, int s){
    int k = log2(s);
    int add = 1<<k;
    int ret1 = max(M[p][q][k], M[p+s-add][q][k]);
    int ret2 = max(M[p][q+s-add][k], M[p+s-add][q+s-add][k]);
    return max(ret1, ret2);
}
