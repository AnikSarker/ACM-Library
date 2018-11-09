int calc(int a,int b,int c,int d){
    int ac = lca(a,c);
    if(level[ac]<level[b])return 0 ;
    if(level[ac]<level[d])return 0 ;
    if(level[b]<level[d])swap(b,d);
    int ret = level[ac]-level[b]+1;
    return ret;
}

int solve(int a,int b,int c,int d){
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
    if(ab==cd)ans++;
    return ans;
}
