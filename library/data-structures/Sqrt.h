struct Sqrt {
    int sz, B, n;
    vector<vector<>> blocks;
    vi A;
    Sqrt(vi &A_) : A(A_) {
        n = A.size();
        sz = sqrt(n);
        B = (n + sz - 1) / sz;
        blocks.resize(B);
        for (int b = 0; b < B; b++) build_block(b);
    }
    void build_block(int b) {
        int l = b * sz, r = min(n, (b + 1) * sz);
        blocks[b].clear();
        for (int i = l; i < r; i++) blocks[b].push_back();
    }
    ll query_block(int b, int x) {
    }
    ll query(int l, int r, int x) {
        ll ans = 1;
        int bl = l / sz, br = r / sz;
        if (bl == br) {
            for (int i = l; i <= r; i++) {
            }
        } else {
            for (int i = l; i < sz * (bl + 1); i++) {
            }
            for (int b = bl + 1; b < br; b++) {
                query_block(b, x);
            }
            for (int i = br * sz; i <= r; i++) {
            }
        }
        return ans;
    }
    void update(int p, int x) {
        A[p] = x;
        int b = p / sz;
        build_block(b);  // if all block needs to be rebuilt
    }
};
