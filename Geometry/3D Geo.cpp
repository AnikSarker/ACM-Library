#include<bits/stdc++.h>
using namespace std;

const double pi = 4 * atan(1);
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
    double getUnsignedAngle(Vector u,Vector v) {
        double cosTheta = getDot(u,v)/getLength(u)/getLength(v);
        cosTheta = max(-1.0,min(1.0,cosTheta));
        return acos(cosTheta);
    }
    Vector unitVector(Vector v){return v/getLength(v);}
}

struct Line{
    Vector v; Point o;
    Line(Vector v,Point o):v(v),o(o){}
    Point getPoint(double t) {return o + v*t;}
};

namespace Linear{
    using namespace Vectorial;
    double getDistSq(Line l, Point p)   {return getPLength(getCross(l.v,p-l.o))/getPLength(l.v);}
    double getDistLinePoint(Line l, Point p)   {return sqrt(getDistSq(l,p));}
    bool cmp(Line l,Point p, Point q)   {return getDot(l.v,p) < getDot(l.v,q);}
    Point projection(Line l,Point p)    {return l.o + l.v * getDot(l.v,p-l.o)/getPLength(l.v);}
    Point reflection(Line l,Point p)    {return projection(l,p)+projection(l,p)-p;}

    double getAngle(Line l,Line m)      {return getUnsignedAngle(l.v,m.v);}
    bool isParallel(Line p,Line q)      {return dcmp(getPLength(getCross(p.v,q.v))) == 0;}
    bool isPerpendicular(Line p,Line q) {return dcmp(getDot(p.v,q.v)) == 0;}

    double getDist(Line l, Line m) {
        Vector n = getCross(l.v, m.v);
        if(getPLength(n) == 0) return getDistLinePoint(l,m.o);
        else return fabs(getDot(m.o-l.o , n)) / getLength(n);
    }

    Point getClosestPointOnLine1(Line l,Line m){
        Vector n = getCross(l.v, m.v);
        Vector n2 = getCross(m.v, n);
        return l.o + l.v * getDot(m.o-l.o, n2) / getDot(l.v, n2);
    }
}

struct Plane{
    Vector n; //normal n
    double d; //getDot(n,p) = d for any point p on the plane
    Plane() {}
    Plane(Vector n, double d) : n(n), d(d) {}
    Plane(Vector n, Point p) : n(n), d(Vectorial :: getDot(n,p)) {}
    Plane(const Plane &p) : n(p.n), d(p.d) {}
};

namespace Planar{
    using namespace Vectorial;
    Plane getPlane(Point a,Point b,Point c) {return Plane(getCross(b-a,c-a),a);}
    Plane translate(Plane p,Vector t)   {return Plane(p.n, p.d+getDot(p.n,t));}
    Plane shiftUp(Plane p,double dist)  {return Plane(p.n, p.d+dist*getLength(p.n));}
    Plane shiftDown(Plane p,double dist)  {return Plane(p.n, p.d-dist*getLength(p.n));}

    double getSide(Plane p,Point a)     {return getDot(p.n,a)-p.d;}
    double getDistance(Plane p,Point a) {return fabs(getSide(p,a))/getLength(p.n);}
    Point projection(Plane p,Point a)   {return a-p.n*getSide(p,a)/getPLength(p.n);}
    Point reflection(Plane p,Point a)   {return a-p.n*getSide(p,a)/getPLength(p.n)*2;}

    bool intersect(Plane p, Line l, Point& a){
        if(dcmp(getDot(p.n,l.v)) == 0) return false;
        a = l.o - l.v * getSide(p,l.o) / getDot(p.n,l.v);
        return true;
    }

    bool intersect(Plane p,Plane q,Line& l){
        l.v = getCross(p.n,q.n);
        if(dcmp(getPLength(l.v)) == 0) return false;
        l.o = getCross(q.n*p.d - p.n*q.d , l.v) / getPLength(l.v);
        return true;
    }

    double getAngle(Plane p,Plane q)      {return getUnsignedAngle(p.n,q.n);}
    bool isParallel(Plane p,Plane q)      {return dcmp(getPLength(getCross(p.n,q.n))) == 0;}
    bool isPerpendicular(Plane p,Plane q) {return dcmp(getDot(p.n,q.n)) == 0;}

    bool getAngle(Plane p,Line l)         {return pi/2.0 - getUnsignedAngle(p.n,l.v);}
    bool isParallel(Plane p,Line l)       {return dcmp(getDot(p.n,l.v)) == 0;}
    bool isPerpendicular(Plane p,Line l)  {return dcmp(getPLength(getCross(p.n,l.v))) == 0;}
//    Vector rotateCCW90(Plane p,Vector d){return getCross(p.n,d);}
//    Vector rotateCW90(Plane p,Vector d) {return getCross(d,p.n);}
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
