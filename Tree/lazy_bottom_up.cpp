vector<ll> arr;

struct SegtreeLazy {
    int bs, h;
    vector<ll> tree, prop;
    ll initVal;
    ll op(ll a, ll b) {
        return a + b;
    }
    ll op2(ll a, ll b, ll cnt) {
        return a + b * cnt;
    }
    SegtreeLazy(int n, ll init,vector<ll> arr)
        : initVal(init) {
        for (bs = 1, h = 0; bs < n; bs <<= 1, ++h);
        tree.resize(bs * 2);
        prop.resize(bs);
        for (int i = 0; i < n; i++)
            tree[i + bs] = arr[i];
        for (int i = bs - 1; i > 0; i--)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    // fill initial value in all nodes
    // O(n)
    void clear() {
        fill(tree.begin(), tree.end(), initVal);
        fill(prop.begin(), prop.end(), 0);
    }

    // make tree with prepared leaf values
    // O(n)
    void build() {
        for (int x = bs - 1; x > 0; --x)
            tree[x] = op(tree[x << 1], tree[x << 1 | 1]);
    }

    // apply val to node x  which interval length is cnt
    // O(1)
    void applyNode(int x, ll cnt, ll val) {
        tree[x] = op2(tree[x], val, cnt);
        if (x < bs) prop[x] = op(prop[x], val);
    }

    // merge node x's child  which interval length is cnt
    // O(1)
    void mergeNode(int x, ll cnt) {
        if (x >= bs) return;
        tree[x] = op2(op(tree[x << 1], tree[x << 1 | 1]), prop[x], cnt);
    }

    // propagate all ancestors of leaf x
    // O(log(n))
    void push(int x) {
        for (int hh = h, cnt = 1 << h; hh > 0; --hh, cnt >>= 1) {
            int p = x >> hh;
            if (prop[p] != 0) {
                applyNode(p << 1, cnt >> 1, prop[p]);
                applyNode(p << 1 | 1, cnt >> 1, prop[p]);
                prop[p] = 0;
            }
        }
    }

    // get value of [s, e]
    // 0 <= s, e < bs
    // O(log(n))
    ll query(int s, int e) {
        s |= bs;  e |= bs;
        push(s);  push(e);
        ll ret0 = initVal, ret1 = initVal;
        for (; s <= e; s = (s + 1) >> 1, e = (e - 1) >> 1) {
            if (s & 1) ret0 = op(ret0, tree[s]);
            if (!(e & 1)) ret1 = op(tree[e], ret1);
        }
        return op(ret0, ret1);
    }

    // apply val to [s, e]
    // 0 <= s, e < bs
    // O(log(n))
    void apply(int s, int e, ll val) {
        s |= bs;  e |= bs;
        push(s);  push(e);
        for (int s0 = s, e0 = e, cnt = 1; s0 <= e0; s0 = (s0 + 1) >> 1, e0 = (e0 - 1) >> 1, cnt <<= 1) {
            if (s0 & 1) applyNode(s0, cnt, val);
            if (!(e0 & 1)) applyNode(e0, cnt, val);
        }
        for (int s0 = s >> 1, e0 = e >> 1, cnt = 2; s0 > 0; s0 >>= 1, e0 >>= 1, cnt <<= 1) {
            mergeNode(s0, cnt);
            mergeNode(e0, cnt);
        }
    }
};
