#define ll long long int

struct Point{
    ll x; ll y; ll val;
    bool operator < (const Point& other) const {
        if(x * other.x > 0) return y*other.x < x*other.y;
        else return y*other.x > x*other.y;
    }
};
Point p[MAX];

int main(){
    int n;
    scanf("%d",&n);

    ll Plus=0, Minus=0;
    for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y>>p[i].val;
    
    //Precalculate w.r.t. Y-axis
    for(int i=1;i<=n;i++){
        if(p[i].x>=0) Plus+=p[i].val;
        else Minus+=p[i].val;
    }
    sort(p+1,p+n+1);
    
    //Calculate w.r.t. all slopes
    for(int i=1;i<=n;i++){
        if(p[i].x>=0) Plus-=p[i].val, Minus+=p[i].val;
        else Minus-=p[i].val, Plus+=p[i].val;
    }
}
