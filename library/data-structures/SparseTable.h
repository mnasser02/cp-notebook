template <class T>
struct SparseTable {
    vector<vector<T>> st;
    int log, n;

    T op(T& a, T& b) { return min(a, b); }
    SparseTable(vector<T>& A) {
        n = A.size();
        log = 32 - __builtin_clz(n);
        st.assign(n, vector<T>(log));
        for (int i = 0; i < n; i++) st[i][0] = A[i];
        for (int k = 1; k < log; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; i++) {
                st[i][k] = op(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return op(st[l][k], st[r - (1 << k) + 1][k]);
    }
};
