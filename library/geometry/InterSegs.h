struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
};

struct segment {
    point p, q;
    int id;
    segment(point p, point q, int i) : p(p), q(q), id(i) {}
    double get_y(double x) const {
        if (abs(p.x - q.x) < EPS)
            return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

bool on_segment(point p, point q, point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(point p, point q, point r) {
    point pq(q.x - p.x, q.y - p.y), pr(r.x - p.x, r.y - p.y);
    int cross = pq.x * pr.y - pq.y * pr.x;

    if (cross == 0) return 0;
    return (cross > 0) ? 1 : -1;
}
bool seg_intersect(const segment& s1, const segment& s2) {
    point p1 = s1.p, q1 = s1.q, p2 = s2.p, q2 = s2.q;
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && on_segment(p1, p2, q1)) return true;
    if (o2 == 0 && on_segment(p1, q2, q1)) return true;
    if (o3 == 0 && on_segment(p2, p1, q2)) return true;
    if (o4 == 0 && on_segment(p2, q1, q2)) return true;

    return false;
}
bool operator<(const segment& a, const segment& b) {
    double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    return a.get_y(x) < b.get_y(x) - EPS;
}

struct event {
    double x;
    int tp, id;

    event() {}
    event(double x, int tp, int id) : x(x), tp(tp), id(id) {}

    bool operator<(const event& e) const {
        if (abs(x - e.x) > EPS)
            return x < e.x;
        return tp > e.tp;
    }
};

set<segment> s;
vector<set<segment>::iterator> where;

set<segment>::iterator prev(set<segment>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}
set<segment>::iterator next(set<segment>::iterator it) {
    return ++it;
}

ii find_inter(const vector<segment>& a) {
    int n = (int)a.size();
    vector<event> e;
    for (int i = 0; i < n; ++i) {
        e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i));
        e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i));
    }
    sort(e.begin(), e.end());

    s.clear();
    where.resize(a.size());
    for (size_t i = 0; i < e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            set<segment>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
            if (nxt != s.end() && intersect(*nxt, a[id]))
                return {nxt->id, id};
            if (prv != s.end() && intersect(*prv, a[id]))
                return {prv->id, id};
            where[id] = s.insert(nxt, a[id]);
        } else {
            set<segment>::iterator nxt = next(where[id]), prv = prev(where[id]);
            if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
                return {prv->id, nxt->id};
            s.erase(where[id]);
        }
    }
    return {-1, -1};
}
