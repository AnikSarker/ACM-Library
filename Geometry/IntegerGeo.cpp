#include<bits/stdc++.h>
using namespace std;
#define ll long long int

struct Fraction{
    ll m,n;
    Fraction(){}
    Fraction(ll x,ll y) {ll g=__gcd(x,y); m=x/g; n=y/g; if(n<0) {m=-m,n=-n;} }
    Fraction operator + (const Fraction& u) const {return Fraction(m*u.n+u.m*n,n*u.n); }
    Fraction operator - (const Fraction& u) const {return Fraction(m*u.n-u.m*n,n*u.n); }
    Fraction operator * (const Fraction& u) const {return Fraction(m*u.m,n*u.n); }
    Fraction operator / (const Fraction& u) const {return Fraction(m*u.n,n*u.m); }
};

struct Line {
    ll a,b,c;
    Line(){}
    Line(ll x=0,ll y=0,ll z=0){
        ll G=__gcd(x,y);            //will equal gcd(x,y,z)
        a=x/G; b=y/G; c=z/G;
        if(a<0) {a=-a; b=-b; c=-c;}  //a=0 case auto-handled
    }
};
