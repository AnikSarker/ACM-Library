#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long int

#define OR 0
#define AND 1
#define XOR 2
#define MAX (1 << 16)

// Fast Walsh-Hadamard Transformation in n log n
struct fwht{
    ll P1[MAX], P2[MAX];

    void walsh_transform(ll* ar,int n,int flag = XOR){
        if (n == 0) return;
        int i, m = n / 2;
        walsh_transform(ar, m, flag);
        walsh_transform(ar + m, m, flag);

        for (i = 0; i < m; i++){  //Don't forget MOD if required
            ll x = ar[i], y = ar[i + m];
            if (flag == OR) ar[i] = x, ar[i + m] = x + y;
            if (flag == AND) ar[i] = x + y, ar[i + m] = y;
            if (flag == XOR) ar[i] = x + y, ar[i + m] = x - y;
        }
    }

    void inverse_walsh_transform(ll* ar, int n, int flag = XOR){
        if (n == 0) return;
        int i, m = n / 2;
        inverse_walsh_transform(ar, m, flag);
        inverse_walsh_transform(ar + m, m, flag);

        for (i = 0; i < m; i++){  //Don't forget MOD if required
            ll x = ar[i], y = ar[i + m];
            if (flag == OR) ar[i] = x, ar[i + m] = y - x;
            if (flag == AND) ar[i] = x - y, ar[i + m] = y;
            if (flag == XOR) ar[i] = (x + y) / 2, ar[i + m] = (x - y) / 2; //modular inverse if required here
        }
    }

    vector<ll> convolution(int n, ll* A, ll* B, int flag = XOR){
        assert(__builtin_popcount(n) == 1); // n must be a power of 2
        for (int i = 0; i < n; i++) P1[i] = A[i];
        for (int i = 0; i < n; i++) P2[i] = B[i];

        walsh_transform(P1, n, flag);
        walsh_transform(P2, n, flag);
        for (int i = 0; i < n; i++) P1[i] = P1[i] * P2[i];
        inverse_walsh_transform(P1, n, flag);
        for(int i = 0; i < n; i++) P1[i] %= MOD;
        return vector<ll> (P1, P1 + n);
    }

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i or j] += A[i] * B[j]
    vector<ll> or_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, OR);}

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i and j] += A[i] * B[j]
    vector<ll> and_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, AND);}

    // For i = 0 to n - 1, j = 0 to n - 1 : v[i xor j] += A[i] * B[j]
    vector<ll> xor_convolution(int n, ll* A, ll* B) {return convolution(n, A, B, XOR);}
};
fwht fft;
int n, k, limit;
ll A[MAX], B[MAX];

vector<ll> o;
vector<ll>multiply(vector<ll> v1, vector<ll> v2){
    for(int i=0;i<limit;i++) A[i] = v1[i];
    for(int i=0;i<limit;i++) B[i] = v2[i];
    return fft.xor_convolution(limit,A,B);
}

int main(){
    //Size of vector must be - 
    //1. Greater than input vector size
    //2. Power of 2 with additional 0 padding (2 --> 4,  3 --> 4, 4 --> 8)
}
