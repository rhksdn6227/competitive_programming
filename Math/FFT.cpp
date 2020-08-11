const double PI = acos(-1); // PI 값을 지정해 놓음
typedef complex<double> cpx;
int n;

void fft(vector<cpx>& a, bool inv) {
	int sz = a.size();
	for (int i = 1, j = 0; i < sz; i++) {
		int bit = sz >> 1;
		for (; bit <= j; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= sz; len <<= 1) {
		double ang = 2 * PI / len;
		if (inv) ang = -ang;
		cpx w(cos(ang), sin(ang));
		for (int i = 0; i < sz; i += len) {
			cpx wp(1, 0);
			for (int j = 0; j < len / 2; j++) {
				cpx u = a[i + j], v = a[i + j + len / 2] * wp;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				wp *= w;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < sz; i++) {
			a[i] /= sz;
			a[i] = cpx(round(a[i].real()), round(a[i].imag())); //result is integer
		}
	}
}

vector<ll> mul(const vector<ll>& a, const vector<ll>& b) {
	vector<cpx> aa(a.begin(), a.end()), bb(b.begin(), b.end());
	int sz = 1; while (sz <= max(a.size(), b.size())) sz <<= 1;
	sz<<=1;
	aa.resize(sz), bb.resize(sz);
	fft(aa, 0), fft(bb, 0);
	for (int i = 0; i < sz; i++) aa[i] *= bb[i];
	fft(aa, 1);
	vector<ll> ret(sz);
	for (int i = 0; i < sz; i++) 
		ret[i] = round(aa[i].real());
  
	return ret;
}
