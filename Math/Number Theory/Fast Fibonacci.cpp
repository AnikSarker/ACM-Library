// F(n-1) * F(n+1) - F(n) * F(n) = (-1)^n
// F(n+k) = F(k) * F(n+1) + F(k-1) * F(n)
// gcd(F(m), F(n)) = F(gcd(m,n))

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
