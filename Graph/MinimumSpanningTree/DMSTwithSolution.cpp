const int INF = 1029384756;
#define MAXN 1000
#define FOR(i,x) for(auto i :x )
struct edge_t {
    int u,v,w;
    set< pair<int,int> > add, sub;
    edge_t() : u(-1), v(-1), w(0) {}
    edge_t(int _u, int _v, int _w) {
        u = _u;
        v = _v;
        w = _w;
        add.insert({u, v});
    }
    edge_t& operator += (const edge_t& obj) {
        w += obj.w;
        for (auto it : obj.add) {
            if (!sub.count(it)) add.insert(it);
            else sub.erase(it);
        }
        for (auto it : obj.sub) {
            if (!add.count(it)) sub.insert(it);
            else add.erase(it);
        }
        return *this;
    }
    edge_t& operator -= (const edge_t& obj) {
        w -= obj.w;
        for (auto it : obj.sub) {
            if (!sub.count(it)) add.insert(it);
            else sub.erase(it);
        }
        for (auto it : obj.add) {
            if (!add.count(it)) sub.insert(it);
            else add.erase(it);
        }
        return *this;
    }
} eg[MAXN*MAXN],prv[MAXN],EDGE_INF(-1,-1,INF);
int N,M;
int cid,incyc[MAXN],contracted[MAXN];
vector<int> E[MAXN];

edge_t dmst(int rt) {
    edge_t cost;
    for (int i=0; i<N; i++) {
        contracted[i] = incyc[i] = 0;
        prv[i] = EDGE_INF;
    }
    cid = 0;
    int u,v;
    while (true) {
        for (v=0; v<N; v++) {
            if (v != rt && !contracted[v] && prv[v].w == INF)
                break;
        }
        if (v >= N) break; // end
        for (int i=0; i<M; i++) {
            if (eg[i].v == v && eg[i] .w < prv[v].w)
                prv[v] = eg[i];
        }
        if (prv[v].w == INF) // not connected
            return EDGE_INF;
        cost += prv[v];
        for (u=prv[v].u; u!=v && u!=-1; u=prv[u].u);
        if (u == -1) continue;
        incyc[v] = ++cid;
        for (u=prv[v].u; u!=v; u=prv[u].u) {
            contracted[u] = 1;
            incyc[u] = cid;
        }
        for (int i=0; i<M; i++) {
            if (incyc[eg[i].u] != cid && incyc[eg[i].v] ==
                    cid) {
                eg[i] -= prv[eg[i].v];
            }
        }
        for (int i=0; i<M; i++) {
            if (incyc[eg[i].u] == cid) eg[i].u = v;
            if (incyc[eg[i].v] == cid) eg[i].v = v;
            if (eg[i].u == eg[i].v) eg[i--] = eg[--M];
        }
        for (int i=0; i<N; i++) {
            if (contracted[i]) continue;
            if (prv[i].u>=0 && incyc[prv[i].u] == cid)
                prv[i].u = v;
        }
        prv[v] = EDGE_INF;
    }
    return cost;
}
#define F first
#define S second
void solve() {
    edge_t cost = dmst(0);
    for (auto it : cost.add) { // find a solution
        E[it.F].push_back(it.S);
        prv[it.S] = edge_t(it.F,it.S,0);
    }
}
