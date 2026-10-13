void dfs1(int v) {
	used[v] = true;
	for (int i = 0; i<g[v].size(); i++) {
		int id = g[v][i],
			to = e[id].b;
		if (!used[to] && e[id].flow < e[id].cap)
			dfs1(to);
	}
}

int main(){
	// ..finding max flow..

	dfs1(s);
	for (int i = 0; i < e.size(); i += 2) {
		if (used[e[i].a] && !used[e[i].b]) {
			ans.push_back(make_pair(e[i].a, e[i].b));
			anss += e[i].flow;
		}
	}
}