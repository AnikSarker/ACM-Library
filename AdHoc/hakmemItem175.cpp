#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// Only for non-negative integers
// Returns the immediate next number
// with same count of one bits, -1 on failure
ll NextSamePop(ll n){
    if(n == 0) return -1;
    ll x = (n & -n);
    ll left = (x + n);
    ll right = ((n ^ left) / x) >> 2;
    ll res = (left | right);
    return res;
}

// Returns the immediate previous number
// with same count of one bits, -1 on failure
ll PrevSamePop(ll n){
    if (n == 0 || n == 1) return -1;
    ll res = ~NextSamePop(~n);
    return (res == 0) ? -1 : res;
}
