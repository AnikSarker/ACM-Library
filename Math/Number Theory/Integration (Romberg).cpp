#include <bits/stdc++.h>
using namespace std;
#define LD long double
LD eps = 1e-8;

LD f(LD x) {return sin(x);}

LD romberg(LD a, LD b){
    vector<LD>t;
    LD h = b-a;
    LD last, curr;
    int k = 1;
    int i = 1;
    t.push_back(h*(f(a)+f(b))/2);

    while(true){
        last = t.back(); curr=0;
        LD x = a+h/2;
        for(int j=0;j<k;j++) curr += f(x), x += h;
        curr = (t[0] + h*curr) / 2;
        LD k1 = 4.0/3.0, k2 = 1.0/3.0;

        for(int j=0; j<i; j++){
            LD temp = k1 * curr - k2 * t[j];
            t[j] = curr; curr = temp;
            k2 /= 4*k1 - k2;
            k1 = k2 + 1;
        }
        t.push_back(curr);
        k *= 2; h /= 2; i++;
        if(fabs(last-curr) < eps) break;
    }
    return t.back();
}
