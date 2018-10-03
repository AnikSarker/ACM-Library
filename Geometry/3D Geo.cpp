#include<bits/stdc++.h>
using namespace std;

const double eps=1e-10;
inline int dcmp (double x) { if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct Point{
    double x, y, z;
    Point() {}
    void read () {cin>>x>>y>>z;}
    void write () {cout<<x<<" --- "<<y<<" --- "<<z<<"\n";}

    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}
    Point operator +(Point b)  {return Point(x+b.x,y+b.y, z+b.z);}
    Point operator -(Point b)  {return Point(x-b.x,y-b.y, z-b.z);}
    Point operator *(double b) {return Point(x*b,y*b, z*b);}
    Point operator /(double b) {return Point(x/b,y/b, z/b);}
    bool operator  <(Point b)  {return make_pair(make_pair(x,y),z) < make_pair(make_pair(b.x,b.y),b.z);}
    bool operator ==(Point b)  {return dcmp(x-b.x)==0 && dcmp(y-b.y) == 0 && dcmp(z-b.z) == 0;}

};
typedef Point Vector;

namespace Vectorial{
    double getDot (Vector a, Vector b)  {return a.x*b.x+a.y*b.y+a.z*b.z;}
    Vector getCross(Vector a, Vector b) {return Point(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);}
    double getLength (Vector a) { return sqrt(getDot(a, a)); }
    double getPLength (Vector a) { return getDot(a, a); }
    Vector unitVector(Vector v){return v/getLength(v);}
}

struct Line{
    Point d, u;
    Line(Point d,Point u):d(d),u(u){}
    Point getPoint(double t) {return u + d*t;}
};

struct Plane{
    Vector n;
    double d;
    Plane() {}
    Plane(Vector n, double d) : n(n), d(d) {}
    Plane(const Plane &p) : n(p.n), d(p.d) {}
};

namespace Planar{
    using namespace Vectorial;
    Plane getPlane(Point A,Point B,Point S){
        Plane p; Point z(0,0,0);
        p.n = getCross(B-S,A-S);
        if(dcmp(getDot(p.n,z-S) < 0)) p.n = getCross(A-S,B-S);
        return p;
    }
    Point rotateCCW90(Plane p,Point d){return getCross(p.n,d);}
    Point rotateCW90(Plane p,Point d) {return getCross(d,p.n);}
}

struct Pyramid{
    int n;     //number of side of the pyramid
    double l;  //length of each side
    double ang;

    Pyramid(int n, double l) {this->n=n; this->l=l; ang=pi/n;}

    double getBaseArea() {return l * l * n / (4* tan(ang));}
    double getHeight() {return l * sqrt(1 - 1 / (4*sin(ang)*sin(ang)) );}
    double getVolume() {return getBaseArea() * getHeight() / 3;}
};
