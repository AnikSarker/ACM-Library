#define ll long long int
#define MAXN 1000005
#define MOD 1000000007

ll bigMod(ll n, ll r) {
    if (r==0)   return 1LL;
    ll ret = bigMod (n, r/2);
    ret = (ret * ret)% MOD;
    if (r %2 ) ret = (ret * n) % MOD;
    return ret;
}

ll Point[MAXN];
ll Fact[MAXN];

// Calculate first k + 1 points (0 to k) on the polynomial
// where k = degree of the polynomial
// Then find f(x) for any x using interpolation in O(n log(MOD))

ll interpolate(int n,ll x) {
    if(x <= n) return Point[x];

    ll num = 1;
    for(int i=0; i<=n; i++) num=(num * (x-i)) % MOD;

    ll ret = 0;
    for(int i=0; i<=n; i++) {
        ll nn = (num * bigMod(x-i, MOD-2)) % MOD;
        ll dd = (Fact[n-i] * Fact[i]) % MOD;

        if((n-i) & 1) dd = MOD -dd;
        nn = (Point[i] * nn) % MOD;
        ret = (ret + nn * bigMod(dd, MOD-2))%MOD;
    }
    return ret;
}
