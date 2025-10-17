struct node {
    int val = 2e9, l, r;
    node *left, *right;
    node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}

    void update(int p, int x) {  // set
        if (l == p && r == p) {
            val = x;
            return;
        }
        int m = l + r >> 1;
        if (p <= m) {
            if (!left) left = new node(l, m);
            left->update(p, x);
        } else {
            if (!right) right = new node(m + 1, r);
            right->update(p, x);
        }
        val = 2e9;  // important
        if (left) ckmin(val, left->val);
        if (right) ckmin(val, right->val);
    }
    int query(int i, int j) {  // min
        if (i <= l && r <= j) return val;
        if (j < l || r < i) return 2e9;
        int res = 2e9;
        if (left) ckmin(res, left->query(i, j));
        if (right) ckmin(res, right->query(i, j));
        return res;
    }
};
