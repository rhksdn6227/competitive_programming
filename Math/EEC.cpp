int a, b, c; //ax+by=c (c%gcd(a,b)==0 이어야 답 있음
int r0, r1, s0, s1, t0, t1; //gcd(a,b)=r0   a*s0+b*t0=r0  
//x0=s0*c/r0  y0=t0*c/r0   x=x0+alpha*s1(=b/r0)  y=y0+alpha*t1(=a/r0)
//a=s0*t1  b=s1*t0
void EEC() {
	r0 = a, r1 = b;
	s0 = 1, s1 = 0;
	t0 = 0, t1 = 1;
	while (r1) {
		int q = r0 / r1;
		int tmp = r0;
		r0 = r1;
		r1 = tmp - r1 * q;
		tmp = s0;
		s0 = s1;
		s1 = tmp - s1 * q;
		tmp = t0;
		t0 = t1;
		t1 = tmp - t1 * q;
	}
}

int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	a = 69, b = 30, c = 12;
	EEC();
	cout << r0 << " " << r1 << " " << s0 << " " << s1 << " " << t0 << " " << t1;
}
