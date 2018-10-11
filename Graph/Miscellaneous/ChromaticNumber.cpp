//complexity n*2^n
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define TEST(s) if (!(s)) { cout << __LINE__ << " " << #s << endl; exit(-1); }

struct Graph {
  int n;
  vector<vector<int>> adj;
  Graph(int n) : n(n), adj(n) { }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
};

int chromaticNumber(Graph g) {
  const int N = 1 << g.n;
  vector<int> nbh(g.n);
  for (int u = 0; u < g.n; ++u) 
    for (int v: g.adj[u]) 
      nbh[u] |= (1 << v);

  int ans = g.n;
  for (int d: {7}) { // ,11,21,33,87,93}) { 
    long long mod = 1e9 + d;
    vector<long long> ind(N), aux(N, 1); 
    ind[0] = 1;
    for (int S = 1; S < N; ++S) {
      int u = __builtin_ctz(S);
      ind[S] = ind[S^(1<<u)] + ind[(S^(1<<u))&~nbh[u]];
    }
    for (int k = 1; k < ans; ++k) {
      long long chi = 0; 
      for (int i = 0; i < N; ++i) {
        int S = i ^ (i >> 1); // gray-code
        aux[S] = (aux[S] * ind[S]) % mod;
        chi += (i & 1) ? aux[S] : -aux[S];
      }
      if (chi % mod) ans = k; 
    }
  }
  return ans;
}
