// man-preference's priority is high
const int maxn=1050;
queue<int> q;
int future_wife[maxn],future_husband[maxn],
order[maxn][maxn],perfer[maxn][maxn],nextt[maxn];
//order[i][j]=indexOfMan i in j-th women'sListOfPreference
//prefer[i]=listOfWomen inOrderOf decreasingPreference
void enage(int man,int woman) {
    int m1=future_husband[woman];
    if(m1==0) {
        future_husband[woman]=man;
        future_wife[man]=woman;
    } else {
        future_wife[m1]=0;
        future_husband[woman]=man;
        future_wife[man]=woman;
        q.push(m1);
    }
}
void stableMarriage() {
    while(!q.empty())q.pop();
    int n,x;scanf("%d",&n);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++)
            scanf("%d",&perfer[i][j]);
        nextt[i]=1;q.push(i);future_wife[i]=0;
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++)
            scanf("%d",&x),order[i][x]=j;
        future_husband[i]=0;
    }
    while(!q.empty()) {
        int man=q.front();q.pop();
        int woman=perfer[man][nextt[man]++];
        if(future_husband[woman]==0)enage(man,woman);
        else if(order[woman][man]<order[woman][future_husband[woman]])enage(man,woman);
        else q.push(man);
    }
}
