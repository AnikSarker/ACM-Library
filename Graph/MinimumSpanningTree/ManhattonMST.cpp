struct point {
  int x, y, index;
  bool operator<(const point &p) const { return x == p.x ? y < p.y : x < p.x; }
} p[maxN];
struct node {
  int value, p;
} T[maxN];

int query(int x) {
  int r = maxint, p = -1;
  for (; x <= n; x += (x & -x)) if (T[x].value < r) r = T[x].value, p = T[x].p;
  return p;
}

void modify(int x, int w, int p) {
  for (; x > 0; x -= (x & -x)) if (T[x].value > w) T[x].value = w, T[x].p = p;
}

// impl add & kruskal
int manhattan() {
  for (int i = 1; i <= n; ++i) p[i].index = i;
  for (int dir = 1; dir <= 4; ++dir) {
    if (dir == 2 || dir == 4) {
      for (int i = 1; i <= n; ++i) swap(p[i].x, p[i].y);
    } else if (dir == 3) {
      for (int i = 1; i <= n; ++i) p[i].x = -p[i].x;
    }
    sort(p + 1, p + 1 + n);
    vector<int> v; static int a[maxN];
    for (int i = 1; i <= n; ++i) a[i] = p[i].y - p[i].x, v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    for (int i = 1; i <= n; ++i) T[i].value = maxint, T[i].p = -1;
    for (int i = n; i >= 1; --i) {
      int pos = query(a[i]);
      if (pos != -1) add(p[i].index, p[pos].index, dist(p[i], p[pos]));
      modify(a[i], p[i].x + p[i].y, i);
    }
  }
  return kruskal();
}
