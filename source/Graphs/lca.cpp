const int MAXN = 1e5;
const int LOG = 20;
int euler_size = 0;

vector<int> g[MAXN];
vector<int> euler;
int d[MAXN], first[MAXN];
pair<int,int> sp[LOG][2*MAXN];

void dfs(int v, int p = -1) {
	if (p == -1) {
		d[v] = 0;
		first[v] = euler_size++;
		euler.push_back(v);
	}
	else
		d[v] = d[p] + 1;
	
	for (auto to : g[v]) {
		if (to == p)
			continue;
		first[to] = euler_size++;
		euler.push_back(to);
		dfs(to, v);
		euler.push_back(v); euler_size++;
	}
}

void build_sp() {
	int n = euler.size();
	for (int i = 0; i < n; i++)
		sp[0][i] = {d[euler[i]], euler[i]};
	
	for (int l = 0; l < LOG - 1; l++)
		for (int i = 0; i + (1 << l) < n; i++)
			sp[l+1][i] = min(sp[l][i], sp[l][i + (1 << l)]);
}

int lca(int v, int u) {
	int l = min(first[v], first[u]);
	int r = max(first[v], first[u]) + 1;
	int t = __lg(r - l);
	return min(sp[t][l], sp[t][r - (1 << t)]).second;
}
