// Tested : UVa 10245 - The Closest Pair Problem

#include <bits/stdc++.h>
using namespace std;
#define ll long long int

struct Point{
    ll x, y;
    Point() {}
    Point(ll _x, ll _y) {x = _x; y = _y;}
    bool operator < (const Point &p) const {return x == p.x ? y < p.y : x < p.x;}
    Point operator - (Point p) {return Point(x - p.x, y - p.y);}
};
ll getDot(Point a,Point b)  {return a.x * b.x + a.y * b.y;}
ll dist(Point p, Point q)   {return getDot(p-q, p-q);}

vector<Point> p;
ll solve(int l, int r) {
    if(r - l <= 3) {
        ll ret = LLONG_MAX;
        for(int i = l; i <= r; i++)
            for(int j = i + 1; j <= r; j++)
                ret = min(ret, dist(p[i], p[j]));
        return ret;
    }

    int mid = (l + r) / 2;
    ll d = min(solve(l, mid), solve(mid+1, r));

    vector<Point> t;
    for(int i = l; i <= r; i++){
        ll dx = p[mid].x - p[i].x;
        if(dx * dx <= d) t.push_back({p[i].y, p[i].x});
    }

    sort(t.begin(), t.end());
    for(int i = 0; i < t.size(); i++) {
        for(int j = i+1; j < t.size() && j <= i + 15; j++)
            d = min(d, dist(t[i], t[j]));
    }
    return d;
}

ll closestPair() {
    sort(p.begin(), p.end());
    return solve(0, p.size()-1);
}
