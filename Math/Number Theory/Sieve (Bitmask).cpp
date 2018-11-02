#include <bits/stdc++.h>
using namespace std;

#define LEN 78777
#define MAX 1000010
#define Check(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define Set(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isPrime(x) (( (x) && ((x)&1) && (!Check(ar, (x)))) || ((x) == 2))

int p, prime[LEN];
unsigned int ar[(MAX >> 6) + 5] = {0};

void Sieve(){
    Set(ar, 0);
    Set(ar, 1);

    for(int i = 3; (i * i) < MAX; i++, i++){
        if(!Check(ar, i)){
            int k = i << 1;
            for(int j = (i * i); j < MAX; j += k) Set(ar, j);
        }
    }

    p = 0;
    prime[p++] = 2;
    for(int i = 3; i < MAX; i++, i++){
        if (isPrime(i)) prime[p++] = i;
    }
}
