#include<bits/stdc++.h>
using namespace std;

#define MAXP 10000000
#define ll long long int
#define pii pair<int,int>
const ll MOD = 10000000000LL;

namespace crt{
    ll egcd(ll a, ll b, ll& x, ll& y){
        if(!b) {y = 0, x = 1; return a;}
        ll g = egcd(b, a % b, y, x);
        y -= ((a / b) * x);
        return g;
    }

    ll inv(ll a, ll m){
        ll x, y;
        egcd(a, m, x, y);
        return (x + m) % m;
    }

    ll chinese_remainder(vector <ll> ar, vector <ll> mods){
        ll x, y, res = 0, M = 1;
        for(int i = 0; i < ar.size(); i++) M *= mods[i];
        for(int i = 0; i < ar.size(); i++){
            x = M / mods[i], y = inv(x, mods[i]);
            res = (res + (((x * ar[i]) % M) * y)) % M;
        }
        return res;
    }
}

namespace binomial{
    ll dp[MAXP];

    void build(ll p,ll mod){
        dp[0] = 1;
        for(int i = 1; i < mod; i++) dp[i] = (ll)dp[i - 1] * ((i % p) ? i : 1) % mod;
    }

    ll trailing(ll x, ll p){
        ll res = 0;
        while(x) {x /= p; res += x;}
        return res;
    }

    ll expo(ll a, ll b, ll m){
        ll res = 1;
        while(b){
            if (b & 1) res = res * a % m;
            a = (a * a) % m, b >>= 1;
        }
        return res;
    }

    vector<pii> factorize(ll m){
        vector <pii> factors;
        for(ll i = 2; i * i <= m; i++){
            int c = 0;
            while (m % i == 0)  {c++; m /= i;}
            if (c) factors.push_back({i, c});
        }
        if(m > 1) factors.push_back({m, 1});
        return factors;
    }

    ll spf(ll x, ll p, ll mod){
        //Referrence : http://e-maxx.ru/algo/modular_factorial
        //Complexity : O(log_p (x))
        ll res = expo(dp[mod - 1], x / mod, mod);
        if(x >= p) res = res * spf(x / p, p, mod) % mod;
        return res * dp[x % mod] % mod;
    }

    ll C_mod_p_q(ll n, ll k, ll p, ll q){
        using namespace crt;

        if(k > n || k < 0) return 0;
        if(n == k || k == 0) return 1;

        ll mod = expo(p, q, 1e18);
        assert(mod < MAXP);

        ll t = trailing(n, p) - trailing(k, p) - trailing(n - k, p);
        if(t >= q) return 0;

        build(p,mod); //Complexity : O(mod)
        //This part can be optimized processing same mods at once.

        ll res = spf(n, p, mod) * inv(spf(k, p, mod) * spf(n - k, p, mod) % mod, mod) % mod;
        res = (res * expo(p,t, mod))% mod;
        return res;
    }

    //Calculate C(n,k) % M
    //Works when M = p1^q1 * p2^q1 * .... px^qx, such that pi^qi < MAXP
    //Running time : O(MAXP)
    ll C(ll n, ll k, ll m){
        if(k > n || m == 1 || k < 0) return 0;
        if(n == k || k == 0) return 1;

        vector<pii> factors = factorize(m);
        vector <ll> ar, mods;
        for(auto f : factors){
            ll x = 1;
            for (int j = 0; j < f.second; j++) x *= f.first;
            mods.push_back(x), ar.push_back(C_mod_p_q(n, k, f.first, f.second));
        }
        return crt::chinese_remainder(ar, mods);
    }

    //check whether C(n,k) is greater than Lim
    bool isGreater(ll n, ll k, ll Lim){
        if(k < 0 || k > n) return false;

        k = min(k, n - k);
        ll u = n, v = 1;
        pair <ll, long double> x = make_pair(1, 1);

        for(int i = 0; i < k; i++, u--, v++){
            x = make_pair(x.first * u, x.second * u);
            x = make_pair(x.first / v, x.second / v);
            if(x.first >= Lim || x.second >= (2.0 * Lim)) return true;
        }
        return false;
    }
}
