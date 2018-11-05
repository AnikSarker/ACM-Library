typedef vector<int> vi;
typedef vector<pair<int,int> > vpi;
vpi compressTree(const vector<int>& subset) {
    vi rev(n+1);
    vi li = subset;
    auto cmp = [&](int a, int b) {
        return st[a] < st[b];
    };
    sort(li.begin(),li.end(), cmp);
    int m = li.size()-1;
    for(int i=0; i<m; i++) {
        int a = li[i], b = li[i+1];
        li.push_back(lca(a, b));
    }
    sort(li.begin(),li.end(), cmp);
    li.erase(unique(li.begin(),li.end()), li.end());
    for(int i=0; i<li.size(); i++)rev[li[i]] = i;
    vpi ret = {pair<int,int>(0, li[0])};
    for(int i=0; i<li.size()-1; i++) {
        int a = li[i], b = li[i+1];
        ret.emplace_back(rev[lca(a, b)],b);
    }
    return ret;
}
