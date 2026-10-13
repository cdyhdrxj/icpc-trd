int n; // number of vertices
vector<vector<pair<int,int>>> g(n);
vector<vector<int>> mst(n); // minimum spanning tree

vector<int> min_e(n, INF), sel(n, -1);

min_e[0] = 0;
set<pair<int,int>> q;
q.insert({0, 0});

while (!q.empty()) {
	int v = q.begin()->second;
	q.erase(q.begin());

	if (sel[v] != -1) {
		mst[v].pb(sel[v]);
		mst[sel[v]].pb(v);
	}

	for (auto [to, w] : g[v]) {
		if (w < min_e[to]) {
			q.erase({min_e[to], to});
			min_e[to] = w;
			sel[to] = v;
			q.insert({min_e[to], to});
		}
	}
}