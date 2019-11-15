/*********************************
 * polyinv(a, b, n) calculates b: b(z)a(z) = 1 (mod z^n)
 * polysqrt(a, b, n) calculates b: b(z)^2 = a(z) (mod z^n)
 * make sure ta[], tb[] has 2n spaces to be used. 
 * in polysqrt(), if a[0] != 1 then discrete sqrt function is needed
*/
 
int ta[N], tb[N], tc[N];
void prepare(int n) { init(n >> 1); }
void ntt(int *a, int n, ll f){
    for(int i=0; i<n; i++) A[i] = a[i];
    ntransform(A, f);
    for(int i=0; i<n; i++) a[i] = A[i];
}

void polyinv(int *a, int *b, int n) { 
	if(n == 1) return void(b[0] = Pow(a[0], mod - 2)); 
	polyinv(a, b, n >> 1); 
	for(int i = 0; i < n; ++i) 
		ta[i] = a[i], tb[i] = b[i]; 
	for(int i = n; i < (n << 1); ++i) 
		ta[i] = tb[i] = 0; 
	n <<= 1; prepare(n); 
	ntt(ta, n, 0), ntt(tb, n, 0); 
	for(int i = 0; i < n; ++i)
		b[i] = (ll) tb[i] * (2 + mod - (ll) ta[i] * tb[i] % mod) % mod; 
	ntt(b, n, 1);
	fill(b + (n >> 1), b + n, 0);
}

int inv2 = Pow(2, mod - 2); 
void polysqrt(int *a, int *b, int n) {
	if(n == 1) return void(b[0] = 1); // b[0] = x: x^2 \equiv a[0] 
	polysqrt(a, b, n >> 1); 
	polyinv(b, tb, n);
	for(int i = 0; i < n; ++i) 
		ta[i] = a[i]; 
	for(int i = n; i < (n << 1); ++i) 
		ta[i] = tb[i] = 0; 
	n <<= 1; prepare(n); 
	ntt(ta, n, 0); ntt(tb, n, 0); 
	for(int i = 0; i < n; ++i) 
		ta[i] = (ll) ta[i] * tb[i] % mod;
	ntt(ta, n, 1);
	for(int i = 0; i < n; ++i) 
		b[i] = (ll) inv2 * (ta[i] + b[i]) % mod;
	fill(b + (n >> 1), b + n, 0);
}
