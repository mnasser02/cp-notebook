template <class T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    // dont use even for pt update
    void add(int i, T val) {
        i++;
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    void range_add(int l, int r, T val) {
        add(l, val);
        if (r + 1 < n)
            add(r + 1, -val);
    }
    T pt_query(int i) {
        i++;
        T ret = 0;
        for (; i > 0; i -= i & -i)
            ret += bit[i];
        return ret;
    }
};
