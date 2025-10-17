// change comp when dealing with real coordinates
struct point {
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator<(point p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
};
struct segment {
    point l, r;
    bool h;
    segment(point l, point r) : l(l), r(r) {
        if (l.x == r.x)
            h = 0;
        else
            h = 1;
    }
    bool operator<(segment s) const {
        if (l.y != s.l.y) return l.y < s.l.y;
        if (l.x != s.l.x) return l.x < s.l.x;
        return r.x < s.r.x;
    }
};
struct event {
    point p;
    segment s;
    int type;

    event(point p, segment s) : p(p), s(s) {
        if (s.h)
            if (s.l.x == p.x)
                type = 0;  // add
            else
                type = 2;  // remove
        else
            type = 1;  // vertical event
    }
    bool operator<(event e) const {
        if (p.x != e.p.x) return p.x < e.p.x;
        return type < e.type;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<event> events;
    for (int i = 0; i < n; i++) {
        point p, q;
        cin >> p.x >> p.y >> q.x >> q.y;
        segment s(p, q);
        event e(p, s);
        events.push_back(e);
        if (s.h) {
            event e2(q, s);
            events.push_back(e2);
        }
    }
    sort(all(events));
    set<segment> active;
    set<point> inter;
    for (event e : events) {
        if (e.type == 0) {
            active.insert(e.s);
        } else if (e.type == 1) {
            auto it = active.lower_bound(
                segment({(int)-1e9, e.s.l.y}, {(int)-1e9, e.s.l.y}));
            for (; it != active.end() && it->l.y <= e.s.r.y; it++) {
                // avoid coincident end-points
                if (it->l.x == e.p.x && (it->l.y == e.s.l.y || it->l.y == e.s.r.y)) continue;
                if (it->r.x == e.p.x && (it->r.y == e.s.l.y || it->l.y == e.s.r.y)) continue;
                inter.insert(point(e.p.x, it->l.y));
            }
        } else if (e.type == 2) {
            active.erase(e.s);
        }
    }
}
