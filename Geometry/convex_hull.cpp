int n;
vector<pii> point;
vector<pii> convex_hull;

ll ccw(pii a, pii b, pii c) {
	pii x = pii(b.first - a.first, b.second - a.second);
	pii y = pii(c.first - a.first, c.second - a.second);
	ll ret = x.first*y.second - x.second*y.first;
	return ret;
}

bool cmp(pii x,pii y) {
	ll t = ccw(point[0], x, y);
	if (t == 0) {
		if (x.first == y.first)
			return abs(point[0].second - x.second) < abs(point[0].second - y.second);
		return abs(point[0].first - x.first) < abs(point[0].first - y.first);
	}
	else if (t > 0)
		return true;
	else
		return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		point.push_back(pii(x, y));
	}
	swap(point[0], *min_element(point.begin(), point.end()));
	sort(point.begin() + 1, point.end(), cmp);
	
  int chsz=0;
	for (int i = 0; i < n; i++) {
		while (chsz >= 2) {
			pii f = convex_hull[tmpsize - 2], s = convex_hull[tmpsize - 1];
			if (ccw(f, s, point[i]) > 0)
				break;
			convex_hull.pop_back();
			chsz--;
		}
		convex_hull.push_back(point[i]);
		chsz++;
	}
}
