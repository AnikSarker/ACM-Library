#include<bits/stdc++.h>
using namespace std;

struct Line {
    int a,b,c;
    Line(){}
    Line(int x=0,int y=0,int z=0){
        int G=__gcd(x,y);            //will equal gcd(x,y,z)
        a=x/G; b=y/G; c=z/G;
        if(a<0) {a=-a; b=-b; c=-c;}  //a=0 case auto-handled
    }
};
