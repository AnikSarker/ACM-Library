//Complexity : O(n^2) for any k <= n
#include<bits/stdc++.h>
using namespace std;
#define MAX 5005
#define ll long long int

ll M[MAX];
const ll INVALID = LLONG_MIN;
ll C[MAX][MAX],dp[MAX][MAX],Opt[MAX][MAX];
//Recurrence : dp[i][j] = min/max i <= k <= j (dp[i-1][k-1] + C[k][j])
//Condition  : Opt[i-1][j] <= Opt[i][j] <= Opt[i][j+1]

int main(){
    int N,K;
    scanf("%d %d",&N,&K);
    for(int i=1;i<=N;i++) scanf("%lld",&M[i]);
    for(int i=1;i<=N;i++) for(int j=i;j<=N;j++) C[i][j]=C[i][j-1] | M[j];

    for(int i=0;i<=K;i++) dp[i][0]=0;
    for(int i=0;i<=K;i++) for(int j=1;j<=N;j++) dp[i][j]=INVALID;
    for(int i=1;i<=N;i++) {Opt[0][i]=1; Opt[i][N+1]=N;}

    for(int i=1;i<=K;i++){
        for(int j=N;j>=1;j--){
            for(int k=Opt[i-1][j];k<=Opt[i][j+1];k++){
                if(dp[i-1][k-1]== INVALID) continue;
                if(dp[i][j]<dp[i-1][k-1]+C[k][j]){
                    dp[i][j]=dp[i-1][k-1]+C[k][j];
                    Opt[i][j]=k;
                }
            }
        }
    }
    printf("%lld\n",dp[K][N]);
}
