void add_edge(int a, int b) { 
	edge e1 = { b, u[a][b], c[a][b], 0, r[b].size() };
	edge e2 = { a, 0, -c[a][b], 0, r[a].size() };
	r[a].push_back(e1);
	r[b].push_back(e2);
}

int main() {  
	// ...
	int flow = 0;
	int cost = 0;
	k = INF;
	while (flow < k) {
		vector<int> id( n+1 , 0);
		vector<int> d(n+1, inf);
		deque <int> q;
		vector<int> p(n+1);
		vector<int> p_e(n+1);
		d[s] = 0;
		q.push_back(s);
		
		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			id[v] = 2;
			for(int i = 0 ; i < r[v].size(); i++) {
				edge &e = r[v][i];
				if(e.f < e.u && d[v] + e.c < d[e.b]) {
					d[e.b] = d[v] + e.c;
					if(!id[e.b])
						q.push_back(e.b);
					else 
					if(id[e.b] == 2)
						q.push_front(e.b);
				id[e.b] = 1;
				p[e.b] = v;
				p_e[e.b] = i;
				}
			}
		}
		
		if(d[t] == INF)
			break;
		
		int addflow = k - flow;
		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];
			int pr = p_e[v];
			addflow = min(addflow, r[pv][pr].u - r[pv][pr].f);
		}

		for (int v = t; v != s; v = p[v]) {
			int pv = p[v];
			int pr = p_e[v];
			int e = r[pv][pr].back;
			r[pv][pr].f += addflow;
			r[v][e].f -= addflow;
			cost += r[pv][pr].c * addflow;
		}

		flow += addflow;
	}
}
