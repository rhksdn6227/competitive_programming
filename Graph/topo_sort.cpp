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
		int tmp = q.front();
		cout << tmp << " ";
		q.pop();
		int s = adj[tmp].size();
		for (int i = 0; i < s; i++) {
			indegree[adj[tmp][i]]--;
			if (indegree[adj[tmp][i]] == 0)
				q.push(adj[tmp][i]);
		}

	}
}
