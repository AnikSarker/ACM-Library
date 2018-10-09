#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fst first
#define snd second
#define mp make_pair
#define sz(C) ((int) (C).size())
#define forn(i, n) for (int i = 0; i < (int) n; ++i)
#define ford(i, n) for (int i = ((int) n) - 1; i >= 0; --i)
#define y1 gftxdtrtfhyjfctrxujkvbhyjice
#define y0 ehfoiuvhefroerferjhfjkehfjke
#define left sdhfsjkshdjkfsdfgkqqweqweh
#define right yytrwtretywretwreytwreytwr
#define next jskdfksdhfjkdsjksdjkgf
#define prev koeuigrihjdkjdfj
#define hash kjfdkljkdhgjdkfhgurehg
#define all(C) begin(C), end(C)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;
typedef vector <ll> vll;
typedef vector <int> vi;
typedef vector <vector <int> > vvi;
typedef vector <pii> vii;
typedef long double ld;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ld EPS = 1e-9;
const int MOD = 998244353;
const int MAXN = 1e6 + 10;
const int A = 26;
const ld PI = acos(-1.0);

void addmod(int& x, int y, int mod) {
  (x += y) >= mod && (x -= mod);
}

int mulmod(int x, int y, int mod) {
  return x * 1ll * y % mod;
}

#define ld double
namespace FFT {
  struct cd {
    ld a, b;

    cd(ld a, ld b) : a(a), b(b) {}

    cd(ld x = 0) : a(x), b(0) {}

    ld real() const {
      return a;
    }

    void operator += (const cd& other) {
      a += other.a;
      b += other.b;
    }

    void operator -= (const cd& other) {
      a -= other.a;
      b -= other.b;
    }

    void operator *= (const cd& other) {
      tie(a, b) = mp(a * other.a - b * other.b, a * other.b + b * other.a);
    }

    friend cd operator * (const cd& x, const cd& y) {
      cd r = x;
      r *= y;
      return r;
    }

    friend cd operator + (const cd& x, const cd& y) {
      cd r = x;
      r += y;
      return r;
    }

    friend cd operator - (const cd& x, const cd& y) {
      cd r = x;
      r -= y;
      return r;
    }

    void operator /= (ld c) {
      a /= c;
      b /= c;
    }
  };

  typedef vector<cd> vcd;

  const int LOG = 15;
  const int N = 1 << LOG;

  int rev[N];
  cd root_[N];

  inline cd root(int k, int n) {
    return root_[k * (N / n)];
  }

  void precalc() {
    rev[0] = 0;
    int hb = -1;
    for (int i = 1; i < N; ++i) {
      if  ((i & (i - 1)) == 0) {
        ++hb;
      }
      rev[i] = rev[i ^ (1 << hb)] | (1 << (LOG - hb - 1));
    }

    forn(i, N) {
      ld ang = PI * i * 2.0 / N;
      root_[i] = cd(cosl(ang), sinl(ang));
    }
  }

  void fft_rec(cd* a, int n) {
    if  (n == 1) {
      return;
    }

    fft_rec(a, n / 2);
    fft_rec(a + n / 2, n / 2);

    forn(k, n / 2) {
      cd w = root(k, n);
      cd x = a[k];
      cd y = w * a[k + n / 2];
      a[k] = x + y;
      a[k + n / 2] = x - y;
    }
  }

  void fft(vcd& a) {
    int n = sz(a);
    vcd na(n, cd(0, 0));
    forn(i, n) na[i] = a[rev[i]];
    na.swap(a);

    fft_rec(&a[0], n);
  }

  void fft_inv(vcd& a) {
    fft(a);
    int n = sz(a);
    reverse(a.begin() + 1, a.end());
    forn(i, n) {
      a[i] /= n;
    }
  }

  vi mult(const vi& a, const vi& b) {
//    TimeStamp t("mult");
    vcd A(N, cd(0, 0));
    vcd B(N, cd(0, 0));
    forn(i, sz(a)) A[i] = a[i];
    forn(i, sz(b)) B[i] = b[i];

    fft(A);
    fft(B);

    forn(i, N) A[i] *= B[i];

    fft_inv(A);

    vi c(N, 0);
    forn(i, N) c[i] = ((ll) (A[i].real() + 0.5)) % MOD;

    return c;
  }

  vi multmod(const vi& a, const vi& b) {
    // a = a0 + sqrt(MOD) * a1
    // a = a0 + base * a1
    int base = (int) sqrtl(MOD);

    vi a0(sz(a)), a1(sz(a));
    forn(i, sz(a)) {
      a0[i] = a[i] % base;
      a1[i] = a[i] / base;
      assert(a[i] == a0[i] + base * a1[i]);
    }

    vi b0(sz(b)), b1(sz(b));
    forn(i, sz(b)) {
      b0[i] = b[i] % base;
      b1[i] = b[i] / base;
      assert(b[i] == b0[i] + base * b1[i]);
    }

    vi a01 = a0;
    forn(i, sz(a)) {
      addmod(a01[i], a1[i], MOD);
    }

    vi b01 = b0;
    forn(i, sz(b)) {
      addmod(b01[i], b1[i], MOD);
    }

    vi C = mult(a01, b01);  // 1

    vi a0b0 = mult(a0, b0); // 2
    vi a1b1 = mult(a1, b1); // 3

    vi mid = C;
    forn(i, N) {
      addmod(mid[i], -a0b0[i] + MOD, MOD);
      addmod(mid[i], -a1b1[i] + MOD, MOD);
    }

    vi res = a0b0;
    forn(i, N) {
      addmod(res[i], mulmod(base, mid[i], MOD), MOD);
    }

    base = mulmod(base, base, MOD);
    forn(i, N) {
      addmod(res[i], mulmod(base, a1b1[i], MOD), MOD);
    }

    return res;
  }
};

int P, M;
int p[MAXN];

void precalc() {
  p[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    p[i] = mulmod(p[i - 1], P, M);
  }
}

vi solve(int n) {
  if  (n == 0) {
    vi cnt(M, 0);
    cnt[0] = 1;
    return cnt;
  }

  if  (n & 1) {
    vi cnt = solve(n - 1);
    vi ncnt(M, 0);
    for (int c = 1; c <= A; ++c) {
      forn(h, sz(cnt)) {
        int new_h = h;
        addmod(new_h, mulmod(c, p[n - 1], M), M);
        addmod(ncnt[new_h], cnt[h], MOD);
      }
    }
    return ncnt;
  }

  vi cnt1 = solve(n / 2);
  vi cnt2(M, 0);
  forn(h, sz(cnt1)) {
    int new_h = mulmod(h, p[n / 2], M);
    addmod(cnt2[new_h], cnt1[h], MOD);
  }

  vi cnt = FFT::multmod(cnt1, cnt2);
  vi ans(M, 0);
  forn(h, sz(cnt)) {
    addmod(ans[h % M], cnt[h], MOD);
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
#endif

  int n, x;
  cin >> n >> M >> P >> x;

  precalc();
  FFT::precalc();

  printf("%d\n", solve(n)[x]);
  return 0;
}
