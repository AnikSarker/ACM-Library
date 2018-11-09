//Slow, but short FFT
//Using STL Complex Class

typedef vector<int> VI;
typedef complex<double> CN;

const double PI = acos(-1);
const double eps = 1e-6;

void FFT(vector<CN>&a,bool invert){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j>=bit;bit>>=1) j-=bit ;
        j+=bit ;
        if(i<j) swap(a[i],a[j]);
    }

    for(int len=2;len<=n;len<<=1){
        double ang=2*PI/len*(invert ? -1:1);
        CN wlen(cos(ang),sin(ang));
        for(int i=0;i<n;i+=len){
            CN w(1) ;
            for(int j=0;j<len/2;j++){
                CN u=a[i+j],v=a[i+j+len/2]*w;
                a[i+j]=u+v;
                a[i+j+len/2]=u-v;
                w*=wlen;
            }
        }
    }
    if(invert) for(int i=0;i<n;i++) a[i]/=n;

}

inline ll Round(double x){
    if(abs(x)<eps) return 0;
    else return (x/abs(x)) * (ll)(abs(x)+0.5);
}
 
void multiply ( vector<ll> & a, vector<ll> & b, vector<ll> & res) {
    ll sq=sqrt(MOD);
    int n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
 
    vector<CN> a1(n),a2(n),b1(n),b2(n);
 
    a.resize(n);
    b.resize(n);
    for(int i=0;i<n;i++){
        a1[i]=a[i]/sq; a2[i]=a[i]%sq;
        b1[i]=b[i]/sq; b2[i]=b[i]%sq;
    }
 
    FFT(a1, false),  FFT(a2, false);
    FFT(b1, false),  FFT(b2, false);
    vector<CN>c1(n),c2(n),c3(n);
 
    for(int i=0;i<n;i++){
        c1[i] = a1[i]*b1[i];
        c2[i] = a1[i]*b2[i]+b1[i]*a2[i];
        c3[i] = a2[i]*b2[i];
    }
 
    FFT(c1,true);
    FFT(c2,true);
    FFT(c3,true);
    res.resize(n);
 
    for(int i=0; i<n; ++i){
        res[i] = ( (sq*sq) %MOD * (Round(c1[i].real()) % MOD) ) %MOD
                  + ( sq * (Round(c2[i].real()) % MOD) ) %MOD
                  + ( Round(c3[i].real()) %MOD );
        res[i] %=  MOD;
    }
}
