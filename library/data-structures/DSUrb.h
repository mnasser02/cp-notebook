struct DSU {
    struct save {
        int x, y, hx, hy, cc;
    };

    vector<int> h, p;
    int cc;
    stack<save> history;

    DSU(int n) : h(n), p(n), cc(n) {
        iota(all(p), 0);
    }

    int find(int x) { return x == p[x] ? x : find(p[x]); }
    bool join(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return false;
        } else {
            if (h[px] < h[py]) swap(px, py);

            history.push({px, py, h[px], h[py], cc});

            if (h[px] == h[py]) h[px]++;
            cc--;
            p[py] = px;

            return true;
        }
    }

    void rollback() {
        auto [x, y, hx, hy, c] = history.top();
        history.pop();
        p[x] = x, p[y] = y, h[x] = hx, h[y] = hy;
        cc = c;
    }
};
