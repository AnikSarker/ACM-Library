#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long int

#define OR 0
#define AND 1
#define XOR 2
#define LOG 17
#define MAX (1 << 17)

//Fast Walsh-Hadamard Transformation
//Complexity : O(n log n)
//OR, AND works for any modulo, XOR works for only prime
struct fwht{
    ll P1[MAX], P2[MAX];
    inline ll cMOD(ll x)     {return x>=MOD ? x-MOD : x;}
    inline ll Add(ll a,ll b) {return cMOD(a+b);}
    inline ll Sub(ll a,ll b) {return Add(a,MOD-b);}
    inline ll Half(ll a)     {return (a & 1) ? (a+MOD)/2 : a/2;}

    void walsh_transform(ll* ar,int n,int flag = XOR){
        for(int m=1; m<n; m<<=1)
            for(int k=0; k<n; k+=m<<1)
                for(int i=k; i<k+m; i++){
                    ll x = ar[i], y = ar[i + m];
                    if (flag == OR) ar[i] = x, ar[i + m] = Add(x,y);
                    if (flag == AND) ar[i] = Add(x,y), ar[i + m] = y;
                    if (flag == XOR) ar[i] = Add(x,y), ar[i + m] = Sub(x,y);
                }
    }

    void inverse_walsh_transform(ll* ar, int n, int flag = XOR){
        for(int m=1; m<n; m<<=1)
            for(int k=0; k<n; k+=m<<1)
                for(int i=k; i<k+m; i++){
                    ll x = ar[i], y = ar[i + m];
                    if (flag == OR) ar[i] = x, ar[i + m] = Sub(y,x);
                    if (flag == AND) ar[i] = Sub(x,y), ar[i + m] = y;
                    if (flag == XOR) ar[i] = Half(Add(x,y)), ar[i + m] = Half(Sub(x, y));
                }
    }

    vector<ll> convolution(int n, ll* A, ll* B, int flag = XOR){
        assert(__builtin_popcount(n) == 1); // n must be a power of 2
        for (int i = 0; i < n; i++) P1[i] = A[i] % MOD;
        for (int i = 0; i < n; i++) P2[i] = B[i] % MOD;

        walsh_transform(P1, n, flag);
        walsh_transform(P2, n, flag);
        for (int i = 0; i < n; i++) P1[i] = (P1[i] * P2[i]) % MOD;
        inverse_walsh_transform(P1, n, flag);
        return vector<ll> (P1, P1 + n);
    }

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i or j] += A[i] * B[j]
    vector<ll> or_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, OR);}

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i and j] += A[i] * B[j]
    vector<ll> and_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, AND);}

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i xor j] += A[i] * B[j]
    vector<ll> xor_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, XOR);}

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i or j] += A[i] * B[j] when i & j = 0
    int PopCount[MAX];
    ll F1[LOG+1][MAX];
    ll F2[LOG+1][MAX];
    ll G[LOG+1][MAX];

    vector<ll> subset_or_convolution(int n, ll* A, ll* B){
        for(int i=1;i<MAX;i++) PopCount[i] = PopCount[i>>1] + (i&1);
        for(int i=0;i<n;i++) F1[PopCount[i]][i] = A[i] % MOD;
        for(int i=0;i<n;i++) F2[PopCount[i]][i] = B[i] % MOD;

        for(int i=0;i<=LOG;i++) walsh_transform(F1[i],n,OR);
        for(int i=0;i<=LOG;i++) walsh_transform(F2[i],n,OR);

        for(int i=0;i<=LOG;i++) for(int j=0;j<=i;j++) for(int k=0;k<n;k++){
            G[i][k]+=(F1[j][k]*F2[i-j][k])%MOD;
            if(G[i][k]>=MOD) G[i][k]-=MOD;
        }
        for(int i=0;i<=LOG;i++) inverse_walsh_transform(G[i],n,OR);
        for(int i=0;i<n;i++) F1[0][i]=G[PopCount[i]][i];
        return vector<ll> (F1[0], F1[0] + n);
    }
};

fwht fft;

int main(){
    //Parameter n (Size of vector) must be - 
    //1. Greater than input vector size
    //2. Power of 2 with additional 0 padding (2 --> 4,  3 --> 4, 4 --> 8)
}
