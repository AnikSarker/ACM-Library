const int maxn = 1e5+10;
const int MAX = 127;
int len[maxn << 1], link[maxn << 1], sz, last;
int adj[maxn << 1][MAX];

void init() {
	sz = last = 0; 
	len[0] = 0; link[0] = -1;
	memset(adj, -1, sizeof adj); 
	sz++;
}
void extend(int c) { 
	int cur = sz++, p; 
	len[cur] = len[last] + 1; 
	for(p = last; p != -1 && adj[p][c] == -1; p = link[p]) 
		adj[p][c] = cur;
	last = cur; 
	if(p == -1) return void(link[cur] = 0);

	int q = adj[p][c]; 
	if(len[q] == len[p] + 1) return void(link[cur] = q);

	int clone = sz++;
	len[clone] = len[p] + 1; 
	link[clone] = link[q];

	for(int i = 0; i < MAX; i++) 
		adj[clone][i] = adj[q][i];
	for(; p != -1 && adj[p][c] == q; p = link[p]) 
		adj[p][c] = clone;
	link[q] = link[cur] = clone; 
} 
