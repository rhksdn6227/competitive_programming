using ll = long long;
const long long mod = 1e3;

struct matrix {
	int size;
	vector<vector<ll> > item;
	matrix(int n = 0) :size(n) {
		item.resize(n);
		for (int i = 0; i < n; ++i) item[i].resize(n);
	}
	matrix operator * (const matrix rhs) {
		matrix temp(size);
		for (int k = 0; k < size; ++k)
			for (int i = 0; i < size; ++i)
				for (int j = 0; j < size; ++j) {
					temp.item[i][j] += item[i][k] * rhs.item[k][j];
					temp.item[i][j] %= mod;
				}
		return temp;
	}
	matrix identity() {
		matrix res(size);
		for (int i = 0; i < size; ++i) res.item[i][i] = 1;
		return res;
	}
	matrix exp(ll times) {
		matrix res, tmp;

		res = matrix(size).identity();
		tmp = *this;

		while (times) {
			if (times % 2)
				res = res * tmp;
			times /= 2;
			tmp = tmp * tmp;
		}
		return res;
	}
};
