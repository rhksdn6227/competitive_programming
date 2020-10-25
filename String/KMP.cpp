#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

string a, b;
int failure[1000001]; //a[j]와 b[i]가 다를 때, failure[i-1]번째부터 a[j]와 다시 비교 시작
vi ans;

int main() {
	/*#ifndef ONLINE_JUDGE
	freopen("output.txt", "w", stdout);
	#endif*/
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	getline(cin, a);
	getline(cin, b);
	//실패함수 전처리
	for (int i = 1, j = 0; i < b.length(); i++) { 
		while (j > 0 && b[i] != b[j]) j = failure[j - 1];
		if (b[i] == b[j]) failure[i] = ++j;
	}

	int idx = 0;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == b[idx]) {
			if (idx == b.length() - 1) {
				ans.push_back(i - b.length() + 2);
				idx = failure[idx]; //중요!!
			}
			else
				idx++;
		}
		else {
			if (idx == 0)
				continue;
			idx = failure[idx - 1];
			i--;
		}
	}
	cout << ans.size() << "\n";
	for (int a : ans)
		cout << a << " ";
}
