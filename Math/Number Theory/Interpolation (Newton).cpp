/* for a nth-order polynomial f(x)
given f(0), f(1), ..., f(n)
express f(x) as sum_over_{coef_i * C(x,i)} */

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

namespace Newton{
    int n;
    vector<ll> coef;

    // initialize and calculate f(x), vector _fx should
    // be filled with f(0) to f(n)
    Build(vector<ll>& fx){
        coef = fx;
        n = fx.size() - 1;
        for(int i=0; i<n; i++){
            for(int j=n; j>i; j--){
                coef[j] -= coef[j-1];
            }
        }
    }

    // evaluate f(x), runs in O(n)
    ll eval(ll x){
        ll m = 1, ret = 0;
        for(int i=0; i<=n; i++){
            ret += coef[i] * m;
            m = m * (x-i) / (i+1);
        }
        return ret;
    }
};
