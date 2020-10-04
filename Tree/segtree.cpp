int n;
int arr[100001];

struct segtree {

	int half;
	vi item;

	void init() {
		for(half=1;half<n;half<<=1);
		item.resize(half*2);
		for (int i = 0; i < n; i++)
			item[i + half] = arr[i];
		for (int i = n; i < half; i++)
			item[i + half] = 0;
		for (int i = half - 1; i > 0; i--)
			item[i] = item[i * 2] + item[i * 2 + 1];
	}
	void update(int idx, int val) {
		idx+=half;
		item[idx] = val;
		while (idx /= 2) {
			item[idx] = item[idx * 2] + item[idx * 2 + 1];
		}
	}
	int query(int l, int r) {
		l += half;
		r += half;
		int ret = 0;
		while (l <= r) {
			if (l % 2)
				ret += item[l++];
			if (!(r % 2))
				ret += item[r--];
			l >>= 1, r >>= 1;
		}
		return ret;
	}
};
