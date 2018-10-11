typedef int ll;
map<int,int>ck[1000006];
int id[1000006];
set<pair<int,int> >s[1000006];
int x, y, n, ans[1000006], offset[1000006];
vector<int>adj[1000006];
void go(int u,int p) {
    ck[id[u]][0]=1;
    s[id[u]].insert({-1,0});
    for(int v : adj[u]) {
        if(v==p)continue;
        go(v,u);
        if(s[id[v]].size()>s[id[u]].size()) {
            for(auto p : s[id[u]]) {
                int ki = p.second-1+offset[id[u]]-offset[id[v]];
                int koyta = ck[id[v]][ki];
                if(koyta!=0)s[id[v]].erase(s[id[v]].find({-koyta,ki}));
                koyta -= p.first ;
                s[id[v]].insert({-koyta,ki});
                ck[id[v]][ki] = koyta ;
            }
            offset[id[v]]++;
            swap(id[u],id[v]);
        } else {
            for(auto p : s[id[v]]) {
                int ki = p.second+1+offset[id[v]]-offset[id[u]];
                int koyta = ck[id[u]][ki];
                if(koyta!=0)s[id[u]].erase(s[id[u]].find({-koyta,ki}));
                koyta -= p.first ;
                s[id[u]].insert({-koyta,ki});
                ck[id[u]][ki] = koyta ;
            }
        }
    }
    auto it = *(s[id[u]].begin());
    ans[u] = it.second + offset[id[u]] ;
}
