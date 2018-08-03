/*C(n, r, M) calculates nCr mod M.. M is not necessarily prime!
Factorize mod into p_0 ^ q_0 * p_1 ^ q_1 .....
Then calculate nCr \equiv a_i (mod p_i ^ q_i) by lucas modified!
Then do CRT to calculate nCd mod(M)*/

ll Pow(ll n, ll p, ll mod) {
	if(!p) return 1;
	else if(p & 1) {
		return n*Pow(n,p-1, mod) % mod;
	} else {
		ll v = Pow(n, p/2, mod);
		return v*v % mod;
	}
}
ll Leg(ll n, ll p) {
	ll ans = 0;
	while(n) ans += n /= p;
	return ans;
}

vector<ii> factorize(ll n) {
	vector<ii> ret;
	for(int i=2; i*i<=n; i++) {
		if(n % i == 0) {
			int cnt = 0;
			while(n % i == 0) {
				n /= i; cnt++;
			} ret.push_back({i, cnt});
		}
	} if(n > 1) ret.push_back({n,1});
	return ret;
}
ll egcd(ll a, ll b, ll &x, ll &y) {
	if(!b) { x = 1, y = 0; return a; }
	ll ret = egcd(b, a%b, y,x);
	y -= (a/b)*x;
	return ret;
}
ll inv(ll n, ll mod) {
	ll x, y;
	ll gcd = egcd(n, mod, x,y);
	return (x+mod)%mod;
}
ll CRT(vector<ll> &a, vector<ll> &m) {
	ll M = 1, ret = 0;
	for(ll num : m) M *= num;
	for(int i = 0; i < a.size(); i++) {
		ll x = M / m[i];
		ll add = ((a[i] * x) % M) * inv(x, m[i]) % M;
		ret = (ret + add) % M;
	} return ret;
}

ll s_fact[maxn];
ll spf(ll x, ll p, ll mod){
    ll ret = Pow(s_fact[mod - 1], x / mod, mod);
    if (x >= p) ret = ret * spf(x / p, p, mod) % mod;
    return ret * s_fact[x % mod] % mod;
}
ll C_mod_p_q(ll n, ll r, ll p, ll q) {
	if(r > n) return 0;
	if(n == r || r == 0) return 1;
	ll M = Pow(p, q, 1e18);
	ll t = Leg(n, p) - Leg(r, p) - Leg(n-r, p);
	if(t >= q) return 0;
	s_fact[0] = 1;
	for(ll i = 1; i < M; i++)
		s_fact[i] = s_fact[i-1]*( (i%p) ? i : 1) % M;
	ll res = spf(n, p,M);
	res *= inv(spf(r,p,M) * spf(n-r, p, M) % M, M);
	res %= M;
	res *= Pow(p, t, M);
	return res % M;
}
ll C(ll n, ll r, int mod){
	if(r > n || mod == 1) return 0;
	if(n == r || r == 0) return 1;
	vector<ii> ppf = factorize(mod);
	vector<ll> a, m;
	for(ii p : ppf) {
		ll pp = Pow(p.first, p.second, 1e7);
		ll aa = C_mod_p_q(n, r, p.first, p.second);
		a.push_back(aa);
		m.push_back(pp);
	} return CRT(a, m);
}
