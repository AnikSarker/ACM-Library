//Finds x such that x <= n and has maximum number of divisors

#include <bits/stdc++.h>
using namespace std;
#define ULL unsigned long long int

ULL n, res, idx;
int p, primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

ULL mul(ULL a, ULL b){
    ULL res = 0;
    while (b){
        if (b & 1LL) res = (res + a);
        if (res > n) return 0;
        a = (a << 1LL);
        b >>= 1LL;
    }
    return res;
}

void backtrack(int i, int lim, ULL val, ULL r){
    if ((r > res) || (r == res && val < idx)) res = r, idx = val;
    if (i == p) return;

    ULL x = val;
    for (int d = 1; d <= lim; d++){
        x = mul(x, primes[i]);
        if (x == 0) return;
        backtrack(i + 1, d, x, r * (d + 1));
    }
}

int main(){
    /* Tested for <= 10^18 */
    p = sizeof(primes) / sizeof(int);
    res = 0;
    scanf("%llu", &n);
    backtrack(0, 100, 1, 1);
    printf("%llu = %llu\n", idx, res);
}
