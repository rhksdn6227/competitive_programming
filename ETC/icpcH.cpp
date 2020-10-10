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
#include <map>
#include <set>
#include <deque>
#include <complex>
#include <climits>
#define all(v) (v).begin(),(v).end()
#define sz(v) ((v).size())
#define F(i,s,n) for(int i=s;i<=n;i++)
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vs = vector<string>;
using pil = pair<int, ll>;
using pdd = pair<double, double>;
using pli = pair<ll, int>;
using plli = pair<ll, pii>;

int n, m;
vector<pii> adj[20001];
int fin[20001];
int state[20001];
int ok[20001];
vi v;
vi ans;

int dfs(int now, int cur,int prev=-1) {
	if (state[now] != 0) {
		if (cur*state[now] == -1) {
			ok[now] = 1;
			return 1;
		}
		else
			return 0;
	}
	state[now] = cur;
	v.push_back(now);
	int ret = 0;
	for (auto next : adj[now]) {
		if (next.first == prev)
			continue;
		ret |= dfs(next.first, cur*next.second, now);
		if (ret == 1)
			break;
	}
	if (ok[now])
		while (!v.empty()) {
			int x = v.back();
			v.pop_back();
			ans.push_back(x);
			if (x == now)
				break;
		}
	else if(ret==0&&!v.empty())
		v.pop_back();
	fin[now] = 1;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	cin >> n >> m;
	F(i, 1, m) {
		int a, b, c;
		string x;
		cin >> a >> b >> x;
		if (x[0] == '+')
			c = 1;
		else
			c = -1;
		adj[a].push_back({ b,c });
		adj[b].push_back({ a,c });
	}
	F(i, 1, n)
		if (fin[i] == 0) {
			if (dfs(i, 1))
				break;
		}

	if (ans.empty())
		cout << -1;
	else {
		cout << 1 << "\n";
		cout << ans.size() << "\n";
		for (int x : ans)
			cout << x << "\n";
	}
}
