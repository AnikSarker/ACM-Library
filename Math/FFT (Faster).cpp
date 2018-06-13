//Fast FFT
//Complex Class Hard Coded

#define op operator
typedef long double ld;
struct base {
   typedef double T; T re, im;
   base() :re(0), im(0) {}
   base(T re) :re(re), im(0) {}
   base(T re, T im) :re(re), im(im) {}
   base op + (const base& o) const { return base(re + o.re, im + o.im); }
   base op - (const base& o) const { return base(re - o.re, im - o.im); }
   base op * (const base& o) const { return base(re * o.re - im * o.im, re * o.im + im * o.re); }
   base op * (ld k) const { return base(re * k, im * k) ;}
   base conj() const { return base(re, -im); }
};

const int N = 21;
const int MAXN = (1<<N);
base w[MAXN];
base f1[MAXN];
int rev[MAXN];
void build_rev(int k) {
   static int rk = -1;
   if( k == rk )return ; rk = k;
   for(int i=1;i<=(1<<k);i++) {
       int j = rev[i-1], t = k-1;
       while( t >= 0 && ((j>>t)&1) ) { j ^= 1 << t; --t; }
       if( t >= 0 ) { j ^= 1 << t; --t; }
       rev[i] = j;
   }
}
void fft(base *a, int k) {
   build_rev(k); int n = 1 << k;
   for(int i=0;i<n;i++) if( rev[i] > i ) swap(a[i], a[rev[i]]);
   for(int l = 2, ll = 1; l <= n; l += l, ll += ll) {
       if( w[ll].re == 0 && w[ll].im == 0 ) {
           ld angle = M_PI / ll;
           base ww( cosl(angle), sinl(angle) );
           if( ll > 1 ) for(int j = 0; j < ll; ++j) {
               if( j & 1 ) w[ll + j] = w[(ll+j)/2] * ww;
               else w[ll + j] = w[(ll+j)/2];
           } else w[ll] = base(1, 0);
       }
       for(int i = 0; i < n; i += l){
           for(int j=0;j<ll;j++){
               base v = a[i + j], u = a[i + j + ll] * w[ll + j];
               a[i + j] = v + u; a[i + j + ll] = v - u;
           }
       }
   }
}
void Multiply() {
   int k = 1;
   while( (1<<k) < (a.size() + b.size()) ) ++k;
   int n = (1<<k);

   for(int i=0;i<n;i++) f1[i] = base(0,0);
   for(int i=0;i<a.size();i++) f1[i] = f1[i] + base(a[i], 0);
   for(int i=0;i<b.size();i++) f1[i] = f1[i] + base(0, b[i]);

   fft(f1, k);
   for(int i=0;i<1+n/2;i++) {
       base p = f1[i] + f1[(n-i)%n].conj();
       base _q = f1[(n-i)%n] - f1[i].conj();
       base q(_q.im, _q.re);
       f1[i] = (p * q) * 0.25;
       if( i > 0 ) f1[(n - i)] = f1[i].conj();
   }
   for(int i=0;i<n;i++) f1[i] = f1[i].conj();
   fft(f1, k);
   res.resize(a.size() + b.size());

   for(int i=0;i<res.size();i++) {
       res[i] = int (f1[i].re / n + 0.5);
   }
}
