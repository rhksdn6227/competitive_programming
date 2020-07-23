int n, m;
int indegree[32001];
vector<int> adj[32001];

void toposort() {
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (indegree[i] == 0)
			q.push(i);
	for (int x = 1; x <= n; x++) {
		if (q.empty()) {
			cout << "impossible";
			break;
		}
		int now = q.front();
		//cout << tmp << " ";
		q.pop();
		for (int next:adj[now]) {
			indegree[next]--;
			if (indegree[next] == 0)
				q.push(next);
		}

	}
}
