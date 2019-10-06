// Complexity : O(n log n)
// dp[i][j] = min(dp[i-1][k-1] + C[k][j]) [ k <= j ]
// To use D&Q, its sufficient to prove the following :
// Cost(L + 1 , j + 1) - Cost(L + 1, j) <= Cost(k + 1, j + 1) - Cost(k + 1, j) for any(L < k < j) For Max Query
// Cost(L + 1 , j + 1) - Cost(L + 1, j) >= Cost(k + 1, j + 1) - Cost(k + 1, j) for any(L < k < j) For Min Query

#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int MAX = 5005;

int ara[MAX];
ll dp[2][MAX];
ll C[MAX][MAX];

void compute(int K, int L, int R, int OptL, int OptR){
    if(L > R) return;
    int mid = (L + R) / 2;

    int optNow = -1;
    dp[K & 1][mid] = 0;
    for(int i=OptL; i<=min(OptR, mid); i++){
        ll tmp = dp[(K & 1) ^ 1][i - 1] + C[i][mid];
        if(tmp >= dp[K & 1][mid]){
            dp[K & 1][mid] = tmp;
            optNow = i;
        }
    }
    compute(K, L, mid - 1, OptL, optNow);
    compute(K, mid + 1, R, optNow, OptR);
}

int main(){
    int t;
    scanf("%d",&t);

    while(t--){
        int n, K;
        scanf("%d %d", &n, &K);
        for(int i=1; i<=n; i++) scanf("%d",&ara[i]);

        for(int i=1; i<=n; i++){
            for(int j=i; j<=n; j++){
                if(i==j) C[i][j] = ara[j];
                else C[i][j] = C[i][j-1] | ara[j];
            }
        }

        for(int i=1; i<=n; i++) dp[1][i] = C[1][i];
        for(int i=2; i<=K; i++) compute(i, 1, n, 1, n);
        printf("%lld\n", dp[K & 1][n]);
    }
}
