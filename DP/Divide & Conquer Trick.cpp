/// DP optimization divide and conquer trick O(nlogn)
/// dp[i][j] = min(dp[i-1][k]+C[k][j]) [ k < j ]

///To use D&Q Its sufficient to prove the following
/// Cost(l + 1 , j + 1) - Cost(l + 1, j) <= Cost(k + 1, j + 1) - Cost(k + 1, j) for any(l < k < j)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m, n, x, y, z, p, q, r, K, t, cs = 1;
ll segor[5002][5002];
ll ara[5002];
ll dp[5002][5002];

void compute(ll K, ll l, ll r, ll optl, ll optr){
    if(l > r) return;
    ll mid = (l + r) / 2;
    ll optnow = optl;

    dp[K][mid] = 0;
    ll tmpoptl = min(optr, mid);

    for(ll i = optl; i <= tmpoptl; i++){
        ll tmp = dp[K - 1][i] + segor[i + 1][mid];
        if(tmp > dp[K][mid]){
            dp[K][mid] = tmp;
            optnow = i;
        }
    }
    compute(K, l, mid - 1, optl, optnow);
    compute(K, mid + 1, r, optnow, optr);
}

int main(){
    cin >> t;

    while(t--){
        scanf("%lld %lld", &n, &K);
        for(ll i = 1; i <= n; i++) scanf("%lld", &ara[i]);

        for(ll i = 1; i <= n; i++){
            segor[i][i - 1] = 0;
            for(ll j = i; j <= n; j++) segor[i][j] = segor[i][j - 1] | ara[j];
        }

        for(ll i = 1; i <= n; i++) dp[1][i] = segor[1][i];

        for(ll i = 2; i <= K; i++) {
            compute(i, 1, n, 1, n);
        }
        printf("%lld\n", dp[K][n]);
    }
}
