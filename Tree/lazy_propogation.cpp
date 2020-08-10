int N, M, K;

struct seg {
	lint a[2100000], lz[2100000], lim;
	void init() {
		for (lim = 1; lim < N; lim <<= 1);
		memset(a, 0, sizeof(a));
		memset(lz, 0, sizeof(lz));
		for (int i = 0; i < N; i++)
			cin >> a[i + lim];
		for (int i = lim - 1; i; i--)
			a[i] = a[i * 2] + a[i * 2 + 1];
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
	void update(lint l, lint r, lint diff) { update(l, r, 1, 0, lim - 1, diff); };
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
		a[n] = a[n * 2] + a[n * 2 + 1];
	}
	lint query(lint l, lint r) { return query(l, r, 1, 0, lim - 1); }
	lint query(lint l, lint r, int n, int nl, int nr) {
		lazy(n, nl, nr);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return a[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n * 2, nl, mid) + query(l, r, n * 2 + 1, mid + 1, nr);
	}
}seg;
