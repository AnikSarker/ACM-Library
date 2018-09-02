NTT ntt(mod);
vector<ll>v[MAX];

//Stirling1 (n,k) = co-eff of x^k in x*(x+1)*(x+2)*....(x+n-1)
int Stirling1(int n, int r) {
    int nn = 1;
    while(nn < n) nn <<= 1;

    for(int i = 0; i < n; ++i) {v[i].push_back(i); v[i].push_back(1);}
    for(int i = n; i < nn; ++i) v[i].push_back(1);

    for(int j = nn; j > 1; j >>= 1) {
        int hn = j >> 1;
        for(int i = 0; i < hn; ++i) ntt.multiply(v[i], v[i + hn], v[i]);
    }
    return v[0][r];
}
