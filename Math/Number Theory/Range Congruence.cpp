#include<bits/stdc++.h>
using namespace std;
#define ll long long int

// finds minimum x such that L <= (A * x) % P <= R
// constraint : 0 < A < P and 0 <= L <= R < P
// returns -1 if no solution exists

ll cdiv(ll x, ll y) {return (x+y-1)/y;}
ll get(ll A, ll P, ll L, ll R) {
	if(A == 0) return L == 0 ? 0 : -1;
	ll c = cdiv(L, A);
	if(A*c <= R) return c;
	ll B = P % A;

	// P = k * A + B, L <= A * (x - K * y) - B * y <= R
	// => -R <= (B * y) % A <= -L
	auto y = get(B, A, A - R % A, A - L % A);
	return y == -1 ? y : cdiv(L + B * y, A) + P / A * y;
}
