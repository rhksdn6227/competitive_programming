vector<vi> scc;
vector<int> adj[10001];
int dfsn[10001];
int finish[10001];
int idx = 1;
stack<int> st;

int dfs(int now) {
	dfsn[now] = idx++;
	st.push(now);
	int ret = dfsn[now];
	for (int next : adj[now]) {
		if (!dfsn[next])
			ret = min(ret, dfs(next));
		else if (!finish[next])
			ret = min(ret, dfsn[next]);
	}
	if (dfsn[now] == ret) {
		vector<int> vc;
		while (1) {
			int tmp = st.top();
			st.pop();
			finish[tmp] = 1;
			vc.push_back(tmp);
			if (tmp == now)
				break;
		}
		scc.push_back(vc);
	}
	return ret;
}
