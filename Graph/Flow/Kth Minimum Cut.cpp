//finding weight of the Kth Minimum Cut
//courtesy : antiquality
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 103;
const int maxm = 5035;
const int INF = 1e9;
struct Edge
{
    int u,v,f,c;
    Edge(int a=0, int b=0, int c=0, int d=0):u(a),v(b),f(c),c(d) {}
}edges[maxm],e[maxm];
struct node
{
    int len,val;
    bool a[maxn];
    bool operator < (node a) const
    {
        return val > a.val;
    }
    void init(){memset(a, 0, sizeof a);}
}tmp,trans;
bool vis[maxn];
int n,m,k,S,T,src,snk;
int edgeTot,head[maxn],nxt[maxm],lv[maxn];
priority_queue<node> q;

void addedge(int u, int v, int c)
{
    edges[edgeTot] = Edge(u, v, 0, c), nxt[edgeTot] = head[u], head[u] = edgeTot, ++edgeTot;
    edges[edgeTot] = Edge(v, u, 0, 0), nxt[edgeTot] = head[v], head[v] = edgeTot, ++edgeTot;
}
bool buildLevel()
{
    queue<int> q;
    memset(lv, 0, sizeof lv);
    q.push(S), lv[S] = 1;
    for (int tmp; q.size(); )
    {
        tmp = q.front(), q.pop();
        for (int i=head[tmp]; i!=-1; i=nxt[i])
        {
            int v = edges[i].v;
            if (edges[i].f < edges[i].c&&!lv[v]){
                lv[v] = lv[tmp]+1, q.push(v);
                if (v==T) return true;
            }
        }
    }
    return false;
}
int fndPath(int x, int lim)
{
    if (!lim||x==T) return lim;
    int sum = 0;
    for (int i=head[x]; i!=-1&&sum < lim; i=nxt[i])
    {
        int v = edges[i].v, val = 0;
        if (lv[v]==lv[x]+1&&edges[i].f < edges[i].c){
            if ((val = fndPath(v, min(edges[i].c-edges[i].f, lim-sum)))){
                sum += val, edges[i].f += val, edges[i^1].f -= val;
            }else lv[v] = -1;
        }
    }
    return sum;
}
int dinic()
{
    int ret = 0, val = 0;
    while (buildLevel())
        while ((val = fndPath(S, INF))) ret += val;
    return ret;
}
void calc(node &x)
{
    memset(head, -1, sizeof head), edgeTot = 0;
    for (int i=1; i<=m; i++) addedge(e[i].u, e[i].v, e[i].c);
    addedge(S, src, INF), addedge(snk, T, INF);
    for (int i=1; i<=x.len; i++)
        if (x.a[i]) addedge(S, i, INF);
        else addedge(i, T, INF);
    queue<int> q;
    x.val = dinic(), q.push(S);
    memset(vis, 0, sizeof vis);
    for (int i=1; i<=n; i++) x.a[i] = 0;
    for (int tmp; q.size(); )
    {
        tmp = q.front(), q.pop();
        for (int i=head[tmp]; i!=-1; i=nxt[i])
            if (edges[i].f < edges[i].c){
            int v = edges[i].v;
            if (!vis[v]) vis[v] = true, x.a[v] = 1, q.push(v);
        }
    }
}
void solve()
{
    scanf("%d%d%d%d%d",&n,&m,&k,&src,&snk), S = 0, T = n+1;
    for (int i=1; i<=m; i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
    tmp.len = 0, tmp.a[src] = true, calc(tmp), q.push(tmp);
    while (--k)
    {
        tmp = q.top(), q.pop();
        for (int i=tmp.len+1; i<=n; i++)
        {
            trans.init(), trans.len = i, trans.a[i] = !tmp.a[i];
            for (int j=1; j<i; j++) trans.a[j] = tmp.a[j];
            calc(trans), q.push(trans);
        }
    }
    printf("%d\n",q.top().val);
}
