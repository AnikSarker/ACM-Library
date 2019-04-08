vector<int>cmp;
int calc(int a,int b,int c,int d) {
    int ac = lca(a,c);
    if(level[ac]<level[b])
        return 0 ;
    if(level[ac]<level[d])
        return 0 ;
    if(level[b]<level[d])
        swap(b,d);
    int ret = level[ac]-level[b]+1;
    cmp.push_back(ac);
    cmp.push_back(b);
    return ret;
}
pair<int,int> solve(int a,int b,int c,int d) {
    cmp.clear();
    int ab= lca(a,b);
    int cd= lca(c,d);
    int ans = 0;
    ans += calc(a,ab,c,cd);
    ans += calc(a,ab,d,cd);
    ans += calc(b,ab,c,cd);
    ans += calc(b,ab,d,cd);
    int f = 0;
    f += calc(ab,ab,c,cd);
    f += calc(ab,ab,d,cd);
    f += calc(a,ab,cd,cd);
    f += calc(b,ab,cd,cd);
    ans -= f ;
    if(ab==cd)
        ans++;
    sort(cmp.begin(),cmp.end());
    cmp.erase(unique(cmp.begin(),cmp.end()),cmp.end());
    pair<int,int>ret={-1,-1};
    assert(cmp.size()<=3);
    int mxdis=0;
    for(int i=0;i<cmp.size();i++){
        for(int j=i;j<cmp.size();j++){
            int u = cmp[i];
            int v = cmp[j];
            int lc = lca(u,v);
            int dis = level[u]+level[v]-2*level[lc]+1;
            if(dis>mxdis){
                ret={u,v};
                mxdis=dis;
            }
        }
    }
    return ret ;
}
