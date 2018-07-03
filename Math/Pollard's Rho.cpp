#include<bits/stdc++.h>
using namespace std;
#define MAX 100005
#define ll long long int
#define pii pair<ll,int>

ll bigMod(ll n,ll r,ll Mod){
    if(r==0) return 1LL;
    ll ret=bigMod(n,r/2,Mod);
    ret=(ret*ret)%Mod;
    if(r%2==1) ret=(ret*n)%Mod;
    return ret;
}

//Miller-Rabin
bool witness(ll wit,ll n){
  if(wit>=n) return false;

  int s=0; ll t=n-1;
  while(t%2==0) s++,t/=2;

  wit=bigMod(wit,t,n);
  if(wit==1 || wit==n-1) return false;

  for(int i=1;i<s;i++){
    wit=(wit*wit)%n;
    if(wit==1) return true;
    if(wit==n - 1) return false;
  }
  return true;
}

//Is n prime?
bool miller(ll n){
  if(n==2) return true;
  if(n%2==0 || n<2) return false;
  if(witness(2,n) || witness(7,n) || witness(61,n)) return false;
  return true;
}

// Pollard's Rho
// a must not equal 0 or -2.
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

vector<pii>Factors;
vector<ll>Divisors;
void findDiv(int pos,ll val){
    if(pos<0) {Divisors.push_back(val); return;}
    ll Now=1;
    for(int i=0;i<=Factors[pos].second;i++){
        findDiv(pos-1,val*Now);
        Now=Now*Factors[pos].first;
    }
}

void findAllDiv(ll n){
    vector<ll>now=factorize(n);
    sort(now.begin(),now.end());

    Factors.clear();
    Divisors.clear();
    int Count=1;
    for(int i=1;i<now.size();i++){
        if(now[i]==now[i-1]) Count++;
        else {Factors.push_back({now[i-1],Count}); Count=1;}
    }
    Factors.push_back({now.back(),Count});
    findDiv(Factors.size()-1,1);
}

ll a[MAX];
set<ll>SET;

int main(){
    int n,k;
    scanf("%d %d",&n,&k);

    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);

    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=min(n,10);i++){
        if(a[i]==1) SET.insert(1);
        else{findAllDiv(a[i]); for(ll xx: Divisors) SET.insert(xx);}
    }

    ll Ans=1;
    for(ll now : SET){
        int Count=0;
        for(int i=n;i>=1;i--){
            if(a[i]%now!=0) Count++;
            if(Count>k) break;
        }
        if(Count<=k) Ans=now;
    }
    cout<<Ans<<endl;
}
