#include<bits/stdc++.h>
using namespace std;

ll bigMod(ll n,ll r,ll Mod){
    if(r==0) return 1LL;
    ll ret=bigMod(n,r/2,Mod);
    ret=(ret*ret)%Mod;
    if(r%2==1) ret=(ret*n)%Mod;
    return ret;
}

//MILLER-RABIN
bool witness(ll wit,ll n){
  if(wit>=n) return false;

  int s=0; ll t=n-1;
  while(t%2==0) s++,t/=2;

  wit=bigMod(wit,t,n);
  if(wit==1 || wit==n-1) return false;

  for(int i=1;i<s;i++) {
    wit=(wit*wit)%n;
    if(wit==1) return true;
    if(wit == n - 1) return false;
  }
  return true;
}

//Is n Prime ---> true/false
bool miller(ll n){
  if(n==2) return true;
  if(n%2==0 || n<2) return false;
  if(witness(2,n) || witness(7,n) || witness(61,n)) return false;
  return true;
}

// POLARD'S RHO
// a - parameter, shall not be equal to 0 or -2.
// returns a divisor, a proper one when succeeded, equal to n if failed
// in case of failure, change a
ll rho(ll n,ll a) {
  auto f=[&](ll x) {return ((x*x)%n+a)%n; };
  ll x=2,y=2;
  while(true){
    x=f(x); y=f(f(y));
    ll d=__gcd(n,abs(x-y));
    if(d!=1) return d;
  }
}

ll get_factor(ll n){
  if(n%2==0) return 2;
  if(n%3==0) return 3;
  if(n%5==0) return 5;
  while(true){
    ll a=2+rand()%100;
    ll d=rho(n,a);
    if(d!=n) return d;
  }
}

void factorize(ll n,vector<ll> &x) {
  if(n==1) return;
  else if(miller(n)) x.push_back(n);
  else {ll d=get_factor(n); factorize(d,x); factorize(n/d,x);}
}

vector<ll>factorize(ll n) {vector<ll>x; factorize(n, x); return x;}
