struct segtree {
	vl item, lz;
	int half;
	void init() {
		for (half = 1; half < n; half <<= 1);
		item.resize(half * 2);
		lz.resize(half * 2);
	}
	void lazy(int node, int nl, int nr) {
		if (lz[node]) {
			item[node] += lz[node] * (nr - nl + 1);
			if (node < half) {
				lz[node * 2] += lz[node];
				lz[node * 2 + 1] += lz[node];
			}
			lz[node] = 0;
		}
	}
	void update(ll l, ll r, ll diff) { update(l, r, 1, 0, half - 1, diff); };
	void update(ll l, ll r, int node, int nl, int nr, ll diff) {
		lazy(node, nl, nr);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lz[node] += diff;
			lazy(node, nl, nr);
			return;
		}
		int mid = (nl + nr) / 2;
		update(l, r, node * 2, nl, mid, diff);
		update(l, r, node * 2 + 1, mid + 1, nr, diff);
		item[node] = item[node * 2] + item[node * 2 + 1];
	}
	ll query(ll l, ll r) { return query(l, r, 1, 0, half - 1); }
	ll query(ll l, ll r, int node, int nl, int nr) {
		lazy(node, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return item[node];
		int mid = (nl + nr) / 2;
		return query(l, r, node * 2, nl, mid) + query(l, r, node * 2 + 1, mid + 1, nr);
	}
}seg;
