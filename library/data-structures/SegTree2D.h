template <class T>
struct SegTree2D {
    vector<vector<T>> tree;
    vector<vi>& A;
    int n, m, ni, mi;

    const T e = 0;
    T merge(T a, T b) { return a + b; }

    SegTree2D(vector<vi>& A_) : A(A_) {
        n = A.size(), m = A[0].size();
        ni = n, mi = m;
        while (__builtin_popcount(n) != 1) n++;
        while (__builtin_popcount(m) != 1) m++;

        tree.assign(2 * n, vector<T>(2 * m, e));

        build_x(1, 0, n - 1);
    }
    void build_y(int px, int lx, int rx, int py, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx) {
                if (lx >= ni || ly >= mi)
                    tree[px][py] = e;
                else
                    tree[px][py] = A[lx][ly];
            } else {
                tree[px][py] = merge(tree[px << 1][py], tree[px << 1 | 1][py]);
            }
        } else {
            int my = ly + ry >> 1;
            build_y(px, lx, rx, py << 1, ly, my);
            build_y(px, lx, rx, py << 1 | 1, my + 1, ry);
            tree[px][py] = merge(tree[px][py << 1], tree[px][py << 1 | 1]);
        }
    }
    void build_x(int px, int lx, int rx) {
        if (lx != rx) {
            int mx = lx + rx >> 1;
            build_x(px << 1, lx, mx);
            build_x(px << 1 | 1, mx + 1, rx);
        }
        build_y(px, lx, rx, 1, 0, m - 1);
    }

    T query_y(int px, int ly, int ry) {
        T ra = e, rb = e;
        for (ly += m, ry += m + 1; ly < ry; ly >>= 1, ry >>= 1) {
            if (ly & 1) ra = merge(ra, tree[px][ly++]);
            if (ry & 1) rb = merge(rb, tree[px][--ry]);
        }
        return merge(ra, rb);
    }
    T query(int lx, int rx, int ly, int ry) {
        T ra = e, rb = e;
        for (lx += n, rx += n + 1; lx < rx; lx >>= 1, rx >>= 1) {
            if (lx & 1) ra = merge(ra, query_y(lx++, ly, ry));
            if (rx & 1) rb = merge(rb, query_y(--rx, ly, ry));
        }
        return merge(ra, rb);
    }

    /*T query_y(int px, int py, int ly, int ry, int i2, int j2) {
        if (i2 <= ly && ry <= j2) {
            return tree[px][py];
        }
        if (ry < i2 || ly > j2) {
            return e;
        }
        int my = ly + ry >> 1;
        return merge(query_y(px, py << 1, ly, my, i2, j2), query_y(px, py << 1 | 1, my + 1, ry, i2, j2));
    }
    T query_x(int px, int lx, int rx, int i1, int j1, int i2, int j2) {
        if (i1 <= lx && rx <= j1) {
            return query_y(px, 1, 0, m - 1, i2, j2);
        }
        if (rx < i1 || lx > j1) {
            return e;
        }
        int mx = lx + rx >> 1;
        return merge(query_x(px << 1, lx, mx, i1, j1, i2, j2), query_x(px << 1 | 1, mx + 1, rx, i1, j1, i2, j2));
    }*/

    void update_y(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int v) {
        if (ly == ry) {
            if (lx == rx) {
                tree[px][py] = v;
            } else {
                tree[px][py] = tree[px << 1][py] + tree[px << 1 | 1][py];
            }
        } else {
            int my = ly + ry >> 1;
            if (y <= my)
                update_y(px, lx, rx, py << 1, ly, my, x, y, v);
            else
                update_y(px, lx, rx, py << 1 | 1, my + 1, ry, x, y, v);
            tree[px][py] = merge(tree[px][py << 1], tree[px][py << 1 | 1]);
        }
    }
    void update_x(int px, int lx, int rx, int x, int y, T v) {
        if (lx != rx) {
            int mx = lx + rx >> 1;
            if (x <= mx)
                update_x(px << 1, lx, mx, x, y, v);
            else
                update_x(px << 1 | 1, mx + 1, rx, x, y, v);
        }
        update_y(px, lx, rx, 1, 0, n - 1, x, y, v);
    }

    // T query(int x1, int x2, int y1, int y2) { return query_x(1, 0, n - 1, x1, x2, y1, y2); }
    void update(int x, int y, T v) { update_x(1, 0, n - 1, x, y, v); }
};
