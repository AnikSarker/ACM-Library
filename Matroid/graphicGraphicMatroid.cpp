// courtesy : https://discuss.codechef.com/t/cnnct2-editorial/40191
#include <bits/stdc++.h>
using namespace std;
const int MX = 300;
int n, m;
bool enabled[MX];
struct graph_t {
	int u[MX], v[MX];
	void read();
	vector<int> getNonBridges();
} G1, G2;
void graph_t::read() {
	for (int i = 0; i < m; i++) {
		ignore = scanf("%d %d", u + i, v + i);
		u[i]--;
		v[i]--;
	}
}
vector<int> graph_t::getNonBridges() {
	static vector<pair<int, int>> G[MX];
	for (int i = 0; i < n; i++) G[i].clear();
	for (int i = 0; i < m; i++) {
		if (enabled[i] == false) continue;
		G[u[i]].emplace_back(v[i], i);
		G[v[i]].emplace_back(u[i], i);
	}
	static bool vis[MX];
	static int up[MX], dep[MX];
	fill(vis, vis + n, false);
	vector<int> result;
	function<void(int, int, int)> dfs = [&](int v, int p, int d) {
		vis[v] = true;
		dep[v] = d;
		up[v] = d;
		for (auto& e : G[v]) {
			if (e.second == p) continue;

			if (vis[e.first] == false) {
				dfs(e.first, e.second, d + 1);
				if (up[e.first] <= d) result.push_back(e.second);
			}
			else {
				if (dep[e.first] < d) result.push_back(e.second);
			}

			up[v] = min(up[v], up[e.first]);
		}
	};
	dfs(0, -1, 0);
	return result;
}
namespace ExchangeGraph {
	vector<int> G[MX];
	void clear() { for (int i = 0; i < m; i++) G[i].clear(); }
	void addEdge(int u, int v) { G[u].push_back(v); }
	bool findAugmentalPath(vector<int> from, vector<int> to) {
		vector<int> par(m, -1), dist(m), queue;
		for (int v : from) {
			queue.push_back(v); par[v] = -2; dist[v] = 0;
		}
		for (size_t i = 0; i < queue.size(); i++) {
			int v = queue[i];
			for (int u : G[v]) {
				if (par[u] == -1) {
					queue.push_back(u);	par[u] = v; dist[u] = dist[v] + 1;
				}
			}
		}
		int target = -1;
		for (int v : to) {
			if (par[v] == -1) continue;
			if (target == -1 || dist[v] < dist[target]) target = v;
		}
		if (target != -1) {
			while (target != -2) {
				enabled[target] = not enabled[target];	target = par[target];
			}
			return true;
		}
		return false;
	}
}
int main() {
	int T;
	ignore = scanf("%d", &T);
	while (T--) {
		ignore = scanf("%d %d", &n, &m);
		G1.read();
		G2.read();
		fill(enabled, enabled + m, true);
		int ans = m;
		while (true) {
			ExchangeGraph::clear();
			auto Y1 = G1.getNonBridges();
			auto Y2 = G2.getNonBridges();
			if (ExchangeGraph::findAugmentalPath(Y1, Y2)) { ans--; continue; }
			for (int e = 0; e < m; e++) {
				if (enabled[e]) continue;
				enabled[e] = true;
				auto edgesTo = G1.getNonBridges();
				auto edgesFrom = G2.getNonBridges();
				enabled[e] = false;
				for (int v : edgesTo) ExchangeGraph::addEdge(e, v);
				for (int v : edgesFrom) ExchangeGraph::addEdge(v, e);
			}
			if (ExchangeGraph::findAugmentalPath(Y1, Y2)) { ans--; }
			else { break; }
		}
		printf("%d\n", ans);
	}
	return 0;
}
