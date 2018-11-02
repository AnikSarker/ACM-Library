const ll mod = 786433;

struct NTT{
    vector<ll>A,B;
    vector<ll> w[2],rev;
    ll P,M,G;

    NTT(ll mod) {P = mod; G = 10;}
    ll Pow(ll a, ll b){
        ll res=1;
        for(;b; b>>=1,a=(a*a)%P) if (b&1) res=(res*a)%P;
        return res;
    }

    void init(ll n){
        for(M=2; M<n; M<<=1);
        M<<=1;
        A.resize(M); B.resize(M);
        w[0].resize(M); w[1].resize(M); rev.resize(M);
        for (ll i=0; i<M; i++){
            ll x=i, &y=rev[i];
            y=0;
            for(ll k=1; k<M; k<<=1,x>>=1) (y<<=1)|=x&1;
        }
        ll x=Pow(G,(P-1)/M),y=Pow(x,P-2);
        w[0][0]=w[1][0]=1;
        for (ll i=1; i<M; i++){
            w[0][i]=(w[0][i-1]*x)%P;
            w[1][i]=(w[1][i-1]*y)%P;
        }
    }

    void ntransform(vector<ll> &a,ll f){
        for (ll i=0; i<M; i++)
            if (i<rev[i]) swap(a[i],a[rev[i]]);
        for (ll i=1; i<M; i<<=1)
            for (ll j=0,t=M/(i<<1); j<M; j+=i<<1)
                for (ll k=0,l=0; k<i; k++,l+=t){
                    ll x=a[j+k+i]*1ll*w[f][l]%P;
                    ll y=a[j+k];
                    a[j+k+i] = y-x<0 ? y-x+P : y-x;
                    a[j+k] = y+x>=P ? y+x-P : y+x;
                }
        if (f){
            ll x=Pow(M,P-2);
            for (ll i=0; i<M; i++) a[i]=a[i]*1ll*x%P;
        }
    }

    void multiply( vector<ll> &X, vector<ll> &Y, vector<ll> &res){
        init(max(X.size(), Y.size()));
        for (ll i = 0; i < M; i++) A[i] = B[i] = 0;
        for (ll i = 0; i < X.size(); i++) A[i] = X[i];
        for (ll i = 0; i < Y.size(); i++) B[i] = Y[i];
        ntransform(A,0); ntransform(B,0);
        res.clear(); res.resize(M);
        for (ll i=0; i<M; i++) res[i]=A[i]*1LL*B[i]%P;
        ntransform(res,1);
    }
};
