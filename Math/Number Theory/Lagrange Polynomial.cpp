//Lagrange Polynomial
//lagrange(n,k) = 1^k + 2^k + 3^k + ... + n^k modulo Prime
//Complexity : O(k log (MOD))

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000010            // Upper Limit of k
#define MOD 1000000007
#define ll long long int

namespace lgr{
    short factor[MAX];
    int P[MAX],S[MAX],ar[MAX],inv[MAX];

    inline int Add(int a,int b) {return a + b >= MOD ? a + b - MOD : a + b;}
    inline int Sub(int a,int b) {return a - b < 0 ? a - b + MOD : a - b;}

    inline int bigMod(ll a,ll b){
        ll res = 1;
        while(b){
            if(b&1) res = (res * a) % MOD;
            a = (a * a) % MOD; b >>= 1;
        }
        return res;
    }

    int lagrange(ll n,int k){
        if(!k) return ( n % MOD );

        if(!inv[0]){
            int x = 1;
            for(int i = 2; i < MAX; i++) x = (ll)x * i % MOD;
            inv[MAX-1] = bigMod(x,MOD-2);
            for(int i = MAX-2; i>=0; i--) inv[i] = (ll)inv[i+1] * (i+1) %MOD;
            for(int i = 0;i < MAX; i++)  factor[i] = 0;
            for(int i = 4;i < MAX; i+=2) factor[i] = 2;
            for(int i = 3; i * i < MAX; i+=2){
                if(!factor[i])
                    for(int j = i*i; j<MAX; j += i + i) factor[j] = i;
            }
        }

        k++;
        ar[0] = 0, ar[1] = 1;
        for(int i=2;i<=k;i++){
            if(!factor[i]) ar[i] = bigMod(i,k-1);
            else ar[i] = (ll) ar[factor[i]] * ar[i/factor[i]] % MOD;
        }
        for(int i = 1; i <= k; i++) ar[i] = Add(ar[i], ar[i-1]);
        if(n <= k) return ar[n];

        P[0]=1, S[k]=1;
        for(int i = 1; i <= k; i++)   P[i] = (n-i+1) % MOD * P[i-1] % MOD;
        for(int i = k-1; i >= 0; i--) S[i] = (n-i-1) % MOD * S[i+1] % MOD;

        int res = 0;
        for (int i = 0; i <= k; i++){
            int x = (ll) ar[i] * P[i] % MOD * S[i] % MOD * inv[k - i] % MOD * inv[i] % MOD;
            if((k-i) & 1) res = Sub(res,x);
            else res = Add(res, x);
        }
        return res;
    }
}

int main(){
    ll n; int k;
    scanf("%lld %d",&n,&k);
    printf("%d\n",lgr::lagrange(n, k));
}
