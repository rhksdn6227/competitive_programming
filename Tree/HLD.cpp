int n;
vi adj[100001];

struct segtree {

	int n, half;
	vi item;

	segtree(int rn) {
		n = rn;
		for (half = 1; half < n; half <<= 1);
		item.resize(half * 2);
	}
	void init(vector<int>& arr) {
		for (int i = 0; i < n; i++)
			item[i + half] = arr[i];
		for (int i = n; i < half; i++)
			item[i + half] = 0;
		for (int i = half - 1; i > 0; i--)
			item[i] = item[i * 2] + item[i * 2 + 1];
	}
	void update(int idx, int val) {
		idx += half;
		item[idx] = val;
		while (idx /= 2) {
			item[idx] = max(item[idx * 2], item[idx * 2 + 1]);
		}
	}
	int query(int l, int r) {
		l += half;
		r += half;
		int ret = 0;
		while (l <= r) {
			if (l % 2)
				ret = max(ret, item[l++]);
			if (!(r % 2))
				ret = max(ret, item[r--]);
			l >>= 1, r >>= 1;
		}
		return ret;
	}
};

struct hld {
	vi par, dep, heavy, head, pos; 
	//par[i]:i의 부모  dep[i]:i의 트리상 깊이  heavy[i]:노드i의 자식들 중 가장 무거운쪽 자식
	//head[i]:i노드가 속한 체인에 속한 노드중 제일 깊이 얕은 놈 pos[i]:노드i의 decompose된 상태의 인덱스
	int cur_pos = 0;
	
	hld(int rn) {
		par.resize(rn + 1);
		dep.resize(rn + 1);
		heavy.resize(rn + 1);
		head.resize(rn + 1);
		pos.resize(rn + 1);
		fill(all(heavy), -1);
	}

	int dfs(int cur) { //par,dep,heavy를 알아낸다
		int ret = 1, mx = 0;
		for (int next : adj[cur]) {
			if (next == par[cur]) continue;
			par[next] = cur, dep[next] = dep[cur] + 1;
			int next_sz = dfs(next);
			ret += next_sz;
			if (mx < next_sz)
				mx = next_sz, heavy[cur] = next;
		}
		return ret;
	}
	void decompose(int cur, int top) { //head,pos를 알아낸다
		head[cur] = top, pos[cur] = cur_pos++;
		if (heavy[cur] != -1)
			decompose(heavy[cur], top);

		for (int next : adj[cur]) {
			if (next != par[cur] && next != heavy[cur])
				decompose(next, next);
		}
	}
	int query(int l, int r,segtree& seg) {
		int ret = 0;
		for (; head[l] != head[r]; r = par[head[r]]) {
			if (dep[head[l]] > dep[head[r]]) swap(l, r);
			int tmp = seg.query(pos[head[r]], pos[r]);
			ret = max(ret, tmp);
		}
		if (dep[l] > dep[r]) swap(l, r);
		if (pos[l] != pos[r]) {
			int tmp = seg.query(pos[l] + 1, pos[r]);
			ret = max(ret, tmp);
		}
		return ret;
	}
	void update(int i, int val,segtree& seg) {
		seg.update(pos[i], val);
	}
};
