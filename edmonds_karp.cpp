const int MAX = 808;
vector<int>g[MAX];
cap[MAX][MAX], flow[MAX][MAX];

int max_flow(int S, int T) {
	int tot = 0;
	while (1) {
		int prev[MAX];
		memset(prev, -1, sizeof(prev));
		queue<int>q;
		q.push(S);
		while (q.size()) {
			int cur = q.front(); q.pop();
			for (int nxt : g[cur]) {
				if (prev[nxt] == -1 && cap[cur][nxt] > flow[cur][nxt]) {
					q.push(nxt);
					prev[nxt] = cur;
					if (nxt == T) break;
				}
			}
		}
		if (prev[T] == -1) break;
		int f = 1e9;
		for (int i = T; i != S; i = prev[i]) {
			f = min(f, cap[prev[i]][i] - flow[prev[i]][i]);
		}
		for (int i = T; i != S; i = prev[i]) {
			flow[prev[i]][i] += f;
			flow[i][prev[i]] -= f;
		}
		tot += f;
	}
	return tot;
}
