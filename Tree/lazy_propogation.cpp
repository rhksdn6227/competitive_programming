int N, M, K;

struct seg {
	vl item, lz;
	int half;
	void init() {
		for (half = 1; half < N; half <<= 1);
		item.resize(half*2);
		lz.resize(half*2);
	}
	void lazy(int n, int nl, int nr) {
		if (lz[n]) {
			a[n] += lz[n] * (nr - nl + 1);
			if (n < lim) {
				lz[n * 2] += lz[n];
				lz[n * 2 + 1] += lz[n];
			}
			lz[n] = 0;
		}
	}
	void update(lint l, lint r, lint diff) { update(l, r, 1, 0, half - 1, diff); };
	void update(lint l, lint r, int n, int nl, int nr, lint diff) {
		lazy(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r){
			lz[n] += diff;
            lazy(n, nl, nr);
            return;
        }       
		int mid = (nl + nr) / 2;
		update(l, r, n * 2, nl, mid, diff);
		update(l, r, n * 2 + 1, mid+1, nr, diff);
		item[n] = item[n * 2] + item[n * 2 + 1];
	}
	lint query(lint l, lint r) { return query(l, r, 1, 0, half - 1); }
	lint query(lint l, lint r, int n, int nl, int nr) {
		lazy(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return item[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n * 2, nl, mid) + query(l, r, n * 2 + 1, mid + 1, nr);
	}
};
