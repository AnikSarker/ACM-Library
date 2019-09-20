#include <bits/stdc++.h>
using namespace std;
#define ll long long int
const ll mod = 786433;
//For 10^9 + 7 : {7340033, 415236097, 463470593}

inline ll add(ll x, ll y) {x += y; return x >= mod ? x - mod : x;}
inline ll sub(ll x, ll y) {x -= y; return x < 0    ? x + mod : x;}
inline ll mul(ll x, ll y) {return (x * y) % mod;}
inline ll Pow(ll x, ll y){
    ll res = 1;
    while(y){
        if(y & 1) res = (res * x) % mod;
        y >>= 1, x = (x * x) % mod;
    }
    return res;
}

struct NTT{
    vector<ll> A,B;
    vector<ll> root, rev;
    ll P,M,G;

    NTT(ll mod) {P = mod; G = 10;}
    void init(int n){
        M = 1; int z = 0;
        while(M < n) M <<= 1, z++;
        M <<= 1; z++;

        A.resize(M); B.resize(M);
        root.resize(M); rev.resize(M);
        for(int i = 1; i < M; i++) rev[i] = rev[i >> 1] >> 1 | (i & 1) << (z - 1);

        int x = Pow(G, (P-1) / M);
        root[0] = 1;
        for(int i = 1; i < M; i++) root[i] = mul(root[i-1], x);
    }

    void ntransform(vector<ll> &a,ll f){
        if(f) reverse(a.begin() + 1, a.end());
        for (ll i = 0; i < M; i++) if(i < rev[i]) swap(a[i],a[rev[i]]);
        for (ll i = 1; i < M; i <<= 1){
            for (ll j = 0, t = M / (i << 1); j < M; j += i << 1){
                for (ll k = 0, l = 0; k < i; k++, l += t){
                    ll x = a[j + k];
                    ll y = mul(a[j + k + i], root[l]);
                    a[j + k] = add(x, y);
                    a[j + k + i] = sub(x, y);
                }
            }
        }

        if(f){
            ll inv = Pow(M, P-2);
            for(ll i = 0; i < M; i++) a[i] = mul(a[i], inv);
        }
    }

    void multiply( vector<ll> &X, vector<ll> &Y, vector<ll> &res){
        init(max(X.size(), Y.size()));
        for (ll i = 0; i < M; i++) A[i] = B[i] = 0;
        for (ll i = 0; i < X.size(); i++) A[i] = X[i];
        for (ll i = 0; i < Y.size(); i++) B[i] = Y[i];
        ntransform(A, 0); ntransform(B, 0);
        res.clear(); res.resize(M);
        for (ll i = 0; i < M; i++) res[i] = mul(A[i], B[i]);
        ntransform(res, 1);
    }
} ntt(mod);
