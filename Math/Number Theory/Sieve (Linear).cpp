#include <bits/stdc++.h>
using namespace std;
const int MAX = 10000005;

int phi[MAX];
int least[MAX];
vector<int> primes;

void RunLinearSieve(int n) {
    n = max(n, 1);
    for(int i=0;i<=n;i++) least[i] = 0;

    phi[1] = 1;
    primes.clear();
    for(int i = 2; i <= n; i++){
        if(least[i] == 0){
            least[i] = i; lstCnt[i] = 1;
            phi[i] = i - 1; sigma[i] = 2;
            primes.push_back(i);
        }
        for(int x : primes){
            if(x > least[i] || i * x > n) break;
            least[i * x] = x;

            if(least[i] == x) phi[i * x] = phi[i] * x;
            else phi[i * x] = phi[i] * (x - 1);
        }
    }
}

int mob[MAX];
void Mobius(int n){
    RunLinearSieve(n);

    mob[1] = 1;
    for(int i = 2; i <= n; i++) {
        int j = i/least[i];
        if(least[j] == least[i]) mob[i] = 0;
        else mob[i] = -mob[j];
    }
}
