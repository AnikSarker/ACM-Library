//O(n) RMQ(Max) for all k-length subarrays of a n-length array using deque
deque<int>dq;
int A[MAX];
int n,k;

void solve(){
    for(int i=1;i<k;i++){
        while(!dq.empty() && A[dq.back()]<=A[i]) dq.pop_back();
        dq.push_back(i);
    }
    for(int i=k;i<=n;i++){
        while(!dq.empty() && A[dq.back()]<=A[i]) dq.pop_back();
        dq.push_back(i);
        while(!dq.empty() && dq.front()<=i-k) dq.pop_front();
        printf("%d ",A[dq.front()]);
    }
}
