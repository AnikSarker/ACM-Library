// Problem  ID : UVa 12056
struct Range {
    double t;  // -pi <= t <= pi
    int evt;
    Point p;
    Range() {}
    Range(double t, int evt, Point p) : t(t), evt(evt), p(p) {}

    bool operator <(const Range &s) const {
        return dcmp(t - s.t) < 0 || (dcmp(t - s.t) == 0 && evt > s.evt);
    }
};

const int MAX = 1005;
Circle C[MAX];
vector<Range>R;

bool cmp_r(const Circle &a, const Circle &b) {return a.r > b.r;}
double AreaUnionCircle(Circle C[], int &n){
    using namespace Vectorial;
    using namespace Circular;

    sort(C, C + n, cmp_r);
    int k = 0;
    for (int i = 0; i < n; i++){
        if (dcmp(C[i].r) == 0) break;
        int j = 0;
        for (j = 0; j < k; j++) //interior or concentric
            if(getPos(C[i],C[j]) < 0 || !dcmp(getLength(C[i].o - C[j].o))) break;
        if (j == k) C[k++] = C[i];
    }
    n = k;

    double ans = 0;
    for (int i = 0; i < n; ++ i){
        int nc = 0;
        R.clear();
        Point mpi = Point(- C[i].r, 0) + C[i].o;
        R.push_back(Range(-pi,  1, mpi));
        R.push_back(Range( pi, -1, mpi));

        for (int j = 0; j < n; ++ j){
            if (j == i) continue;

            vector<Point>sol;
            int ret = getCircleCircleIntersection(C[i],C[j],sol);
            if(ret<2) continue;

            Point a = sol[0]; Point b = sol[1];
            double jR = getAngle(a - C[i].o), jL = getAngle(b - C[i].o);
            if (dcmp(jR - jL) > 0) ++ nc;
            R.push_back(Range(jR,  1, a));
            R.push_back(Range(jL, -1, b));
        }
        sort(R.begin(),R.end());

        double pj = - pi;
        Point  pp = mpi;
        for(Range rng : R){
            nc += rng.evt;
            if((nc == 2 && rng.evt > 0) || nc == 0)
                ans += C[i].sector(rng.t - pj) + getCross(pp,rng.p) / 2;
            pj = rng.t; pp = rng.p;
        }
    }
    return ans;
}
