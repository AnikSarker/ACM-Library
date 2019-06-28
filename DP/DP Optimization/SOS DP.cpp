//SOS DP

for(int mask = 0; mask < (1<<N); mask++){
    //handle base case separately (leaf states)
    dp[mask][-1] = A[mask];
    for(int b = 0; b < N; b++){
        if(mask & (1<<b)) dp[mask][b] = dp[mask][b-1] + dp[mask^(1<<b)][b-1];
        else              dp[mask][b] = dp[mask][b-1];
    }
    F[mask] = dp[mask][N-1];
}
