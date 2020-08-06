
int p[20][1000000];
vector<int> adj[1000000];
int depth[1000000];

void init() {
	for (int pw = 1; pw < 20; pw++)
		for (int v = 0; v < w * h; v++) {
			p[pw][v] = p[pw - 1][p[pw - 1][v]];
		}
}

void dfs(int now,int bf,int d) {
	visited[now] = 1;
	p[now][0] = bf;
	depth[now] = d;
	for (int next:adj[now]) {
    if(next==bf)
      continue;
    if(visited[next])
      continue;
		dfs(adj[c][i], c, d + 1);
	}
}

int query(int x, int y) {
	int cx = x, cy = y;
	if (depth[x] < depth[y])
		swap(x, y);

	for (int i = 19; i >= 0; i--)
		if (depth[p[i][x]] >= depth[y]) {
			x = p[i][x];
		}
	if (x == y)
		return x;
	for (int i = 19; i >= 0; i--)
		if (p[i][x] != p[i][y]) {
			x = p[i][x];
			y = p[i][y];
		}
	int lca = p[0][x];
  return lca;
}
