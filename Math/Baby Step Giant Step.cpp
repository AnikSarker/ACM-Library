//Shanks Baby-Step Giant-Step (Faster)
//a^x = b (mod m)
#define ll long long int
ll egcd(ll a,ll b,ll &x,ll &y){
    if(b==0) {x=1; y=0; return a;}
    ll g=egcd(b,a%b,y,x);
    y-=a/b*x;
    return g;
}

ll InvMod(ll a,ll m){
    ll x,y;
    if(egcd(a,m,x,y)==1) return (x+m)%m;
    return -1;
}

const int SQRT_MOD_MAX=30000;
struct hash_table{
    ll a[SQRT_MOD_MAX];
    int j[SQRT_MOD_MAX];

    void init() {for(int i=0;i<SQRT_MOD_MAX;i++) a[i]=-1;}

    void Insert(ll aa,int jj){
        int i=aa%SQRT_MOD_MAX;
        while(a[i]!=-1 && a[i]!=aa) i=(i+1)%SQRT_MOD_MAX;
        if(a[i]==-1){
            a[i]=aa;
            j[i]=jj;
        }
    }

    int Find(ll aa){
        int i=aa%SQRT_MOD_MAX;
        while(a[i]!=-1 && a[i]!=aa) i=(i+1)%SQRT_MOD_MAX;
        return a[i]==aa?j[i]:-1;
    }
};

ll baby_step_giant_step(ll a,ll b,ll m){
    int k=(int)sqrt(m)+1;
    static hash_table H; H.init();

    //Baby step
    ll aa=1;
    for(int j=0;j<k;j++) H.Insert(aa,j), aa=aa*a%m;

    //Giant step
    aa=InvMod(aa,m);
    for(int i=0;i<m;i++){
        int j=H.Find(b);
        if(j!=-1) return i*k+j;
        b=b*aa%m;
    }
    return -1;
}
