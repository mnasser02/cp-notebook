const int e = 0;
struct node {
    ll sum;
    node *left, *right;
    node(int x) : left(nullptr), right(nullptr), sum(x) {}
    node(node *l, node *r) : left(l), right(r), sum(e) {
        if (left) sum += l->sum;
        if (right) sum += r->sum;
    }
};
struct PersSegTree {
    int n;
    vector<node *> version;

    PersSegTree(int n_) : n(n_) {
        vi A(n, e);
        version.push_back(build(A, 0, n - 1));
    }

    PersSegTree(vi &A) {
        n = A.size();
        version.push_back(build(A, 0, n - 1));
    }

    node *build(vi &A, int l, int r) {
        if (l == r) {
            return new node(A[l]);
        }
        int m = l + r >> 1;
        return new node(build(A, l, m), build(A, m + 1, r));
    }

    ll query(node *v, int l, int r, int i, int j) {
        if (i <= l && r <= j) {
            return v->sum;
        }
        if (r < i || l > j) {
            return e;
        }
        int m = l + r >> 1;
        return query(v->left, l, m, i, j) + query(v->right, m + 1, r, i, j);
    }
    node *update(node *v, int l, int r, int p, int x) {
        if (l == r) {
            return new node(x);
        }

        int m = l + r >> 1;
        if (p <= m)
            return new node(update(v->left, l, m, p, x), v->right);
        else
            return new node(v->left, update(v->right, m + 1, r, p, x));
    }

    ll query(int i, int j, int k = -1) {
        if (k == -1) k = version.size() - 1;
        return query(version[k], 0, n - 1, i, j);
    }
    void update(int p, int x, int k = -1) {
        if (k == -1) k = version.size() - 1;
        version[k] = update(version[k], 0, n - 1, p, x);
    }
    void copy(int k = -1) {
        if (k == -1) k = version.size() - 1;
        version.push_back(version[k]);
    }
};
