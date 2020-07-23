vector<vector<int>> scc;
int v, e;
vector<int> adj[10001];
int dfsn[10001];
int finish[10001];
int idx = 1;
stack<int> st;

int dfs(int vertex) {
	dfsn[vertex] = idx++;
	st.push(vertex);
	int ret = dfsn[vertex];
	for (int next : adj[vertex]) {
		if (!dfsn[next])
			ret = min(ret, dfs(next));
		else if (!finish[next])
			ret = min(ret, dfsn[next]);
	}
	if (dfsn[vertex] == ret) {
		vector<int> vc;
		while (1) {
			int tmp = st.top();
			st.pop();
			finish[tmp] = 1;
			vc.push_back(tmp);
			if (tmp == vertex)
				break;
		}
		scc.push_back(vc);
	}
	return ret;
}
