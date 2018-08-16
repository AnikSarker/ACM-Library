//Slow, but short FFT
//Using STL Complex Class

typedef vector<int> VI;
typedef complex<double> CN;
VI a,b,res;

double PI=acos(-1);
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

void Multiply(){
    vector<CN>fa(a.begin(),a.end());
    vector<CN>fb(b.begin(),b.end());
    int n=1;
    while(n<max(a.size(),b.size())) n<<=1;
    n<<=1;
    fa.resize(n),fb.resize(n);
    FFT(fa,false),FFT(fb,false);
    for(int i=0;i<n;i++) fa[i]*=fb[i];
    FFT(fa,true);
    res.resize(n);
    for(int i=0;i<n;i++) res[i]=fa[i].real()/abs(fa[i].real())*(int)(abs(fa[i].real())+0.5);
}
