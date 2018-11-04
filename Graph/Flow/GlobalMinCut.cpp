//Global Mincut ( stoer Wagner N^3)
typedef long long ll;
const ll maxN = 305 ;
const ll inf = 0x3f3f3f3f ;
// Stoer-wagner algorithm, complexity: O(n^3)
// compute the global minimum cut with self-loop ignored.
ll n,m, g[maxN][maxN];//1-indexed,initialised with 0
bool vis[maxN];
ll dis[maxN],v[maxN];
ll stoer_wagner() {
    ll i, j, now,ans=inf;
    for(i=0; i<n; i++)v[i]=i+1;
    while(n>1) {
        for(now=0,i=1; i<n; i++)dis[v[i]]=0;
        for(i=1; i<n; i++) {
            swap(v[now],v[i-1]);
            for(now=j=i; j<n; j++) {
                dis[v[j]]+=g[v[i-1]][v[j]];
                if(dis[v[now]]<dis[v[j]])now=j;
            }
        }
        ans=min(ans,dis[v[now]]);
        for(j=0; j<n; j++)
            g[v[j]][v[now-1]]=g[v[now-1]][v[j]]+=g[v[j]][v[now]] ;
        v[now]=v[--n];
    }
    return ans ;
}
