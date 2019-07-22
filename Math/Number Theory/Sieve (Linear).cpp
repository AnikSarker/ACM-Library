#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000005;

int least[MAX];
vector<int> primes;

void RunLinearSieve(int n) {
    n = max(n, 1);
    for(int i=0;i<=n;i++) least[i] = 0;

    primes.clear();
    for(int i = 2; i <= n; i++){
        if(least[i] == 0){
            least[i] = i;
            primes.push_back(i);
        }
        for(int x : primes){
            if(x > least[i] || i * x > n) break;
            least[i * x] = x;
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
