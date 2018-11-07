///SOS_DP

if((mask & (1 << pos)) == true){
    dp[pos][mask] = dp[pos - 1][mask] + dp[pos - 1][mask ^ (1 << pos)]
}
else dp[pos][mask] = dp[pos - 1][mask];
