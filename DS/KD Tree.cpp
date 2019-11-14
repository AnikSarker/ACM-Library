#include<bits/stdc++.h>
using namespace std;
const int N = 200555, K = 2;
typedef long long ll;
#define sqr(x) ((x) * (x))

int k = 2, idx; 
// idx = current dimension, k = total dimension

struct Point{
    int pr, id;
    ll x[K];
    bool operator < (const Point &u) const {return x[idx] < u.x[idx];}
}po[N];

typedef pair < ll , Point > tp;
priority_queue < tp > nq;

struct KDtree{
    Point pt[N<<2];
    int son[N<<2], mn[N<<2];

    void init(){
        memset(son, 0, sizeof(son));
        memset(mn, 0, sizeof(mn));
    }
    
    void build(int l, int r, int node = 1, int dep = 0)    {
        if(l > r) return;
        son[node] = r - l;
        son[node * 2] = son[node * 2 + 1] = -1;
        idx = dep % k;
        int mid = (l + r) / 2;
        nth_element(po + l, po + mid, po + r + 1);
        pt[node] = po[mid];
        mn[node] = po[mid].pr;

        build(l, mid - 1, node * 2, dep + 1);
        build(mid + 1, r, node * 2 + 1, dep + 1);

        mn[node] = min(mn[node], min(mn[node * 2], mn[node * 2 + 1]));
    }

    void query(Point p, int m, int node = 1, int dep = 0){
        if(son[node] == -1) return;
        tp nd(0, pt[node]);
        for(int i = 0; i < k; i++) nd.first += sqr(nd.second.x[i] - p.x[i]);
        int dim = dep % k;
        int lft = 2 * node, rgh = 2 * node + 1, fg = 0;
        if(p.x[dim] >= pt[node].x[dim]) swap(lft, rgh);

        if(nd.second.pr > p.pr) nd.first = 1e18;
        if(~son[lft] && mn[lft] <= p.pr) query(p, m, lft, dep + 1);

        if(nq.size() < m) nq.push(nd), fg = 1;
        else{
            if(nd.first < nq.top().first) nq.pop(), nq.push(nd);
            else if(nd.first == nq.top().first && nd.second.id < nq.top().second.id) nq.pop(), nq.push(nd);
            if(sqr(p.x[dim] - pt[node].x[dim]) <= nq.top().first) fg = 1;
        }
        if(~son[rgh] && fg && mn[rgh] <= p.pr) query(p, m, rgh, dep + 1);
    }
}kdt;
int T, n, m, root;

int main(){
    cin >> T;

    while(T--){
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++){
            scanf("%lld %lld %lld", &po[i].x[0], &po[i].x[1], &po[i].pr);
            po[i].id = i;
        }

        kdt.build(1, n);
        while(m--){
            Point p;
            scanf("%lld %lld %lld", &p.x[0], &p.x[1], &p.pr);
            kdt.query(p, 1);
            if(nq.empty()){
                printf("-1\n");
                continue;
            }
            printf("%lld %lld %d\n", nq.top().second.x[0], nq.top().second.x[1], nq.top().second.pr);
            while(!nq.empty()) nq.pop();
        }
    }
}
