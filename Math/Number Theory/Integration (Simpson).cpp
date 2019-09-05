#include <bits/stdc++.h>
using namespace std;
typedef long double LD;
const LD eps = 1e-6;

LD f(LD x) {return sin(x);}

inline LD simpson(LD fl, LD fr, LD fmid, LD l, LD r){
     return (fl + fr + 4.0 * fmid) * (r-l) / 6.0;
}

LD Solve(LD slr, LD fl, LD fr, LD fmid, LD l, LD r){
	LD mid = (l + r) / 2;
	LD fml = f((l + mid) / 2);
	LD fmr = f((mid + r) / 2);
	LD slm = simpson(fl,fmid,fml,l,mid);
	LD smr = simpson(fmid,fr,fmr,mid,r);
	if( fabs(slr-slm-smr) < eps) return slm + smr;
	return Solve(slm,fl,fmid,fml,l,mid) + Solve(smr,fmid,fr,fmr,mid,r);
}

LD integrate(LD l,LD r){
	LD mid = (l+r) / 2;
	LD fl = f(l);
	LD fr = f(r);
	LD fmid = f(mid);
	LD slr = simpson(fl,fr,fmid,l,r);
	return Solve(slr,fl,fr,fmid,l,r);
}
