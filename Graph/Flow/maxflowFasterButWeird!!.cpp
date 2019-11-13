//....................................................................................//
only works in planer graph!!
//....................................................................................//
#include <bits/stdc++.h>

using namespace std;

const int Nmax = 1200 + 7;
const int Mmax = 100 * Nmax;
const int NIL = -1;

struct Edge
{
    int v;
    int capacity;
    int flow;

    int urm;
};

Edge Graph[Mmax];
int head[Nmax];

long long excess[Nmax];
int height[Nmax];
bool active[Nmax];
int pointer[Nmax];

int countHeight[2 * Nmax];

queue<int> Q;

int N, M, countEdges;

void addEdge(int u, int v, int cap1, int cap2)
{
    Graph[countEdges] = {v, cap1, 0, head[u]};
    head[u] = countEdges++;

    Graph[countEdges] = {u, cap2, 0, head[v]};
    head[v] = countEdges++;
}

void enqueue(int v)
{
    if (!active[v] && excess[v] > 0)
    {
        active[v] = true;
        Q.push(v);
    }
}

void gap(int k)
{
    for (int i = 1; i <= N; ++i)
    {
        if (height[i] >= k)
        {
            countHeight[ height[i] ]--;
            height[i] = max(height[i], N + 1);
            countHeight[ height[i] ]++;

            enqueue(i);
        }
    }
}

void push(int u, int p)
{
    int v = Graph[p].v;
    long long delta = min(excess[u], (long long)(Graph[p].capacity - Graph[p].flow));

    if (height[u] <= height[v] || delta == 0) return;

    Graph[p].flow += delta;
    Graph[p ^ 1].flow -= delta;

    excess[u] -= delta;
    excess[v] += delta;

    enqueue(v);
}

void relabel(int v)
{
    countHeight[ height[v] ]--;

    height[v] = 2 * N;

    for (int p = head[v]; p != NIL; p = Graph[p].urm)
    {
        if (Graph[p].capacity - Graph[p].flow > 0)
            height[v] = min(height[v], height[ Graph[p].v ] + 1);
    }

    countHeight[ height[v] ]++;

    enqueue(v);
}

void discharge(int u)
{
    bool doneGap = 0;

    while (excess[u] > 0)
    {
        if (countHeight[ height[u] ] == 1 && (doneGap == false))
        {
            gap(height[u]);

            doneGap = true;
            pointer[u] = NIL;
        }

        if (pointer[u] == NIL)
        {
            relabel(u);
            pointer[u] = head[u];
        }
        else
        {
            int p = pointer[u];
            int v = Graph[p].v;

            if (height[u] >= height[v] + 1 && Graph[p].capacity > Graph[p].flow)
                push(u, p);
            else
                pointer[u] = Graph[ pointer[u] ].urm;
        }
    }
}

void initPreflow(int S, int T)
{
    for (int i = 1; i <= N; ++i)
    {
        excess[i] = 0;
        height[i] = 0;
        pointer[i] = head[i];
    }

    height[S] = N;
    active[S] = active[T] = true;

    countHeight[N] = 1;
    countHeight[0] = N - 1;

    for (int p = head[S]; p != NIL; p = Graph[p].urm)
    {
        excess[S] += Graph[p].capacity;
        push(S, p);
    }
}

long long push_relabel(int S, int T)
{
    initPreflow(S, T);

    while (Q.empty() == false)
    {
        int v = Q.front();
        Q.pop();
        active[v] = false;
        discharge(v);
    }

    long long flow = 0;

    for (int p = head[S]; p != NIL; p = Graph[p].urm)
        flow += Graph[p].flow;

    return flow;
}

int main()
{
    ///freopen("data.in", "r", stdin);

    scanf("%d ", &N);
    countEdges = 0;

    scanf("%d ", &M);
    int s, t ;
    scanf("%d %d",&s, &t);
    for (int i = 1; i <= N; ++i)
        head[i] = NIL;

    int x, y, c;

    while (M--)
    {
        scanf("%d %d %d", &x, &y, &c);
        addEdge(x, y, c, 0);
    }

    cout << push_relabel(s, t) << "\n";
    return 0;
}

//....................................................................................//
// One limitation of the HLPP implementation is that you can't recover the weights for the full flow - use Dinic's for this.
//....................................................................................//
template <int MAXN, class T = int> struct HLPP {
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T f;
    };
    int s = MAXN - 1, t = MAXN - 2;
    vector<edge> adj[MAXN];
    vector<int> lst[MAXN], gap[MAXN];
    T excess[MAXN];
    int highest, height[MAXN], cnt[MAXN], work;
    void addEdge(int from, int to, int f, bool isDirected = true) {
        adj[from].push_back({to, adj[to].size(), f});
        adj[to].push_back({from, adj[from].size() - 1, isDirected ? 0 : f});
    }
    void updHeight(int v, int nh) {
        work++;
        if (height[v] != MAXN)
            cnt[height[v]]--;
        height[v] = nh;
        if (nh == MAXN)
            return;
        cnt[nh]++, highest = nh;
        gap[nh].push_back(v);
        if (excess[v] > 0)
            lst[nh].push_back(v);
    }
    void globalRelabel() {
        work = 0;
        fill(all(height), MAXN);
        fill(all(cnt), 0);
        for (int i = 0; i < highest; i++)
            lst[i].clear(), gap[i].clear();
        height[t] = 0;
        queue<int> q({t});
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v])
                if (height[e.to] == MAXN && adj[e.to][e.rev].f > 0)
                    q.push(e.to), updHeight(e.to, height[v] + 1);
            highest = height[v];
        }
    }
    void push(int v, edge &e) {
        if (excess[e.to] == 0)
            lst[height[e.to]].push_back(e.to);
        T df = min(excess[v], e.f);
        e.f -= df, adj[e.to][e.rev].f += df;
        excess[v] -= df, excess[e.to] += df;
    }
    void discharge(int v) {
        int nh = MAXN;
        for (auto &e : adj[v]) {
            if (e.f > 0) {
                if (height[v] == height[e.to] + 1) {
                    push(v, e);
                    if (excess[v] <= 0)
                        return;
                } else
                    nh = min(nh, height[e.to] + 1);
            }
        }
        if (cnt[height[v]] > 1)
            updHeight(v, nh);
        else {
            for (int i = height[v]; i <= highest; i++) {
                for (auto j : gap[i])
                    updHeight(j, MAXN);
                gap[i].clear();
            }
        }
    }
    T calc(int heur_n = MAXN) {
        fill(all(excess), 0);
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for (auto &e : adj[s])
            push(s, e);
        for (; highest >= 0; highest--) {
            while (!lst[highest].empty()) {
                int v = lst[highest].back();
                lst[highest].pop_back();
                discharge(v);
                if (work > 4 * heur_n)
                    globalRelabel();
            }
        }
        return excess[t] + INF;
    }
};
