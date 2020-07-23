int n, p, start, finish;
int capacity[401][401], flow[401][401];
vector<int> adj[401];

int residual(int a, int b) {
	return capacity[a][b] - flow[a][b];
}

int main() {
	cin.tie(0); cout.tie(0);
	ios_base::sync_with_stdio(false);

	int ans = 0;
	cin >> n >> p;
	start = 1;
	finish = 2;
	while (p--) {
		int a, b;
		cin >> a >> b;
		capacity[a][b] = 1;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	while (1) {
		vector<int> prev(401, -1);
		queue<int> q;
		q.push(start);
		while (!q.empty()) {
			int now = q.front(); q.pop();
			if (now == finish)
				break;
			for (int next : adj[now]) {
				if (prev[next] != -1 || residual(now, next) <= 0)
					continue;
				prev[next] = now;
				q.push(next);
			}
		}
		if (prev[finish] == -1)
			break;
		int tmp = 1e9;
		for (int i = finish; i != start; i = prev[i])
			tmp = min(tmp, residual(prev[i], i));
		for (int i = finish; i != start; i = prev[i]) {
			flow[prev[i]][i] += tmp;
			flow[i][prev[i]] -= tmp;
		}
		ans += tmp;
	}
	cout << ans;
}
