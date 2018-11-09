/* Polynomial multiplication
   Algorithm: Karatsuva multiplication
   Order: n^1.58
   Note : 1) All the number should be kept in reverse order in vector
          2) initially for two numbers length should be power of 2,
             otherwise padded extra field with zero  */

#include<bits/stdc++.h>
using namespace std;
#define ll long long int

// to check if all value of A is zero
bool AllZero( vector<ll> &A ){
    for(int i=0;i<A.size();i++ ) if(A[i]) return false;
    return true;
}

// multiple to polynomial A and B , result in Ret
// A should be represented as A1*x^(n/2) + A0
// B should be represented as B1*x^(n/2) + B0
void KaratSuva( vector<ll> &A,vector<ll> &B,vector<ll> &Ret ){
    ll i,j,n = A.size();
    Ret.resize(2*n);

    // check if any polynomial is zero
    if( AllZero( A ) || AllZero( B ) ) return;

    /* normal multiplication for n lower value
    limit should be power of 2 ( 16,32,64 )
    any value can be used but 32 seems to be better */
    if(n<=32){
        for(i=0;i<n;i++) for(j=0;j<n;j++)
            Ret[i+j] += A[i]*B[j];
        return;
    }

    vector<ll> A1( A.begin()+n/2,A.end());
    vector<ll> A0( A.begin(),A.begin()+n/2 );
    vector<ll> B1( B.begin()+n/2,B.end());
    vector<ll> B0( B.begin(),B.begin()+n/2 );

    vector<ll> A1_B1,A0_B0;
    KaratSuva( A1,B1,A1_B1 );
    KaratSuva( A0,B0,A0_B0 );

    for(i=0;i<n/2;i++) {A1[i] += A0[i]; B1[i] += B0[i];}

    vector<ll> A_B;
    KaratSuva( A1,B1,A_B );
    for(i=0;i<n;i++) A_B[i] -= A1_B1[i] + A0_B0[i];

    for(i=0;i<n;i++){
        Ret[i] += A0_B0[i];
        Ret[i+n/2] += A_B[i];
        Ret[i+n] += A1_B1[i];
    }
}

int main(){
    int n;
    scanf("%d",&n);

    vector<ll> A, B;
    A.resize(n+1); B.resize(n+1);

    for(int i=0;i<=n;i++) scanf("%lld",&A[i]);
    for(int i=0;i<=n;i++) scanf("%lld",&B[i]);
    n++;
    while(n&(n-1)) A.push_back(0), B.push_back(0), n++;

    vector<ll> Ret;
    KaratSuva(A,B,Ret);
    while(Ret.back() == 0) Ret.pop_back();
}
