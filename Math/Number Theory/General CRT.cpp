//Tested : Kattis-generalchineseremainder

#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define pll pair<ll, ll>

ll egcd(ll a, ll b, ll& x, ll& y){
    if(!b) {y = 0, x = 1; return a;}
    ll g = egcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}

pll GeneralCRT(pll a, pll b){
    if(a.second < b.second) swap(a, b);
    ll x, y; egcd(a.second, b.second, x, y);
    ll g = a.second * x + b.second * y;
    ll l = a.second / g * b.second;
    if((b.first - a.first) % g) return {-1, -1}; // No Solution

    ll c = (b.first - a.first) % b.second;
    c = (c * x) % b.second;
    c = c / g * a.second;
    c += a.first;
    if(c < 0) c += l;
    return {c, l};
}
