//Tested : LightOJ 1306 - Solutions to an Equation

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

// Diophantine equation : a * x + b * y = gcd(a, b)
// egcd computes one solution (x, y) for gcd(a,b) = g
// Note: computed value g can be negative.
// Given one solution (x0, y0), other solutions have form :
// xk = x0 + k * b / g and yk = y0 - k * a / g

ll egcd(ll a,ll b,ll &x,ll &y){
    if(a == 0) {x = 0; y = 1; return b;}
    ll x1,y1;
    ll gcd = egcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1; y = x1;
    return gcd;
}

inline ll Floor(ll p, ll q) {return p>0 ? p/q : p/q - !!(p%q);}
inline ll Ceil(ll p, ll q)  {return p<0 ? p/q : p/q + !!(p%q);}

// Number of solutions of Diophantine Eqn : Ax + By = C
// A,B,C,x,y integers and X1 <= x <= X2 and Y1 <= y <= Y2
inline ll solve(ll A,ll B,ll C,ll X1,ll X2,ll Y1,ll Y2){
    if(A<0) {A = -A; B = -B; C = -C;}
    ll G = __gcd(A,B);
    if(G && C%G) return 0;

    if(A == 0 && B == 0) return (C == 0) ? (X2 - X1 + 1) * (Y2 - Y1 + 1) : 0;
    if(A == 0) return (Y1 <= C/B && C/B <= Y2) ? (X2 - X1 + 1) : 0;
    if(B == 0) return (X1 <= C/A && C/A <= X2) ? (Y2 - Y1 + 1) : 0;

    ll x,y; 
    egcd(A,B,x,y);
    x = x * (C/G);  y = y * (C/G);

    ll newX1 = C - B * Y1, newX2 = C - B * Y2;
    if(newX1> newX2) swap(newX1, newX2);
    newX2 = Floor(newX2, A); newX1 = Ceil(newX1, A);

    if(X1 > newX2) return 0;
    if(X2 < newX1) return 0;
    X1 = max(X1, newX1); X2 = min(X2, newX2);

    ll div = abs(B/G);
    if(x < X1) return (X2 - x) / div - (X1 - 1 - x) / div;
    if(x > X2) return (x - X1) / div - (x - X2 - 1) / div;
    return 1 + (x - X1) / div + (X2 - x) / div;
}
