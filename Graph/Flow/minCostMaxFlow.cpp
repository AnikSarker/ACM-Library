typedef long long ll;
const ll maxn = 20100;
const ll mod = 1e9+7;
const ll INF = 1e12;
struct Edge {
    ll from, to, cap, flow;
    ll cost;
};
struct MCMF {//0-indexed
    ll n, m, s, t;
    vector<Edge> edges;
    vector<ll> G[maxn];
    ll inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(ll n) {
        this->n = n;
        for(ll i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(ll from, ll to, ll cap, ll cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool SPFA(ll s, ll t, ll& tot_cost,ll& tot_flow) {
        for(ll i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        a[s] = INF;
        queue<ll> Q;
        Q.push(s);
        while(!Q.empty()) {
            ll u = Q.front();
            Q.pop();
            inq[u] = 0;
            for(ll i = 0; i < G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if(d[t] == INF) return false;
        tot_cost += (ll)d[t] * (ll)a[t];
        tot_flow += (ll)a[t];
        ll u = t;
        while(u != s) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }
    pair<ll,ll> Mincost(ll s, ll t) {
        ll cost = 0;
        ll flow = 0;
        while(SPFA(s, t, cost,flow));
        return {cost,flow};
    }
} mcmf;
