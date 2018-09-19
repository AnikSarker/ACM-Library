#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
#define ll long long int

// Gaussian Elimination Online
struct maxxor{
    ll b[64];
    ll sz;
    void init() {sz = 0;}

    void add(ll x){
        for(ll i = 0; i < sz; i++)
            if((x ^ b[i]) < x) x ^= b[i];
        for(ll i = 0; i < sz; i++)
            if((x ^ b[i]) < b[i]) b[i] ^= x;
        if(x){
            b[sz++] = x;
            for(ll i = sz - 1; i>=0 ; i--)
                if(b[i] < b[i - 1])
                    swap(b[i], b[i - 1]);
        }
    }

    ll getMax(){
        ll ans=0;
        for(ll i = 0; i < sz; i++) ans ^= b[i];
        return ans;
    }

    ll getKth(ll k){
        k--; ll ans = 0;
        for(ll i = 0; i < sz; i++)
            if((k >> i) & 1) ans ^= b[i];
        return ans;
    }
}ds;

// Gaussian Elimination Offline
ll a[MAX], n;
ll maxxor(){
    int r = 0; ll ret = 0;
    for(int c = 31; c >= 0; c--){
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
