/**
 * Description: computes a set of maximum size which is independent 
 	* in both graphic and colorful matroids, aka a spanning forest where
 	* no two edges are of the same color
 * Time: $O(GI^{1.5})$ calls to oracles, where $G$ is the size of the ground set 
 	* and $I$ is the size of the independent set
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/combinatorial%20(11.2)/MatroidIntersect.h
 * Verification: https://www.urionlinejudge.com.br/judge/en/problems/view/2128
 * Verification: https://www.spoj.com/problems/COIN/
 */
int cs, N, M, R;
const int maxn = 307;
const int maxm = 307;
const int maxc = 307;
typedef pair<int,int> pi;
typedef vector<int> vi;
#define F0R(i,j) for(int i = 0; i < j ; i++) 
#define sz(x) x.size()
#define f first
#define s second
#define trav(u,x) for(auto& u : x)
#define MOD 1e9+7
#define pb push_back
struct DSU {
	vi e; void init(int n) { e = vi(n,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	bool unite(int x, int y) { // union-by-rank
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x;
		return 1;
	}
};
map<int,int> m;
struct Element {
	pi ed; int col;
	bool in_independent_set = 0;
	int independent_set_position;
	Element(int u, int v, int c) { ed = {u,v}; col = c; }
};
vi independent_set; vector<Element> ground_set; bool col_used[maxc];
struct GBasis {
	DSU D;
	void reset() { D.init(sz(m)); } 
	void add(pi v) { assert(D.unite(v.f,v.s)); }
	bool independent_with(pi v) { return !D.sameSet(v.f,v.s); }
};
GBasis basis, basis_wo[maxm];
bool graph_oracle(int inserted) { return basis.independent_with(ground_set[inserted].ed); }
bool graph_oracle(int inserted, int removed) {
	int wi = ground_set[removed].independent_set_position;
	return basis_wo[wi].independent_with(ground_set[inserted].ed);
}
void prepare_graph_oracle() {
	basis.reset();
	F0R(i,sz(independent_set)) basis_wo[i].reset();
	F0R(i,sz(independent_set)) {
		pi v = ground_set[independent_set[i]].ed; basis.add(v);
		F0R(j,sz(independent_set)) if (i != j) basis_wo[j].add(v);
	}
}
bool colorful_oracle(int ins) { ins = ground_set[ins].col; return !col_used[ins]; }
bool colorful_oracle(int ins, int rem) {
	ins = ground_set[ins].col;
	rem = ground_set[rem].col;
	return !col_used[ins] || ins == rem;
}
void prepare_colorful_oracle() {
	F0R(i,R) col_used[i] = 0; 
	trav(t,independent_set) col_used[ground_set[t].col] = 1;
}
bool augment() {
	prepare_graph_oracle(); prepare_colorful_oracle();
	vi par(sz(ground_set),MOD);  queue<int> q;
	F0R(i,sz(ground_set)) if (colorful_oracle(i)) {
		assert(!ground_set[i].in_independent_set);
		par[i] = -1; q.push(i);
	}
	int lst = -1;
	while (sz(q)) {
		int cur = q.front(); q.pop();
		if (ground_set[cur].in_independent_set) {
			F0R(to,sz(ground_set)) if (par[to] == MOD) {
				if (!colorful_oracle(to,cur)) continue;
				par[to] = cur; q.push(to);
			}
		} else {
			if (graph_oracle(cur)) { lst = cur; break;	}
			trav(to,independent_set) if (par[to] == MOD) {
				if (!graph_oracle(cur,to)) continue;
				par[to] = cur; q.push(to);
			}
		}
	}
	if (lst == -1) return 0;
	do {
		ground_set[lst].in_independent_set ^= 1;
		lst = par[lst];
	} while (lst != -1);
	independent_set.clear();
	F0R(i,sz(ground_set)) if (ground_set[i].in_independent_set) {
		ground_set[i].independent_set_position = sz(independent_set);
		independent_set.pb(i);
	}
	return 1;
}
void solve() {
    cs++;
    m.clear(); ground_set.clear(); independent_set.clear();
    F0R(i,M) {
		int a, b, c; cin >> a >> b >> c; c--;
		ground_set.pb(Element(a,b,c)); m[a] = m[b] = 0;
    }
    int co = 0; trav(t,m) t.s = co++;
    trav(t,ground_set) t.ed.f = m[t.ed.f], t.ed.s = m[t.ed.s]; 
    while(augment()); //// keep increasing size of independent set
    //Matroid Intersection is stored in Independent Set
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    while( cin >> N >> M >> R ) solve();
}
