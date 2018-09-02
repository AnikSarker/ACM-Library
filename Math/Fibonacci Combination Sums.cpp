//Fibonacci Combination Sums (Binet's Formula)
#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MOD 1000000007
#define MAXK 205

ll bigMOD(ll n,ll r){
    if(r==0) return 1LL;
    ll ret = bigMOD(n,r/2);
    ret = (ret*ret)%MOD;
    if(r%2==1) ret = (ret*n)%MOD;
    return ret;
}

ll inverse(ll x) {return bigMOD(x%MOD, MOD - 2);}
ll cMOD(ll x) {x%=MOD; return (x>=0) ? x : x+MOD;}

struct cong{
    ll a, b;
    cong (ll x, ll y) {a = cMOD(x); b = cMOD(y);}
    cong operator + (const cong &x) const {
        return cong(a + x.a, b + x.b);
    }
    cong operator - (const cong &x) const {
        return cong(a - x.a, b - x.b);
    }
    cong operator * (const cong &x) const {
        ll c = x.a;
        ll d = x.b;
        return cong((a * c) + (5 * b * d), (a * d) + (b * c));
    }
    cong operator / (ll x) const {
        return cong(a * inverse(x), b * inverse(x));
    }
    cong operator / (const cong g) const {
        ll c = g.a;
        ll d = g.b;
        ll x = cMOD(a*c - 5*b*d) * inverse(c*c - 5*d*d);
        ll y = cMOD(a*d - b*c) * inverse(5*d*d - c*c);
        return cong(x, y);
    }
};

cong bigMOD(cong n, ll r) {
    if(r==0) return cong(1, 0);
    cong ret = bigMOD(n,r/2);
    ret = ret * ret;
    if(r%2 == 1) ret = ret * n;
    return ret;
}

cong geosum(cong x, ll n) {
    if(x.a == 1 && x.b == 0) return cong(n+1, 0);
    return (bigMOD(x, n+1) - cong(1, 0)) / (x - cong(1, 0));
}

cong alpha = cong(1, 1) / 2;
cong beta  = cong(1, -1) / 2;

ll c[MAXK][MAXK];
ll a[MAXK][MAXK];

ll fibPower(ll n, int m) {
    cong ans = cong(0, 0);
    for(int j = 0; j <= m; j++) {
        cong t = bigMOD(alpha, j) * bigMOD(beta, m - j);
        cong x = cong(c[m][j], 0) * geosum(t, n);
        if((m - j) & 1) ans = ans - x;
        else ans = ans + x;
    }
    ans = ans * bigMOD((cong(0, 1) / 5), m);
    return ans.a;
}

void PreCalc(){
    for(int i = 0; i < MAXK; i++) {
        c[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
            c[i][j] %= MOD;
        }
    }

    a[0][0] = 1;
    for(int i = 1; i < MAXK; i++) {
        a[i][0] = 1;
        for(int j = 1; j <= i+1; j++) {
            a[i][j] = a[i - 1][j] + i * a[i - 1][j - 1];
            a[i][j] %= MOD;
        }
    }
}

// query(n,k) = sum of C(Fib(i),k) in range 0 <= i <=n
ll query(ll n, int k) {
    if(n < 0) return 0;
    ll ans = 0;
    for(int i = 0; i <= k; i++) {
        ll x = a[k - 1][i] * (fibPower(n + 2, k - i) - 1);
        if(i & 1) ans = cMOD(ans - x);
        else ans = cMOD(ans + x);
    }
    for(int i = 1; i <= k; i++) {ans *= inverse(i); ans %= MOD;}
    return ans;
}

int main(){
    PreCalc();

    ll k, l, r;
    scanf("%lld %lld %lld",&k,&l,&r);
    ll ans = query(r, k) - query(l-1, k);
    cout << cMOD(ans) << endl;
}
