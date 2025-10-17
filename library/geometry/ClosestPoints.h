// change comparisons when dealing with real coordinates
struct point {
    ll x, y;
    point(ll x = 0, ll y = 0) : x(x), y(y) {}
    bool operator<(point p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};
sort(all(points));

auto cmp = [](const point& p, const point& q) {
    if (p.y != q.y) return p.y < q.y;
    return p.x < q.x;
};

set<point, decltype(cmp)> active(cmp);
int leftmost_i = 0;
ll min_dist = 1e18;
for (point curr : points) {
    while ((curr.x - points[leftmost_i].x) * (curr.x - points[leftmost_i].x) > min_dist) {
        active.erase(points[leftmost_i]);
        leftmost_i++;
    }
    auto it = active.lower_bound({curr.x, curr.y - (int)sqrt(min_dist)});
    for (; it != active.end() && it->y <= curr.y + (int)sqrt(min_dist);
         it++)
        min_dist = min(min_dist, dist2(*it, curr));
    active.insert(curr);
}
