//0-indexed , root = 0 
typedef vector<pair<int,int> > vpi;
typedef vector<vpi> graph;
typedef long long ll ;
int sz(graph& C) {
    return C.size();
}
template<class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) {
        int N = V.size(), on = 1, depth = 1;
        while (on < V.size() ) on *= 2, depth++;
        jmp.assign(depth, V);
        for(int i=0; i<depth-1; i++)  for(int j=0; j<N; j++)
                jmp[i+1][j]=min(jmp[i][j],jmp[i][min(N-1,j+(1<<i))]);
    }
    T query(int a, int b) {
        assert(a < b); // or return inf if a == b
        int dep = 31-__builtin_clz(b-a);
        return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
    }
};
struct LCA {
    vector<int> time;
    vector<long long> dist;
    RMQ<pair<int,int> > rmq;
    LCA(graph& C) : time(sz(C), -99), dist(sz(C)), rmq(dfs(C)) {}
    vpi dfs(graph& C) {
        vector<tuple<int, int, int, ll>> q(1);
        vector<pair<int,int> > ret;
        int T = 0, v, p, d;
        ll di;
        while (!q.empty()) {
            tie(v, p, d, di) = q.back();
            q.pop_back();
            if (d) ret.emplace_back(d, p);
            time[v] = T++;
            dist[v] = di;
            for(auto &e: C[v]) if (e.first != p)
                    q.emplace_back(e.first, v, d+1, di + e.second);
        }
        return ret;
    }
    int query(int a, int b) {
        if (a == b) return a;
        a = time[a], b = time[b];
        return rmq.query(min(a, b), max(a, b)).second;
    }
    long long distance(int a, int b) {
        int lca = query(a, b);
        return dist[a] + dist[b] - 2 * dist[lca];
    }
};
