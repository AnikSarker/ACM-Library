#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
#define ll long long int

// Gaussian Elimination Online
struct maxxor{
    vector<ll> basis;
    void init() {basis.clear();}

    void add(ll x){
        // Keep the basis sorted in increasing order
        for(ll b : basis) x = min(x, x ^ b);
        for(ll &b : basis) b = min(b, x ^ b);

        if(x){
            basis.push_back(x);
            for(ll i = basis.size() - 1; i> 0 ; i--){
                if(basis[i] < basis[i - 1]) swap(basis[i], basis[i - 1]);
                else break;
            }
        }
    }

    //returns max subset xor
    ll getMax(){
        ll ans=0;
        for(ll b : basis) ans ^= b;
        return ans;
    }

    //returns max xor over (k ^ some subset)
    ll getMax(ll k){
        ll ans = k;
        for(ll b : basis) ans = max(ans, ans ^ b);
        return ans;
    }

    //returns k-th (0-indexed) smallest distinct subset xor
    ll getKth(ll k){
        ll ans = 0;
        for(ll i = 0; i < basis.size(); i++)
            if((k >> i) & 1) ans ^= basis[i];
        return ans;
    }
}ds;

// Gaussian Elimination Offline
ll a[MAX], n;
ll maxxor(){
    int r = 0; ll ret = 0;
    for(int c = 63; c >= 0; c--){
        int idx = -1;
        for(int i = r; i < n && idx < 0; i++)
            if(a[i] >> c & 1) idx = i;
        if(idx == -1) continue;
        swap(a[r], a[idx]);
        for(int i = 0; i < n; i++) if(i != r)
                if(a[i] >> c & 1) a[i] ^= a[r];
        r++;
    }
    for(int i = 0; i < n; i++) ret = max(ret, ret ^ a[i]);
    return ret;
}
