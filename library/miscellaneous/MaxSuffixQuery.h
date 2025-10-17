map<int, ll> m;
void ins(int a, ll b) {
    auto it = m.lower_bound(a);
    if (it != end(m) && it->second >= b) return;
    it = m.insert(it, {a, b});
    it->second = b;
    while (it != begin(m) && prev(it)->second <= b) {
        m.erase(prev(it));
    }
}
ll query(int x) {
    auto it = m.lower_bound(x);
    return it == end(m) ? 0 : it->second;
}
