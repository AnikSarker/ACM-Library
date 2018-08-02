///Taken from Rezwan Arefin
const int maxn = 1e5 + 10;
int n, m, a[maxn], prv[maxn], ans[maxn], block;

struct query {
	int l, r, id, t, blcl, blcr; 
	query(int _a, int _b, int _c, int _d) {
		l = _a, r = _b; 
		id = _c, t = _d;
		blcl = l / block;
		blcr = r / block;
	}
	bool operator < (const query &p) const {
		if(blcl != p.blcl) return l < p.l; 
		if(blcr != p.blcr) return r < p.r; 
		return t < p.t;
	}
}; vector<query> q; 

struct update {
	int pos, pre, now; 
}; vector<update> u;


struct lol {
	void add(int x) {} 
	void remove(int x) {}
	int get() {}
} ds;

int l, r, t; 
int cnt[maxn * 2];

void add(int x) { // Add a[x] to ds
}
void remove(int x) { // Remove a[x] from ds
}
void apply(int i, int x) { // Change a[i] to x 
	if(l <= i && i <= r) {
		remove(i);
		a[i] = x;
		add(i); 
	} else a[i] = x;
}

int main(int argc, char const *argv[]) {
	read(n); read(m);
	block = pow(n, 0.6667);

	for(int i = 0; i < n; ++i) 
		read(a[i]), last[i] = a[i];

	u.push_back({-1, -1, -1});

	for(int i = 0; i < m; ++i) {
		int t, l, r; 
		read(t); read(l); read(r); 
		if(t == 1) { --r;
			q.push_back(query(l, r, q.size(), u.size() - 1));
		} else {
			u.push_back({l, prv[l], r});
			prv[l] = r;
		}
	} 

	sort(q.begin(), q.end()); 
	l = 0, r = -1, t = 0;

	for(int i = 0; i < q.size(); i++) {
		while(t < q[i].t) ++t, apply(u[t].pos, u[t].now); 
		while(t > q[i].t) apply(u[t].pos, u[t].pre), --t;

		while(r < q[i].r) add(++r);
		while(l > q[i].l) add(--l);
		while(r > q[i].r) remove(r--);
		while(l < q[i].l) remove(l++);

		ans[q[i].id] = ds.get(); 
	}

	for(int i = 0; i < q.size(); i++) 
		printf("%d\n", ans[i]);
}
