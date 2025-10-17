struct node {
    int sum = 0, lazy = 0, l, r;
    node *left, *right;
    node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}

    void extend() {
        if (!left && l != r) {
            int m = l + r >> 1;
            left = new node(l, m);
            right = new node(m + 1, r);
        }
    }

    void push() {  // lazy only for children; used when children are created when necessary
        if (!lazy || l == r || !left) return;
        left->lazy = lazy, right->lazy = lazy;
        int m = l + r >> 1;
        left->sum = (m - l + 1) * lazy, right->sum = (r - m) * lazy;
        lazy = 0;
    }

    void update(int i, int j, int x) {  // set
        if (i <= l && r <= j) {
            lazy = x;
            sum = (r - l + 1) * x;
            return;
        }
        if (l > j || r < i) return;
        extend(), push();
        left->update(i, j, x);
        right->update(i, j, x);
        sum = left->sum + right->sum;
    }
    int query(int i, int j) {  // sum
        if (i <= l && r <= j) return sum;
        if (j < l || r < i) return 0;
        extend(), push();
        return left->query(i, j) + right->query(i, j);
    }
};
