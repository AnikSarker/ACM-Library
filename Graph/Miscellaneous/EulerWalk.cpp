/*
 Eulerian undirected/directed path/cycle algorithm.Returns a list of nodes
 in the Eulerian path/cycle with src at both start and end, or
 empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 Time: O(E) where E is the number of edges.
 */
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
#define sz(x) (int)x.size()
struct V {
	vector<pii> outs; // (dest, edge index)
	int nins = 0;
	void clr(){nins=0;outs.clear();}
};
#define ff first
#define ss second
vpi euler_walk(vector<V>& nodes, int nedges, int src=0) {
	int c = 0;
	for(auto &n:nodes)c += abs(n.nins - sz(n.outs));
	if (c > 2) return {};
	vector<vector<pii>::iterator> its;
	for(auto &n:nodes)
		its.push_back(n.outs.begin());
	vector<bool> eu(nedges+7);
	vpi ret, s = {{src,0}};
	while(!s.empty()) {
		auto x = s.back();
		auto& it = its[x.ff], end = nodes[x.ff].outs.end();
		while(it != end && eu[it->second]) ++it;
		if(it == end) { ret.push_back(x); s.pop_back(); }
		else { s.push_back(*it); eu[it->second] = true; }
	}
	if(sz(ret) != nedges+1)
		ret.clear(); // No Eulerian cycles/paths.
	// else, non-cycle if ret.front() != ret.back()
	reverse(ret.begin(),ret.end());
	return ret;
}
vector<V>nodes(maxn);
