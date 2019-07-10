//Offline CHT
struct Line{
    ll m,c;
    Line(ll x,ll y){m=x; c=y;}
    ll Get(ll x) {return m*x+c;}
    bool operator<(const Line &other) const {return m < other.m;}
};

bool Bad(Line &P,Line &C,Line &N){
    return (P.c-C.c) * 1.0L * (N.m-P.m) > (P.c-N.c) * 1.0L * (C.m - P.m);
}

//This Convex Hull always maintains lower convex hull
//m1 >= m2 >= m3 .... >= mk
//For Min Query : Add(m,c)
//For Max Query : Add(-m,-c)

struct ConvexHull{
    vector<Line>hull;
    
    void Add(ll m,ll c){
        //always maintaining the minimum c in case multiple equal m
        if(hull.size()>0 && hull.back().m==m) {
            if(hull.back().c>c) hull.pop_back();
            else return;
        }

        hull.push_back(Line(m, c));
        int sz=hull.size();
        while(sz>2 && Bad(hull[sz-3],hull[sz-2],hull[sz-1])){
            swap(hull[sz-2],hull[sz-1]); hull.pop_back(); sz--;
        }
    }

    ll Query(ll x){
        int lo=-1;
        int hi=hull.size()-1;
        while(hi-lo>1) {
            int mid=(lo+hi)/2;
            if(hull[mid].Get(x)>=hull[mid+1].Get(x)) lo=mid;
            else hi=mid;
        }
        if(hi<0 || hi>=hull.size()) return INF;
        return hull[hi].Get(x);
    }
};
