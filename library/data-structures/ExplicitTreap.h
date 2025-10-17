#define f first
#define s second

using pt = struct tnode *;
struct tnode {
    int pri, val;
    pt c[2];  // essential

    int sz;
    ll sum;         // for range queries
    bool flip = 0;  // lazy update
    tnode(int _val) {
        pri = rand();
        sum = val = _val;
        sz = 1;
        c[0] = c[1] = nullptr;
    }
    ~tnode() {
        delete c[0];
        delete c[1];
    }
};

int size(pt x) { return x ? x->sz : 0; }
ll sum(pt x) { return x ? x->sum : 0; }

pt push(pt x) {  // lazy propagation
    if (!x || !x->flip) return x;

    swap(x->c[0], x->c[1]);
    x->flip = 0;

    if (x->c[0]) x->c[0]->flip ^= 1;
    if (x->c[1]) x->c[1]->flip ^= 1;

    return x;
}

pt pull(pt x) {
    pt a = x->c[0], b = x->c[1];
    // assert(!x->flip); push(a), push(b);
    x->sz = 1 + size(a) + size(b);
    x->sum = (x->val + sum(a) + sum(b)) % M;
    return x;
}

void tour(pt x, vi &v) {  // print values of nodes,
    if (!x) return;       // inorder traversal
    // push(x);
    tour(x->c[0], v);
    v.push_back(x->val);
    tour(x->c[1], v);
}

pair<pt, pt> split(pt t, int v) {  // >= v goes to the right
    if (!t) return {t, t};
    // push(t);
    if (t->val >= v) {
        auto p = split(t->c[0], v);
        t->c[0] = p.s;
        return {p.f, pull(t)};
    } else {
        auto p = split(t->c[1], v);
        t->c[1] = p.f;
        return {pull(t), p.s};
    }
}
pair<pt, pt> splitsz(pt t, int sz) {  // sz nodes go to left
    if (!t) return {t, t};
    // push(t);
    if (size(t->c[0]) >= sz) {
        auto p = splitsz(t->c[0], sz);
        t->c[0] = p.s;
        return {p.f, pull(t)};
    } else {
        auto p = splitsz(t->c[1], sz - size(t->c[0]) - 1);
        t->c[1] = p.f;
        return {pull(t), p.s};
    }
}
pt merge(pt l, pt r) {  //  keys in l < keys in r
    if (!l || !r) return l ?: r;
    // push(l), push(r);
    pt t;
    if (l->pri > r->pri)
        l->c[1] = merge(l->c[1], r), t = l;
    else
        r->c[0] = merge(l, r->c[0]), t = r;
    return pull(t);
}
pt insert(pt x, int v) {
    auto a = split(x, v), b = split(a.s, v + 1);
    return merge(a.f, merge(new tnode(v), b.s));
}
pt erase(pt x, int v) {
    auto a = split(x, v), b = split(a.s, v + 1);
    return merge(a.f, b.s);
}
ll query(pt t, int l, int r, int i, int j) {
    if (!t || r < i || l > j) {
        return 0;
    }
    if (i <= l && r <= j) {
        return t->sum;
    }
    int m = size(t->c[0]) + l;
    ll add = (i <= m && m <= j ? t->val : 0);
    return (add + query(t->c[0], l, m - 1, i, j) + query(t->c[1], m + 1, r, i, j)) % M;
}
