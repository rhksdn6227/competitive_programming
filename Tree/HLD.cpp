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
#include <halfits.h>
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

struct seg {
	int item[270000], half;
	void init(int n) {
		for (half = 1; half <= n; half <<= 1);
	}
	void update(int x, int v) {
		x += half;
		item[x] = v;
		while (x > 1) {
			x >>= 1;
			item[x] = max(item[2 * x], item[2 * x + 1]);
		}
	}
	int query(int s, int e) {
		s += half;
		e += half;
		int ret = -1e9;
		while (s <= e) {
			if (s % 2 == 1) ret = max(ret, item[s++]);
			if (e % 2 == 0) ret = max(ret, item[e--]);
			s >>= 1;
			e >>= 1;
		}
		return ret;
	}
}seg;

typedef pair<int, int> p;

int n, m;
int depth[101010], lcaT[20][101010], par[101010], weight[101010];
int comp[101010], head[101010], lab[101010];
int piv1, piv2;
vector<p> g[101010];
int newCost[101010];
int s[101010], e[101010], c[101010];

void dfs(int now, int prv) {
	weight[now] = 1;
	for (auto& i : g[now]) {
		int nxt = i.first, cost = i.second;
		if (nxt == prv) continue;
		depth[nxt] = depth[now] + 1;
		lcaT[0][nxt] = now;
		par[nxt] = now;
		newCost[nxt] = cost;
		dfs(nxt, now);
		weight[now] += weight[nxt];
	}
}

void hld(int now, int prv) {
	sort(g[now].begin(), g[now].end(), [](const p& a, const p& b) {
		return weight[a.first] > weight[b.first];
		});

	int heavy = -1;
	for (auto& i : g[now]) {
		int nxt = i.first;
		if (nxt == prv) continue;
		heavy = nxt;
		comp[nxt] = comp[now];
		lab[nxt] = ++piv2;
		hld(nxt, now);
		break;
	}

	for (auto& i : g[now]) {
		int nxt = i.first;
		if (nxt == heavy || nxt == prv) continue;
		comp[nxt] = ++piv1;
		head[piv1] = nxt;
		lab[nxt] = ++piv2;
		hld(nxt, now);
	}
}

int lca(int s, int e) {
	if (depth[s] > depth[e]) swap(s, e);
	int diff = depth[e] - depth[s];
	for (int i = 0; i < 20; i++) {
		if ((diff >> i) & 1) e = lcaT[i][e];
	}
	for (int i = 19; i >= 0; i--) {
		if (lcaT[i][s] != lcaT[i][e]) s = lcaT[i][s], e = lcaT[i][e];
	}
	if (s == e) return s;
	return lcaT[0][s];
}

void update(int idx, int val) {
	if (depth[s[idx]] > depth[e[idx]]) swap(s[idx], e[idx]);
	seg.update(lab[e[idx]], val);
}

int sub_query(int s, int e) {
	int ret = 0;
	while (comp[s] != comp[e]) {
		int ss = head[comp[s]], ee = head[comp[e]];
		if (depth[ss] > depth[ee]) {
			ret = max(ret, seg.query(lab[ss], lab[s]));
			s = par[ss];
		}
		else {
			ret = max(ret, seg.query(lab[ee], lab[e]));
			e = par[ee];
		}
	}
	if (depth[e] > depth[s]) swap(s, e);
	ret = max(ret, seg.query(lab[e] + 1, lab[s]));
	return ret;
}

int query(int u, int v) {
	int t = lca(u, v);
	return max(sub_query(u, t), sub_query(v, t));
}



int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	seg.init(n);
	for (int i = 1; i < n; i++) {
		cin >> s[i] >> e[i] >> c[i];
		g[s[i]].push_back({ e[i], c[i] });
		g[e[i]].push_back({ s[i], c[i] });
	}

	dfs(1, 0);
	for (int i = 1; i < 20; i++) {
		for (int j = 1; j <= n; j++) {
			lcaT[i][j] = lcaT[i - 1][lcaT[i - 1][j]];
		}
	}

	head[1] = comp[1] = lab[1] = piv1 = piv2 = 1;
	hld(1, 0);
	for (int i = 2; i <= n; i++) {
		seg.update(lab[i], newCost[i]);
	}
	cin >> m;
	while (m--) {
		int op; cin >> op;
		if (op == 1) {
			int idx, val; cin >> idx >> val;
			update(idx, val);
		}
		else {
			int u, v; cin >> u >> v;
			cout << query(u, v) << "\n";
		}
	}
}

//출처:https://justicehui.github.io/hard-algorithm/2019/02/06/HLD/
