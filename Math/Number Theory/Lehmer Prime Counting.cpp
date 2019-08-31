//Tested : CF 665F - Four Divisors

/* Let p(j) = j-th prime number.
dp(n,j) = Count of k (1 <= k <= n and all prime div of k >= p(j))
Then we have : dp(n,1) = n and dp(n,j+1) = dp(n,j) - dp(n/p(j),j)
Let p(k) be the smallest prime > sqrt(n), π(n) = dp(n,k) + k - 1 
Complexity : O(n ^ (2/3)) */

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

const int LIM = 250;
const int MAXP = 10000005;

vector<int> P;
int prec[MAXP];
bool prime[MAXP];

void build(){
    prime[2] = true;
    for(int i = 3; i < MAXP; i += 2) prime[i] = true;

    for(int i = 3; i*i < MAXP; i += 2){
        if(!prime[i]) continue;
        for(int j = i*i; j < MAXP; j += i+i) prime[j] = false;
    }

    for(int i=2; i<MAXP; i++) if(prime[i]) P.push_back(i);
    for(int i=1; i<MAXP; i++) prec[i] = prec[i-1] + prime[i];
}

ll dp[LIM*LIM][LIM];
ll rec(ll N, int K){
    if(N <= 1 || K < 0) return 0;
    if(N <= P[K]) return N-1;
    if(N < MAXP && P[K] * 1LL * P[K] > N) return N-1 - prec[N] + prec[P[K]];

    bool ok = N < LIM * LIM && K < LIM;
    if (ok && dp[N][K]) return dp[N][K];

    ll ret = N/P[K] - rec(N/P[K], K-1) + rec(N, K-1);

    if(ok) dp[N][K] = ret;
    return ret;
}

ll count_primes(ll N) {
    if(N < MAXP) return prec[N];
    int K = prec[(int)sqrt(N) + 1];
    return N-1 - rec(N, K) + prec[P[K]];
}
