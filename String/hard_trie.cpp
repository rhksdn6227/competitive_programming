using pci=pair<char,int>;

struct node {
	bool finish;
    vector<pci > next;
	node() :finish(false), next(vector<pci >()) {}
    int find_(char c){
        for (auto &tmp : next)
            if (tmp.first == c)
                return tmp.second;
        return -1;
    }
};
struct trie {
	int size;
	vector<node> sub;
	trie() :size(1) {
		sub.push_back(node());
	}
	void insert(string& str) {
		int idx = 0;
		for (int i = 0; i < str.size(); ++i) {
            int id = sub[idx].find_(str[i]);
            if(id == -1){
                sub.push_back(node());
                sub[idx].next.push_back(pci(str[i], size));
                idx = size++;
            }
			else {
				idx = id;
			}
		}
		sub[idx].finish = true;
	}
	bool search(string& str) {
		int idx = 0;
		for (int i = 0; i < str.size(); ++i) {
			int id = sub[idx].find_(str[i]);
            if(id == -1)
                return false;
			idx = id;
		}
		return sub[idx].finish;
	}
};
