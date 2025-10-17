#include <bits/stdc++.h>
using namespace std;

/** BST that supports split/merge
 *
 * Sources:
 *  https://github.com/mzhang2021/cp-library/blob/master/implementations/data-structures/SplayTree.h
 *  https://ocw.mit.edu/courses/6-854j-advanced-algorithms-fall-2008/921232cb9a69015c50002ff5ea6a9824_lec6.pdf
 * Verification:
 *  https://judge.yosupo.jp/submission/321184
 * Time: O(logn)
 */

const int MX = 1e6 + 5, M = 998244353;
struct node {
    int p, ch[2], sz;
    long long val, sum, lazyb, lazyc;
    bool flip;
    node(long long x = 0) : ch(), val(x), sum(x), flip(0), p(0), sz(0), lazyb(1), lazyc(0) {}
} t[MX];
int id = 1;

void push(int u) {
    if (!u) return;
    if (t[u].lazyb != 1 || t[u].lazyc) {
        t[u].val = (t[u].lazyb * t[u].val + t[u].lazyc) % M;
        t[u].sum = (t[u].lazyb * t[u].sum + t[u].lazyc * t[u].sz) % M;

        for (int i = 0; i < 2; i++) {
            int v = t[u].ch[i];
            if (v) {
                t[v].lazyb = t[v].lazyb * t[u].lazyb % M;
                t[v].lazyc = (t[v].lazyc * t[u].lazyb + t[u].lazyc) % M;
            }
        }

        t[u].lazyb = 1;
        t[u].lazyc = 0;
    }
    if (t[u].flip) {
        swap(t[u].ch[0], t[u].ch[1]);
        t[t[u].ch[0]].flip ^= 1;
        t[t[u].ch[1]].flip ^= 1;
        t[u].flip = 0;
    }
}

void pull(int u) {
    int l = t[u].ch[0], r = t[u].ch[1];
    push(l), push(r);
    t[u].sz = t[l].sz + t[r].sz + 1;
    t[u].sum = (t[l].sum + t[r].sum + t[u].val) % M;
}

void attach(int u, int v, int d) {
    t[u].ch[d] = v;
    t[v].p = u;
    pull(u);
}

int build(vector<int>& A, int l, int r) {
    if (l > r) return 0;
    int m = (l + r) / 2, u = id++;
    t[u] = node(A[m]);
    attach(u, build(A, l, m - 1), 0);
    attach(u, build(A, m + 1, r), 1);
    return u;
}

int dir(int u) {
    int p = t[u].p;
    return t[p].ch[0] == u ? 0 : (t[p].ch[1] == u ? 1 : -1);
}

void rotate(int u) {
    int v = t[u].p, w = t[v].p;
    int du = dir(u), dv = dir(v);

    attach(v, t[u].ch[!du], du);
    attach(u, v, !du);

    if (~dv) {
        attach(w, u, dv);
    } else {
        t[u].p = w;
    }
}

void splay(int u) {
    while (true) {
        int v = t[u].p, w = t[v].p;
        int du = dir(u), dv = dir(v);
        push(w), push(v), push(u);
        if (du == -1) return;
        if (~dv) rotate(du == dv ? v : u);
        rotate(u);
    }
}

int find(int u, int i) {
    assert(u);
    push(u);
    int rk = t[t[u].ch[0]].sz;

    if (i < rk) {
        return find(t[u].ch[0], i);
    } else if (i > rk) {
        return find(t[u].ch[1], i - rk - 1);
    } else {
        splay(u);
        return u;
    }
}

int find_max(int u) {
    push(u);
    while (t[u].ch[1]) {
        u = t[u].ch[1];
        push(u);
    }
    splay(u);
    return u;
}

int find_min(int u) {
    push(u);
    while (t[u].ch[0]) {
        u = t[u].ch[0];
        push(u);
    }
    splay(u);
    return u;
}

int merge(int l, int r) {
    push(l), push(r);
    if (!l || !r) return l ? l : r;
    l = find_max(l);
    attach(l, r, 1);
    return l;
}

pair<int, int> split(int u, int i) {
    assert(i < t[u].sz);
    if (i == -1) {
        return {0, u};
    }
    u = find(u, i);
    int v = t[u].ch[1];
    t[u].ch[1] = t[v].p = 0;
    pull(u);
    return {u, v};
}

int insert(int u, int i, int val) {
    int v = id++;
    t[v] = node(val);

    auto [l, r] = split(u, i - 1);
    attach(v, l, 0);
    attach(v, r, 1);

    return v;
}

int erase(int u, int i) {
    u = find(u, i);
    int l = t[u].ch[0], r = t[u].ch[1];
    t[l].p = t[r].p = 0;
    return merge(l, r);
}

int reverse(int u, int l, int r) {
    auto [a, b] = split(u, l - 1);
    auto [c, d] = split(b, r - l);
    t[c].flip ^= 1;
    return merge(merge(a, c), d);
}

int update(int u, int l, int r, int x, int y) {
    auto [a, b] = split(u, l - 1);
    auto [c, d] = split(b, r - l);
    t[c].lazyb = x;
    t[c].lazyc = y;
    return merge(merge(a, c), d);
}

pair<int, int> query(int u, int l, int r) {
    auto [a, b] = split(u, l - 1);
    auto [c, d] = split(b, r - l);
    push(c);
    int ans = t[c].sum;
    u = merge(merge(a, c), d);
    return {u, ans};
}