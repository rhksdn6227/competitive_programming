#include <memory.h>

typedef struct Trie {
	bool terminal = false;
	Trie* child[26];
	Trie() :terminal(false) {
		memset(child, 0, sizeof(child));
	}
	~Trie() {
		for (int i = 0; i < 26; i++)
			delete child[i];
	}
	void insert(const char* key) {
		if (*key == 0) {
			terminal = true;
		}
		else {
			int x = *key - 'A';
			if (!child[x])
				child[x] = new Trie();
			child[x]->insert(key + 1);
		}
	}
	Trie* find(const char* key) {
		if (*key == 0)
			return this;
		int x = *key - 'A';
		if (!child[x])
			return NULL;
		return child[x]->find(key + 1);
	}
	
} Trie;

int main() {
	int ans = 0;
	cin >> N >> M;
	Trie t;
	char s[500];
	for (int i = 0; i < N; i++) {
		cin >> s;
		t.insert(s);
	}
	for (int i = 0; i < M; i++) {
		cin >> s;
		Trie* tmp = t.find(s);
		if (tmp != NULL && tmp->terminal == true)
			ans++;
	}
	cout << ans;
}
