const int MAX = 808;
vector<int>g[MAX];
int work[MAX], lv[MAX], cap[MAX][MAX], flow[MAX][MAX];

struct Dinic {
	void add(int u, int v, int c) {
		g[u].push_back(v);
		g[v].push_back(u);
		cap[u][v] += c;
	}
	bool bfs(int S, int T) {
		memset(lv, -1, sizeof(lv));
		queue<int>q;
		lv[S] = 0;
		q.push(S);
		while (q.size()) {
			int cur = q.front(); q.pop();
			for (int nxt : g[cur]) {
				if (lv[nxt] == -1 && cap[cur][nxt] > flow[cur][nxt]) {
					lv[nxt] = lv[cur] + 1;
					q.push(nxt);
				}
			}
		}
		return ~lv[T];
	}
	int dfs(int cur, int w, int T) {
		if (cur == T) return w;
		for (int& i = work[cur]; i < g[cur].size(); i++) {
			int nxt = g[cur][i];
			if (lv[nxt] == lv[cur] + 1 && cap[cur][nxt] > flow[cur][nxt]) {
				int f = dfs(nxt, min(w, cap[cur][nxt] - flow[cur][nxt]), T);
				if (f) {
					flow[cur][nxt] += f;
					flow[nxt][cur] -= f;
					return f;
				}
			}
		}
		return 0;
	}
	int max_flow(int S, int T) {
		int ret = 0;
		while (bfs(S, T)) {
			memset(work, 0, sizeof(work));
			while (1) {
				int f = dfs(S, 1e9, T);
				if (!f) break;
				ret += f;
			}
		}
		return ret;
	}
}dinic;