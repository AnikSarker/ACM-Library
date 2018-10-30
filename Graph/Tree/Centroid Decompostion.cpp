// p[u] = parent of u in centroid tree
// d[x][u] = distance from u to a parent of u at level x of centroid tree
//           if u is in subtree of centroid c, then d[lvl[c]][u] = dist(c, l)
// Taken from Rezwan Arefin
// If (x, y) edge exist, then x must be in adj[y] and y must be in adj[x]
const int maxn = 1e5 + 10; 
vector<int> adj[maxn]; 
int lvl[maxn], sub[maxn], p[maxn], vis[maxn], d[18][maxn], ans[maxn];
	
void calc(int u, int par) { sub[u] = 1; 
	for(int v : adj[u]) if(v - par && !vis[v]) 
		calc(v, u), sub[u] += sub[v];
}
int centroid(int u, int par, int r) {
	for(int v : adj[u]) if(v - par && !vis[v]) 
		if(sub[v] > r) return centroid(v, u, r);
	return u;
}
void dfs(int l, int u, int par) {
	if(par + 1) d[l][u] = d[l][par] + 1; 
	for(int v : adj[u]) if(v - par && !vis[v]) 
		dfs(l, v, u);
}
void decompose(int u, int par) {
	calc(u, -1);
	int c = centroid(u, -1, sub[u] >> 1);
	vis[c] = 1, p[c] = par, lvl[c] = 0; 
	if(par + 1) lvl[c] = lvl[par] + 1;
	dfs(lvl[c], c, -1);
	for(int v : adj[c]) if(v - par && !vis[v]) 
		decompose(v, c);
}

void update(int u) {
	for(int v = u; v + 1; v = p[v]) 
		ans[v] = min(ans[v], d[lvl[v]][u]);
}
int query(int u) {
	int ret = 1e9;
	for(int v = u; v + 1; v = p[v])
		ret = min(ret, ans[v] + d[lvl[v]][u]);
	return ret;
}
