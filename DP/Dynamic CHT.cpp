//Dynamic CHT
const ll is_query = -(1LL<<62);
const ll INF = 1LL << 60;
struct Line{ // y=m*x+b
    ll m,b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const{
        if (rhs.b!=is_query) return m<rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<Line> {// will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return 1.0*(x->b - y->b)*(z->m - y->m) > 1.0 * (y->b - z->b)*(y->m - x->m);
    }
    void Add(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll Query(ll x) {
        auto l = lower_bound((Line){x,is_query});
        if (l == end()) return -inf;
        return l->m * x + l->b;
    }
};
