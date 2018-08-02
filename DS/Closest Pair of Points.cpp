// O(n (log n)^2) 
// Taken from Rezwan Arefin
typedef long long ll;
#define sq(a) ((a)*(a))
struct point { 
    ll x, y; 
    bool operator < (const point &p) const {
        return x == p.x ? y < p.y : x < p.x;
    }
};
ll dist(point &p, point &q) { return sq(p.x - q.x) + sq(p.y - q.y); }
vector<point> p;
ll solve(int l, int r) {
    if(r - l <= 3) {
        ll ret = 1e18;
        for(int i = l; i <= r; i++) 
            for(int j = i + 1; j <= r; j++) 
                ret = min(ret, dist(p[i], p[j])); 
        return ret; 
    } 
    int mid = l + r >> 1;
    ll d = min(solve(l, mid), solve(mid+1, r)); 

    vector<point> t;
    for(int i = l; i <= r; i++) 
        if(sq(p[mid].x - p[i].x) <= d) 
            t.push_back({p[i].y, p[i].x}); 
        
    sort(t.begin(), t.end()); 
    for(int i = 0; i < t.size(); i++) {
        for(int j = i+1; j < t.size() && j <= i + 15; j++) 
            d = min(d, dist(t[i], t[j])); 
    } return d;
}
ll closestPair() {
    sort(p.begin(), p.end()); 
    return solve(0, p.size()-1); 
}
