typedef long long ll;
#define MAX 105
#define maxM 107
#define maxN 107
const ll inf = 1e12+7;
template<typename T>
struct KuhnMunkras { // n for left, m for right
  int n, m, match[maxM];
  T g[maxN][maxM], lx[maxN], ly[maxM], slack[maxM];
  bool vx[maxN], vy[maxM];
  void init(int n_, int m_) {
     n = n_, m = m_;
     for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            g[i][j]=-inf;
  }
  void add(int u, int v, T w) {
    g[u][v] = w;
  }
  bool find(int x) {
    vx[x] = true;
    for (int y = 1; y <= m; ++y) {
      if (!vy[y]) {
        T delta = lx[x] + ly[y] - g[x][y];
        if (delta== T(0)) {
          vy[y] = true;
          if (match[y] == 0 || find(match[y])) {
            match[y] = x;
            return true;
          }
        } else slack[y] = min(slack[y], delta);
      }
    }
    return false;
  }
  pair<T,T> matching() { // maximum weight matching
    fill(lx + 1, lx + 1 + n, 0);
    memset(ly,0,sizeof(ly)); memset(match,0,sizeof(match));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) lx[i] = max(lx[i], g[i][j]);
    }
    for (int k = 1; k <= n; ++k) {
      fill(slack + 1, slack + 1 + m, numeric_limits<T>::max());
      while (true) {
        memset(vx,0,sizeof(vx)); memset(vy,0,sizeof(vy));
        if (find(k)) break;
        else {
          T delta = numeric_limits<T>::max();
          for (int i = 1; i <= m; ++i) {
            if (!vy[i]) delta = min(delta, slack[i]);
          }
          for (int i = 1; i <= n; ++i) {
            if (vx[i]) lx[i] -= delta;
          }
          for (int i = 1; i <= m; ++i) {
            if (vy[i]) ly[i] += delta;
            if (!vy[i]) slack[i] -= delta;
          }
        }
      }
    }
    T resultCost = 0;
    T resultMatch = 0;
    for (int i = 1; i <= n; ++i) resultCost += lx[i];
    for (int i = 1; i <= m; ++i) resultCost += ly[i];
    for (int i = 1; i <= m; i++){
        if(g[match[i]][i]>-inf)
            resultMatch++;
        else resultCost+=inf;
    }
    return {resultCost,resultMatch};
  }
};
