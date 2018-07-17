//Gaussian Elimination
//Finds rank r of a linear system consisting of n equations
//format : (a1*x1+a2*x2+a3*x3 + ... an*xn) % k = 0, where 0 <= ai < k
//number of solution : k^(number of free variable) = k^(n-rank)

#define MOD 1000000007
#define ll long long int
typedef vector<ll> VL;
typedef vector<VL> VVL;

ll bigmod(ll n,ll r,ll m){
    if(r==0) return 1LL;
    ll ret=bigmod(n,r/2,m);
    ret=(ret*ret)%m;
    if(r%2==1) ret=(ret*n)%m;
    return ret;
}

ll gcdExtended(ll a, ll b, ll& x, ll& y){
    if(a==0) {x=0;y=1;return b;}
    ll x1,y1;
    ll gcd = gcdExtended(b%a,a,x1,y1);

    x = y1 - (b/a)*x1;
    y = x1;
    return gcd;
}

ll modinverse(ll x,ll y) {ll a,b; gcdExtended(x,y,a,b); return a;}

int gauss(VVL &a,ll k){
      int n = a.size(), m = a[0].size(), r=0;
      for(int c=0 ; c<m-1 && r<n ; c ++ ) {
            for(int i=r+1; i<n; i++) if(a[i][c]>a[r][c]) swap(a[i],a[r]);
            if(a[r][c] == 0 ) continue;

            ll s = modinverse(a[r][c],k);
            for(int i=0;i<n;i++) if(i!=r){
                  if(a[i][c] == 0) continue;
                  ll t = (a[i][c]*s)%k;
                  for(int j=0; j<m; j++) {a[i][j]-=t*a[r][j]; a[i][j]%=k; if(a[i][j]<0) a[i][j]+=k;}
            }
            r++;
      }
      return r;
}

vector<int>G[MAX];
int main(){
      int t;
      scanf("%d",&t);

      for(int cs=1;cs<=t;cs++){
            ll n,m,k;
            scanf("%lld %lld %lld",&n,&m,&k);
            for(int i=0;i<m;i++){
                  int a,b;
                  scanf("%d %d",&a,&b);
                  a--,b--;
                  G[a].push_back(b); G[b].push_back(a);
            }

            VVL a(n,VL(n+1,0));
            for(int i=0;i<n;i++){
                  a[i][i]=1;
                  for(int j=0;j<G[i].size();j++) a[i][G[i][j]] = k-1;
                  a[i][n] = 0;
            }
            int r=gauss(a,k);
            printf("Case %d: %lld\n",cs,bigmod(k,n-r,MOD));
            for(int i=0;i<n;i++) G[i].clear();
      }
}
