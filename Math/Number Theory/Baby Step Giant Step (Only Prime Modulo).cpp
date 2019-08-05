//Tested : LightOJ 1325 - Distributing Chocolates

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

//Shanks Baby-Step Giant-Step (Faster)
//a^x = b (mod m)
ll egcd(ll a,ll b,ll &x,ll &y){
    if(b == 0) {x = 1; y = 0; return a;}
    ll g = egcd(b,a%b,y,x);
    y -= a / b * x;
    return g;
}

ll InvMod(ll a,ll m){
    ll x,y;
    if(egcd(a,m,x,y) == 1) return (x + m) % m;
    return -1;
}

unordered_map<ll, ll> H;
ll baby_step_giant_step(ll a,ll b,ll m){
    H.clear();
    int k = (int) sqrt(m)+1;

    //Baby step
    ll aa = 1;
    for(int j=0;j<k;j++){
        if(!H.count(aa)) H[aa] = j;
        aa = aa * a % m;
    }

    //Giant step
    aa = InvMod(aa,m);
    for(int i=0;i<k;i++){
        if(H.count(b)) return i*k + H[b];
        b = b * aa % m;
    }
    return -1;
}
