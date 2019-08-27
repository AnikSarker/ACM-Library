#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll p = 998244353, gen = 3;

inline ll add(ll x, ll y) {x += y; return x >= p ? x - p: x;}
inline ll sub(ll x, ll y) {x -= y; return x < 0    ? x + p : x;}
inline ll mul(ll x, ll y) {return (x * y) % p;}
inline ll Pow(ll x, ll y){
    ll res = 1;
    while(y){
        if(y & 1) res = (res * x) % p;
        y >>= 1, x = (x * x) % p;
    }
    return res;
}

namespace Polynom{
    vector<ll> rev, root;
    vector<ll> operator + (vector<ll> f, vector<ll> g) {
        ll n = max(f.size(), g.size());
        f.resize(n); g.resize(n);
        for (ll i = 0; i < n; i++) f[i] = add(f[i], g[i]);
        return f;
    }

    vector<ll> operator - (vector<ll> f, vector<ll> g) {
        ll n = max(f.size(), g.size());
        f.resize(n); g.resize(n);
        for (ll i = 0; i < n; i++) f[i] = sub(f[i], g[i]);
        return f;
    }

    void getRevRoot(ll n) {
        ll m = log(n) / log(2) + 1e-7;

        rev.resize(n); root.resize(n);
        for (ll i = 1; i < n; i++)  rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));
        for (ll len = 1; len < n; len <<= 1) {
            ll uni = Pow(gen, (p ^ 1) / (len << 1));
            root[len] = 1;
            for (ll i = 1; i < len; i++) root[i + len] = mul(root[i + len - 1], uni);
        }
    }
    void ntransform(vector<ll> &f, ll n, bool t){
        if(t) reverse(f.begin() + 1, f.end());
        f.resize(n);

        for (ll i = 0; i < n; i++) { if (i < rev[i]) {swap(f[i], f[rev[i]]);} }
        for (ll len = 1; len < n; len <<= 1) {
            for (ll i = 0; i < n; i += len << 1) {
                for (ll j = 0; j < len; j++) {
                    ll x = f[i + j], y = mul(f[i + j + len], root[j + len]);
                    f[i + j] = add(x, y); f[i + j + len] = sub(x, y);
                }
            }
        }
    }
    vector<ll> operator * (vector<ll> f, vector<ll> g) {
        ll n = 1, m = f.size() + g.size() - 1;
        while (n < m) n <<= 1;
        ll invN = Pow(n, p - 2);

        getRevRoot(n);
        ntransform(f, n, false); ntransform(g, n, false);
        for (ll i = 0; i < n; i++) f[i] = mul(f[i], g[i]);
        ntransform(f, n, true);
        for (ll i = 0; i < n; i++) f[i] = mul(f[i], invN);
        f.resize(m);
        return f;
    }

    vector<ll> polyInv(vector<ll> f, ll m){
        vector<ll> g, h; f.resize(m);
        if (m == 2) g.push_back(Pow(f[0], p - 2));
        else g = polyInv(f, m >> 1);

        ll n = m << 1, invN = Pow(n, p - 2);
        g.resize(m); h.resize(m);
        for (ll i = (m >> 1) - 1; ~i; i--) h[i] = (g[i] << 1) % p;

        getRevRoot(n);
        ntransform(f, n, false); ntransform(g, n, false);
        for (ll i = 0; i < n; i++) f[i] = mul(mul(f[i], g[i]), g[i]);
        ntransform(f, n, true);
        for (ll i = 0; i < m; i++) h[i] = sub(h[i], mul(f[i], invN));
        return h;
    }

    vector<ll> operator ~(vector<ll> f){
        ll n = 1, m = (ll) f.size();
        while(n < m) n <<= 1;
        if(n == 1) f[0] = Pow(f[0], p - 2);
        else f = polyInv(f, n);
        f.resize(m);
        return f;
    }

    vector<ll> dvf, dvg, dvr;
    vector<ll> operator / (vector<ll> f, vector<ll> g) {
        if (f == dvf && g == dvg) return dvr;
        dvf = f; dvg = g;
        ll n = f.size(), m = g.size(); n = n - m + 1;
        reverse(f.begin(), f.end()); f.resize(n);
        reverse(g.begin(), g.end()); g.resize(n);
        dvr = f * (~g); dvr.resize(n); reverse(dvr.begin(), dvr.end());
        return dvr;
    }

    vector<ll> operator % (vector<ll> f, vector<ll> g) {
        ll n = (ll) g.size() - 1;
        f = f - f / g * g;
        f.resize(n - 1); return f;
    }

    vector<ll> fac, inv, one = {1};
    void getFacInv(ll n){
        if (n <= fac.size()) { return; }
        fac.resize(n); inv.resize(n);
        for (ll i = fac[0] = 1; i < n; i++) fac[i] = mul(fac[i - 1], i);
        inv[n - 1] = Pow(fac[n - 1], p - 2);
        for (ll i = n - 1; i; i--) inv[i - 1] = mul(inv[i], i);
    }

    vector<ll> operator >> (vector<ll> f, ll m){
        ll n = (ll) f.size(); m = min(n, m); getFacInv(n);
        for (ll i = m; i < n; i++) f[i - m] = mul(mul(f[i], fac[i]), inv[i - m]);
        f.resize(n - m);
        return f;
    }

    vector<ll> operator << (vector<ll> f, ll m) {
        ll n = f.size(); f.resize(n + m); getFacInv(n + m);
        for (ll i = n + m - 1; i >= m; i--) f[i] = mul(mul(f[i - m], fac[i - m]), inv[i]);
        fill(f.begin(), f.begin() + m, 0);
        return f;
    }

    vector<ll> polyLn(vector<ll> f) {
        ll n = f.size();
        f = (f >> 1) * (~f) << 1;
        f.resize(n);
        return f;
    }

    vector<ll> polyExp(vector<ll> f, ll n) {
        vector<ll> g, h; f.resize(n);
        if (n == 2) g.push_back(1);
        else g = polyExp(f, n >> 1);
        g.resize(n);
        return g * (one - polyLn(g) + f);
    }

    vector<ll> polyExp(vector<ll> f) {
        ll n = 1, m = (ll) f.size();
        while (n < m) { n <<= 1; } f = polyExp(f, n);
        f.resize(m);
        return f;
    }

    vector<ll> operator ^ (vector<ll> f, ll x) {
        ll n = (ll) f.size(); f = polyLn(f);
        for (ll i = 0; i < n; i++) { f[i] = (long long) f[i] * x % p; }
        return polyExp(f);
    }
}
using namespace Polynom;

int main(){
    vector<ll> a{43431,1231,435,43340,430,10};
    vector<ll> b = ~a;

    vector<ll> c = a * b * a;
    for(ll x : c) cout<<x<<" ";
}
