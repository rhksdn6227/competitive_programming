//시간복잡도: O((n+m)*sqrt(n))
int n, m, rt;
int arr[100001];
int cnt[1000001];
int ans[100001];
int cur = 0;

//쿼리의 오른쪽 끝이 속한 블록이 증가하는 순서대로,
//블록이 같으면 왼쪽 끝이 증가하는 순서로 정렬
struct query { 
	int l, r, idx;
	bool operator<(const query& o) {
		int x = r / rt;
		int y = o.r / rt;
		return x == y ? l < o.l : x < y;
	}
}q[100001];

void make(int idx, bool add) {
	if (add) {
		if (cnt[arr[idx]]++ == 0)
			cur++;
	}
	else {
		if (--cnt[arr[idx]] == 0)
			cur--;
	}
}

int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	rt = (int)sqrt(n);
	F(i, 1, n)
		cin >> arr[i];
	cin >> m;
	F(i, 1, m) {
		int a, b;
		cin >> a >> b;
		q[i] = { a,b,i };
	}
	sort(q + 1, q + 1 + m);
	int left = 1, right = 0;
	F(i, 1, m) { //l>r이 되는 경우가 생길 수 있기 때문에 범위 확장 연산 먼저 해준다.
		while (q[i].l < left)
			make(--left, true);
    while (q[i].r > right)
			make(++right, true);
		while (q[i].l > left)
			make(left++, false);
		while (q[i].r < right)
			make(right--, false);
		
		ans[q[i].idx] = cur;
	}
	F(i, 1, m)
		cout << ans[i] << "\n";
}
