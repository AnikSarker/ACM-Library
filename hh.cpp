#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll trf[2],tra[2],tbf[2],tba[2];
string s;
ll t,cs;

struct Fraction{
    ll m,n;
    Fraction(){}
    Fraction(ll x,ll y) {ll g=__gcd(x,y); m=x/g; n=y/g; if(n<0) {m=-m,n=-n;} }
    Fraction operator + (const Fraction& u) const {return Fraction(m*u.n+u.m*n,n*u.n); }
    Fraction operator - (const Fraction& u) const {return Fraction(m*u.n-u.m*n,n*u.n); }
    Fraction operator * (const Fraction& u) const {return Fraction(m*u.m,n*u.n); }
    Fraction operator / (const Fraction& u) const {return Fraction(m*u.n,n*u.m); }
};
typedef Fraction lf;

void solve(){

    for(int i=0;i<2;i++)
        scanf("%lld %lld %lld %lld",&trf[i],&tbf[i],&tra[i],&tba[i]);
    cin>>s;
    if(s[0]=='Y'){
        lf A1 = Fraction(1,tbf[1]+300);
        lf B1 = Fraction(trf[1] , tbf[1]+300);
        lf C1 = Fraction(1,tba[1]);
        lf D1 = Fraction(tra[1]+7,tba[1]);

        lf A2 = Fraction(1,tbf[0]);
        lf B2 = Fraction(trf[0]+7 , tbf[0]);
        lf C2 = Fraction(1,tba[0]+300);
        lf D2 = Fraction(tra[0],tba[0]+300);

        lf Kx = B1 - B2 + D2 - D1 ;
        lf Ky = A2 - C2 - A1 + C1 ;
        lf K = Kx / Ky ;

        if()

        ll ans = (K.m+1) / K.n ;
        ans = max(0LL,ans);
        printf("Case %lld: %lld\n",cs,ans);
    }
    else{
        lf A1 = Fraction(1,tbf[1]+300);
        lf B1 = Fraction(trf[1] , tbf[1]+300);
        lf C1 = Fraction(1,tba[1]);
        lf D1 = Fraction(tra[1],tba[1]);

        lf A2 = Fraction(1,tbf[0]+300);
        lf B2 = Fraction(trf[0] , tbf[0]+300);
        lf C2 = Fraction(1,tba[0]+300);
        lf D2 = Fraction(tra[0],tba[0]+300);

        lf Kx = B1 - B2 + D2 - D1 ;
        lf Ky = A2 + C2 ;
        lf K = Kx / Ky ;

        ll ans = (K.m+1) / K.n ;
        ans = max(1LL,ans);
        printf("Case %lld: %lld\n",cs,ans);
    }
}
int main(){
    cin>>t;
    while(cs<t){
        cs++;
        solve();

    }
    return 0;

}
