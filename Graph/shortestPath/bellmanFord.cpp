void BellmanFord() {
    for(ll i=1; i<=n; i++)for(ll j=0; j<m; j++)
            if(d[u[j]]+w[j] < d[v[j]])
                d[v[j]]=d[u[j]]+w[j],ck[v[j]]=cs;
    bool negCycle = false;
    for(ll j=0; j<m; j++)
        if(d[u[j]]+w[j] < d[v[j]]) {
            negCycle=true;
            break;
        }
}
