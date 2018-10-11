//CompressTree , 0-rooted with specific nodes
vpi compressTree(LCA& lca, const vector<int>& subset) {
	vector<int> rev;
  rev.resize(lca.dist.size());
  vector<int> li = subset,&T = lca.time;
	auto cmp = [&](int a, int b){return T[a] < T[b]; };
  sort(li.begin(),li.end(), cmp);
	int m = li.size()-1;
	for(int i=0;i<m;i++) {
		int a = li[i], b = li[i+1];
    li.push_back(lca.query(a, b));
	}
	sort(li.begin(),li.end(), cmp);
  li.erase(unique(li.begin(),li.end()), li.end());
	for(int i=0;i<li.size();i++)rev[li[i]] = i;
  vpi ret = {pair<int,int>(0, li[0])};
	for(int i=0;i<li.size()-1;i++) {
		int a = li[i], b = li[i+1];
    ret.emplace_back(rev[lca.query(a, b)],b);
	}
	return ret;
}
