const int S = 200;
struct Mo {
    const vi &A;
    int L, R;
    int ans;

    Mo(vi &A) : A(A), L(0), R(-1), ans(0) {}

    int process(int l, int r) {
        while (R < r) insert(A[++R]);
        while (R > r) erase(A[R--]);
        while (L < l) erase(A[L++]);
        while (L > l) insert(A[--L]);
        return ans;
    }
    void insert(int x) {
    }
    void erase(int x) {
    }
};

struct Query {
    int l, r, i;
    bool operator<(Query q) {
        int b1 = l / S, b2 = q.l / S;
        if (b1 == b2) return r < q.r;
        return b1 < b2;
    }
};
