//Check whether x=k is a root of polynomial f(x)
//Check whether f(k) = 0 efficiently

#define ll long long int
bool divisible_by_k(vector<ll>arr,int k){
    int n = arr.size();
    if(arr[0] % k != 0) return false;
    for(int i=1;i<n;i++){
        arr[i] += arr[i-1]/k;
        if(arr[i] % k != 0) return false;
    }
    return (arr[n-1] == 0);
}
