#include <bits/stdc++.h>
using namespace std;
#define LD long double

// Equation of the form: (x_prev * l) + (x_cur * p) + (x_next * r) = rhs
struct equation{
    LD l, p, r, rhs;

    equation(){}
    equation(LD l, LD p, LD r, LD rhs = 0.0):
        l(l), p(p), r(r), rhs(rhs){}
};

// Thomas algorithm to solve tri-digonal system of equations in O(n)
vector <LD> thomas_algorithm(int n, vector <struct equation> ar){
    ar[0].r = ar[0].r / ar[0].p;
    ar[0].rhs = ar[0].rhs / ar[0].p;

    for (int i = 1; i < n; i++){
        LD v = 1.0 / (ar[i].p - ar[i].l * ar[i - 1].r);
        ar[i].r = ar[i].r * v;
        ar[i].rhs = (ar[i].rhs - ar[i].l * ar[i - 1].rhs) * v;
    }
    for (int i = n - 2; i >= 0; i--) ar[i].rhs = ar[i].rhs - ar[i].r * ar[i + 1].rhs;

    vector <LD> res;
    for (int i = 0; i < n; i++) res.push_back(ar[i].rhs);
    return res;
}
