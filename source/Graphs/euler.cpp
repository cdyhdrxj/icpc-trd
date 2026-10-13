int n; // number of vertices
int m; // number of edges

vector<vector<pair<int,int>> g(n); // edge: {index, to}
vector<int> vis(m, 0);
vector<int> first(n, 0);
vector<int> path;

void euler(int v)
{
	int len = g[v].size();
	while (first[v] < len) {
		auto [i, to] = g[v][first[v]];

		first[v]++;

		if (!vis[i]) {
			vis[i] = 1;
			euler(to);
			path.push_back(to);
		}
	}    
}

int main() {
	// ... reading the graph ...

	int start; // start vertex
	euler(start);

	path.push_back(start);
	reverse(path.begin(), path.end());
}