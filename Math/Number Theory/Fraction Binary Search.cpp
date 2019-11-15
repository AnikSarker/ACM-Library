/*
 * Given f and N, finds the smallest fraction p/q in [0, 1]
 * such that f(p/q) is true, and p, q <= N.
 * May throw an exception from f if it finds an exact solution,
 * in which case N can be removed.
 * Time: O(log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

struct Frac{ ll p, q;};
template<class F> Frac fracBS(F f, ll N){
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
	assert(!f(lo));
	assert(f(hi));

	while (A || B){
		ll adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B; B = !!adv;
	}
	return dir ? hi : lo;
}

int main(){
    Frac ret = fracBS([](Frac f) {return 3*f.p >= f.q;}, 10); // {1,3}
    cout<<ret.p<<" "<<ret.q<<endl;
}
