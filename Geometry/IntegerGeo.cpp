#include<bits/stdc++.h>
using namespace std;
#define ll long long int
inline ll dcmp(ll x) {return x;}

struct Fraction{
    ll m,n;
    Fraction(){}
    Fraction(ll x,ll y) {ll g=__gcd(x,y); m=x/g; n=y/g; if(n<0) {m=-m,n=-n;} }
    Fraction operator + (const Fraction& u) const {return Fraction(m*u.n+u.m*n,n*u.n); }
    Fraction operator - (const Fraction& u) const {return Fraction(m*u.n-u.m*n,n*u.n); }
    Fraction operator * (const Fraction& u) const {return Fraction(m*u.m,n*u.n); }
    Fraction operator / (const Fraction& u) const {return Fraction(m*u.n,n*u.m); }
};

struct Point{
    ll x, y;
    Point (ll x = 0, ll y = 0): x(x), y(y) {}

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const Point& u) const { return !(*this == u); }
    bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x-u.x)==0 && dcmp(y-u.y) < 0); }
    bool operator > (const Point& u) const { return u < *this; }
    bool operator <= (const Point& u) const { return *this < u || *this == u; }
    bool operator >= (const Point& u) const { return *this > u || *this == u; }
    Point operator + (const Point& u) { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) { return Point(x - u.x, y - u.y); }
    Point operator * (const ll u) { return Point(x * u, y * u); }
    ll operator * (const Point& u) { return x*u.y - y*u.x; }
};
typedef Point Vector;

namespace Vectorial {
    ll getDot (Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
    ll getCross (Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
    ll getPLength (Vector a) { return getDot(a, a); }
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

namespace Linear {
    using namespace Vectorial;

    bool getIntersection (Point p, Vector v, Point q, Vector w, Point& o) {
        if (dcmp(getCross(v, w)) == 0) return false; //parallel

        Vector u = p - q;
        ll cross1 = getCross(w, u);  ll cross2 = getCross(v, w);
        ll g = __gcd(v.x,v.y); v.x/=g; v.y/=g;   cross1 *= g;
        if(cross1 % cross2) return false; //intersection point non-integer

        ll k = cross1 / cross2;
        o = p + v * k;
        return true;
    }

    ll sign(ll x) {return x == 0 ? x : x/abs(x);}
    bool haveIntersection (Point a1, Point a2, Point b1, Point b2) {
        ll c1=getCross(a2-a1, b1-a1), c2=getCross(a2-a1, b2-a1), c3=getCross(b2-b1, a1-b1), c4=getCross(b2-b1,a2-b1);
        c1=sign(c1); c2=sign(c2); c3=sign(c3); c4=sign(c4);
        return dcmp(c1)*dcmp(c2) <= 0 && dcmp(c3)*dcmp(c4) <= 0;
    }
}
