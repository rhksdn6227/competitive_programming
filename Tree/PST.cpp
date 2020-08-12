#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <limits.h>
#include <map>
#include <set>
#include <deque>
#include <complex>
#define all(v) (v).begin(),(v).end()
#define sz(v) ((v).size())
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using pdd = pair<double, double>;
using pil = pair<int, ll>;

int n, q;
struct node {
	int l, r;
	ll val;
};
ll arr[100001];

struct PST { //항상 쿼리문 들어올 때 루트노드 초기화를 직접 해줘야 한다.
	vector<node> item;
	vector<int> root;


	void init(int now, int nl = 0, int nr = n - 1) {
		if (nl == nr) {
			item[now].val = arr[nl];
			return;
		}
		int mid = (nl + nr) / 2;
		item.push_back({ 0,0,0 }), item[now].l = (int)item.size() - 1;
		init(item[now].l, nl, mid);
		item.push_back({ 0,0,0 }), item[now].r = (int)item.size() - 1;
		init(item[now].r, mid + 1, nr);
		item[now].val = item[item[now].l].val + item[item[now].r].val;
	}

	//idx:arr의 인덱스 dif:차이값 now:업데이트하는 버전의 루트노드 nl,lr:노드의 구간정보
	void update(int idx, int dif, int now = 1, int nl = 0, int nr = n - 1) {
		if (nl == nr) return;
		int mid = (nl + nr) / 2;
		if (idx <= mid) {
			int lidx = item[now].l;
			item.push_back({ item[lidx].l, item[lidx].r, item[lidx].val + dif });
			item[now].l = (int)item.size() - 1;
			update(idx, dif, item[now].l, nl, mid);
		}
		else {
			int ridx = item[now].r;
			item.push_back({ item[ridx].l, item[ridx].r, item[ridx].val + dif });
			item[now].r = (int)item.size() - 1;
			update(idx, dif, item[now].r, mid + 1, nr);
		}
	}

	ll sum(int l, int r, int now, int nl = 0, int nr = n - 1) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return item[now].val;
		int mid = (nl + nr) / 2;
		return sum(l, r, item[now].l, nl, mid) + sum(l, r, item[now].r, mid + 1, nr);
	}
}pst;




int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	pst.item.resize(2);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	pst.root.push_back(1);
	pst.init(1);
	cin >> q;
	while (q--) {
		int x;
		cin >> x;
		if (x == 1) {
			int i, v;
			cin >> i >> v;
			i--;
			pst.item.push_back(pst.item[pst.root.back()]);
			pst.item.back().val += v - arr[i];
			pst.root.push_back(pst.item.size()-1);
			pst.update(i, v - arr[i], pst.root.back());
			arr[i] = v;
		}
		else {
			int k, i, j;
			cin >> k >> i >> j;
			i--, j--;
			cout << pst.sum(i, j, pst.root[k]) << "\n";
		}
	}
}
