#define maxN 10
#define maxM 10
int dp[maxN][maxN]; // minimum mean cycle(allow negative weight)
double mmc(int n) {
    for (int i = 0; i < n; ++i) {
        memset(dp[i + 1], 0x7f, sizeof(dp[i + 1]));
        for (int j = 1; j <= ec; ++j) {
            int u = edge[j].u, v = edge[j].v, w = edge[j].w;
            if (dp[i][u] != maxint)
                dp[i + 1][v] = min(dp[i + 1][v],dp[i][u]+w);
        }
    }
    double res = maxdbl;
    for (int i = 1; i <= n; ++i) {
        if (dp[n][i] == maxint) continue;
        double value = -maxdbl;
        for (int j = 0; j < n; ++j) {
            value = max(value,double(dp[n][i]-dp[j][i])/(n-j));
        }
        res = min(res, value);
    }
    return res;
}
