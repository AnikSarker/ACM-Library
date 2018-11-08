#include <bits/stdc++.h>
using namespace std;

#define MAXN 100
#define MAXM 100010
#define MAXP 666666
#define MAX 10000010
#define ll long long int
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

namespace pcf{
    ll dp[MAXN][MAXM];
    unsigned int ar[(MAX>>6)+5] = {0};
    int len=0, primes[MAXP], counter[MAX];

    void Sieve(){
        setbit(ar,0), setbit(ar,1);
        for(int i=3;(i*i)<MAX;i++,i++){
            if(!chkbit(ar,i)){
                int k=i<<1;
                for(int j=(i*i);j<MAX;j+=k) setbit(ar,j);
            }
        }

        for(int i=1;i<MAX;i++){
            counter[i]=counter[i - 1];
            if(isprime(i)) primes[len++]=i, counter[i]++;
        }
    }

    void init(){
        Sieve();
        for(int n=0;n<MAXN;n++){
            for(int m=0;m<MAXM;m++){
                if(!n) dp[n][m]=m;
                else dp[n][m]=dp[n-1][m]-dp[n-1][m/primes[n-1]];
            }
        }
    }

    ll phi(ll m,int n){
        if(n==0) return m;
        if(primes[n-1] >= m) return 1;
        if(primes[n-1] * 1LL * primes[n-1] >=m) return counter[m] - n + 1;
        if(m<MAXM && n<MAXN) return dp[n][m];
        return phi(m,n-1) - phi(m/primes[n-1],n-1);
    }

    //returns number of primes in range [1,m]
    //Complexity : O(m^(2/3))
    ll Lehmer(ll m){
        if(m < MAX) return counter[m];

        ll w,res=0;
        int i,a,s,c,x,y;
        s=sqrt(0.9+m), y=c=cbrt(0.9+m);
        a=counter[y], res=phi(m,a)+a-1;
        for(i=a;primes[i]<=s;i++) res=res-Lehmer(m/primes[i])+Lehmer(primes[i])-1;
        return res;
    }
    
    ll Legendre(ll m){
        if (m < MAX) return counter[m];

        int lim = sqrt(m) + 1;
        int n = upper_bound(primes, primes + len, lim) - primes;
        return phi(m, n) + (n - 1);
     }
}
