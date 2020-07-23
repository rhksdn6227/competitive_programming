const double PI = acos(-1); // PI 값을 지정해 놓음
typedef complex<double> cpx;
int n;

void fft(vector<cpx>& a, bool inv) {
	int n = a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; bit <= j; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len;
		if (inv) ang = -ang;
		cpx w(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
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
		for (int i = 0; i < n; i++) {
			a[i] /= n;
			a[i] = cpx(round(a[i].real()), round(a[i].imag())); //result is integer
		}
	}
}

vector<ll> mul(const vector<ll>& a, const vector<ll>& b) {
	vector<cpx> aa(a.begin(), a.end()), bb(b.begin(), b.end());
	int n = 1; while (n <= max(a.size(), b.size())) n <<= 1;
	aa.resize(n), bb.resize(n);
	fft(aa, 0), fft(bb, 0);
	for (int i = 0; i < n; i++) aa[i] *= bb[i];
	fft(aa, 1);
	vector<ll> ret(n);
	for (int i = 0; i < n; i++) 
		ret[i] = round(aa[i].real());
  
	return ret;
}
