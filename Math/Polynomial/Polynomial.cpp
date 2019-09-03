#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll p = 998244353, gen = 3;

inline ll add(ll x, ll y) {x += y; return x >= p ? x - p: x;}
inline ll sub(ll x, ll y) {x -= y; return x < 0  ? x + p : x;}
inline ll mul(ll x, ll y) {return (x * y) % p;}
inline ll Pow(ll x, ll y){
    ll res = 1;
    while(y){
        if(y & 1) res = mul(res, x);
        y >>= 1, x = mul(x, x);
    }
    return res;
}

namespace Polynom{
    vector<ll> rev, root;
    vector<ll> operator + (vector<ll> f, vector<ll> g) {
        ll n = max(f.size(), g.size());
        f.resize(n); g.resize(n);
        for(ll i = 0; i < n; i++) f[i] = add(f[i], g[i]);
        return f;
    }

    vector<ll> operator - (vector<ll> f, vector<ll> g) {
        ll n = max(f.size(), g.size());
        f.resize(n); g.resize(n);
        for(ll i = 0; i < n; i++) f[i] = sub(f[i], g[i]);
        return f;
    }

    void getRevRoot(ll n) {
        ll m = 0; while( (1<<m) < n) m++;

        rev.resize(n); root.resize(n);
        for(ll i = 1; i < n; i++)  rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));
        for(ll len = 1; len < n; len <<= 1) {
            ll uni = Pow(gen, (p ^ 1) / (len << 1));
            root[len] = 1;
            for(ll i = 1; i < len; i++) root[i + len] = mul(root[i + len - 1], uni);
        }
    }

    void ntransform(vector<ll> &f, ll n, bool t){
        if(t) reverse(f.begin() + 1, f.end());
        f.resize(n);

        for(ll i = 0; i < n; i++) { if (i < rev[i]) {swap(f[i], f[rev[i]]);} }
        for(ll len = 1; len < n; len <<= 1) {
            for(ll i = 0; i < n; i += len << 1) {
                for(ll j = 0; j < len; j++) {
                    ll x = f[i + j], y = mul(f[i + j + len], root[j + len]);
                    f[i + j] = add(x, y); f[i + j + len] = sub(x, y);
                }
            }
        }
    }

    // Given a n-degree polynomial f and m-degree polynomial g
    // returns a (n + m) degree polynomial f * g (not in modular field)
    vector<ll> operator * (vector<ll> f, vector<ll> g) {
        ll n = 1, m = f.size() + g.size() - 1;
        while (n < m) n <<= 1;
        ll invN = Pow(n, p - 2);

        getRevRoot(n);
        ntransform(f, n, false); ntransform(g, n, false);
        for(ll i = 0; i < n; i++) f[i] = mul(f[i], g[i]);
        ntransform(f, n, true);
        for(ll i = 0; i < n; i++) f[i] = mul(f[i], invN);
        f.resize(m);
        return f;
    }

    vector<ll> polyInv(vector<ll> f, ll m){
        vector<ll> g, h; f.resize(m);
        if (m == 2) g.push_back(Pow(f[0], p - 2));
        else g = polyInv(f, m >> 1);

        ll n = m << 1, invN = Pow(n, p - 2);
        g.resize(m); h.resize(m);
        for(ll i = (m >> 1) - 1; ~i; i--) h[i] = add(g[i], g[i]);

        getRevRoot(n);
        ntransform(f, n, false); ntransform(g, n, false);
        for(ll i = 0; i < n; i++) f[i] = mul(mul(f[i], g[i]), g[i]);
        ntransform(f, n, true);
        for(ll i = 0; i < m; i++) h[i] = sub(h[i], mul(f[i], invN));
        return h;
    }

    // given a n-degree polynomials f
    // returns w such that f * w = 1 (mod z^n)
    vector<ll> operator ~ (vector<ll> f){
        assert(f[0] != 0);
        ll n = 1, m = (ll) f.size();
        while(n < m) n <<= 1;
        if(n == 1) f[0] = Pow(f[0], p - 2);
        else f = polyInv(f, n);
        f.resize(m);
        return f;
    }

    vector<ll> dvf, dvg, dvr;
    // given 2 n-degree polynomials f and g
    // returns w such that g * w = f (mod z^n)
    vector<ll> operator / (vector<ll> f, vector<ll> g) {
        if (f == dvf && g == dvg) return dvr;
        dvf = f; dvg = g;
        ll n = f.size(), m = g.size(); n = n - m + 1;
        reverse(f.begin(), f.end()); f.resize(n);
        reverse(g.begin(), g.end()); g.resize(n);
        dvr = f * (~g); dvr.resize(n); reverse(dvr.begin(), dvr.end());
        return dvr;
    }

    vector<ll> fac, inv, one = {1};
    void getFacInv(ll n){
        if (n <= fac.size()) return;
        fac.resize(n); inv.resize(n);
        for(ll i = fac[0] = 1; i < n; i++) fac[i] = mul(fac[i - 1], i);
        inv[n - 1] = Pow(fac[n - 1], p - 2);
        for(ll i = n - 1; i; i--) inv[i - 1] = mul(inv[i], i);
    }

    vector<ll> operator >> (vector<ll> f, ll m){
        ll n = f.size(); m = min(n, m); getFacInv(n);
        for(ll i = m; i < n; i++) f[i - m] = mul(mul(f[i], fac[i]), inv[i - m]);
        f.resize(n - m);
        return f;
    }

    vector<ll> operator << (vector<ll> f, ll m){
        ll n = f.size(); f.resize(n + m); getFacInv(n + m);
        for(ll i = n + m - 1; i >= m; i--) f[i] = mul(mul(f[i - m], fac[i - m]), inv[i]);
        fill(f.begin(), f.begin() + m, 0);
        return f;
    }

    vector<ll> polyLn(vector<ll> f){
        ll n = f.size();
        f = (f >> 1) * (~f) << 1;
        f.resize(n);
        return f;
    }

    vector<ll> polyExp(vector<ll> f, ll n){
        vector<ll> g, h; f.resize(n);
        if (n == 2) g.push_back(1);
        else g = polyExp(f, n >> 1);
        g.resize(n);
        return g * (one - polyLn(g) + f);
    }

    vector<ll> polyExp(vector<ll> f){
        ll n = 1, m = (ll) f.size();
        while(n < m) n <<= 1;
        f = polyExp(f, n);
        f.resize(m);
        return f;
    }

    // Given a n-degree polynomial f
    // returns w such that w = f ^ x (mod z^n)
    vector<ll> operator ^ (vector<ll> f, ll x){
        ll idx = 0;
        while(idx < f.size() && f[idx] == 0) idx++;
        if(idx == f.size()) return f;

        vector<ll> g;
        for(int i = idx; i < f.size(); i++) g.push_back(f[i]);

        ll n = g.size();
        ll inv = Pow(g[0], p-2), ext = Pow(g[0], x);
        for(ll i = 0; i < n; i++) g[i] = mul(g[i], inv);
        g = polyLn(g);
        for(ll i = 0; i < n; i++) g[i] = mul(g[i], x);
        g = polyExp(g);
        for(ll i = 0; i < n; i++) g[i] = mul(g[i], ext);

        f.clear();
        for(ll i = 0; i < idx * x; i++) f.push_back(0);
        for(ll i = 0; i < n; i++){
            if(f.size() == n + idx) break;
            f.push_back(g[i]);
        }
        return f;
    }
}
using namespace Polynom;

int main(){
    vector<ll> a{43431,1231,435,43340,430,10};
    vector<ll> b = ~a;
    vector<ll> c = a * b * a;
    for(ll x : c) cout<<x<<" "; cout<<endl;

    vector<ll> d = a^3;
    vector<ll> e = a * a * a;
    for(ll x : d) cout<<x<<" "; cout<<endl;
    for(ll x : e) cout<<x<<" "; cout<<endl;
    e.resize(a.size());

    vector<ll> f = e / d;
    vector<ll> g = f * d;
    for(ll x : g) cout<<x<<" ";
}
