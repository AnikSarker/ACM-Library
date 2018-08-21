//Lagrange Polynomial
//lagrange(n,k) = 1^k + 2^k + 3^k + ... + n^k modulo Prime
//Complexity : O(k log (MOD))

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000010
#define MOD 1000000007
#define ll long long int

namespace lgr{
    short factor[MAX];
    int P[MAX],S[MAX],ar[MAX],inv[MAX];

    inline int bigMod(ll a,ll b){
        ll res=1;
        while(b){
            if(b&1) res=(res*a)%MOD;
            a=(a*a)%MOD; b>>=1;
        }
        return res;
    }

    int lagrange(ll n,int k){
        if(!k) return (n%MOD);
        if(!inv[0]){
            int x=1;
            for(int i=2;i<MAX;i++) x=((ll)x*i)% MOD;
            inv[MAX-1]=bigMod(x,MOD-2);
            for(int i=MAX-2;i>=0;i--) inv[i]=((ll)inv[i+1]*(i+1))%MOD;
        }

        k++;
        for(int i=0;i<=k;i++) factor[i]=0;
        for(int i=4;i<=k;i+=2) factor[i]=2;
        for(int i=3;(i*i)<=k;i+=2){
            if(!factor[i]) for(int j=(i*i),x=(i<<1);j<=k;j+=x) factor[j] = i;
        }

        ar[1]=1,ar[0]=0;
        for(int i=2;i<=k;i++){
            if(!factor[i]) ar[i]=bigMod(i,k-1);
            else ar[i]=((ll)ar[factor[i]] * ar[i/factor[i]]) % MOD;
        }

        for(int i=1;i<=k;i++){
            ar[i]+=ar[i - 1];
            if(ar[i]>=MOD) ar[i]-=MOD;
        }
        if(n<=k) return ar[n];

        P[0]=1, S[k]=1;
        for(int i=1;i<=k;i++) P[i]= ((ll)P[i-1] * ((n-i+1)%MOD) ) % MOD;
        for(int i=k-1;i>=0;i--) S[i]= ((ll)S[i+1] * ((n-i-1)%MOD)) % MOD;

        int res=0;
        for (int i=0;i<=k;i++){
            int x = (ll)ar[i] * P[i] % MOD * S[i] % MOD * inv[k - i] % MOD * inv[i] % MOD;
            if((k-i)&1) {res-=x; if(res<0) res+=MOD;}
            else {res+=x; if(res>=MOD) res-=MOD;}
        }
        return (res % MOD);
    }
}

int main(){
    ll n; int k;
    scanf("%lld %d",&n,&k);
    printf("%d\n",lgr::lagrange(n, k));
}
