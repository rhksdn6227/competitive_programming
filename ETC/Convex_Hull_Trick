typedef struct { //f(x)=ax+b (x>=s)
	ll a, b;
	double s;
}line;

int n;
ll a, b, c;
ll arr[1000001];
ll psum[1000001];
line l[1000001];
ll dp[1000001];

double cross_x(line x, line y) { //두 직선의 교점의 x좌표
	return ((double)(x.b - y.b)) / ((double)(y.a - x.a));
}

//기울기가 단조증가할때 최대값 구하기

int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n >> a >> b >> c;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		psum[i] = psum[i - 1] + arr[i];
	}
	int top = 0;
	for (int i = 1; i <= n; i++) {
		ll f = psum[i] * psum[i] * a + psum[i] * b + c;
		line now = { a*(-2)*psum[i - 1],a * psum[i - 1] * psum[i - 1] - b * psum[i - 1] + dp[i - 1],0 };
		while (top > 0) {
			now.s = cross_x(now, l[top - 1]);
			if (now.s > l[top - 1].s)
				break;
			top--;
		}
		l[top++] = now;
		int left = 0, right = top - 1, mid;
		int ans=0;
		while (left <= right) { //이분탐색으로 해당하는 직선 찾기
			mid = (left + right) / 2;
			if (l[mid].s > psum[i])
				right = mid - 1;
			else {
				ans = mid;
				left = mid + 1;
			}
		}
		dp[i] = f + l[ans].a*psum[i] + l[ans].b;
	}
	cout << dp[n];
}
