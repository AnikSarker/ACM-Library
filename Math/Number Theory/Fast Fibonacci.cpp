#define ll long long int

pair<ll, ll> fib(ll n) {
    if(n == 0) return {0, 1};
    ll x, y;
    if(n & 1) {
        tie(y, x) = fib(n - 1);
        return {x, (y + x) % MOD};
    }
    else{
        tie(x, y) = fib(n >> 1);
        return {(x * y + x * (y - x + MOD)) % MOD, (x * x + y * y) % MOD};
    }
}
