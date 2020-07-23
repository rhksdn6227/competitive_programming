int n;
vector<pii> adj[501];
int dist[501];



bool bf() {
	bool infinite = false;
	fill(dist, dist + n, 1e9);
	dist[1] = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			int s = adj[i].size();
			for (int j = 0; j < s; j++)
				if (dist[adj[i][j].first] > dist[i] + adj[i][j].second) {
					dist[adj[i][j].first] = dist[i] + adj[i][j].second;
					if (k == n) {
						infinite = true;
						break;
					}
				}
		}
	}
	return infinite;
}
