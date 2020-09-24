vi index;

int getidx(int x) {
	return lower_bound(index.begin(), index.end(), x) - index.begin();
}

int main() {
	cin >> n;
	F(i, 1, n) {
		cin >> arr[i];
		index.push_back(arr[i]);
	}
	sort(all(index));
	index.erase(unique(all(index)), index.end());
}
