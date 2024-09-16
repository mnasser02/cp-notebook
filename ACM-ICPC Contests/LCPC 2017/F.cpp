#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define EPS 1e-9
#define PI 3.14159265358979323846

struct point {
    ll x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {}
    point operator+(point p) const { return point(x + p.x, y + p.y); }
    point operator-(point p) const { return point(x - p.x, y - p.y); }
    bool operator<(point p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator==(point p) const {
        return x == p.x && y == p.y;
    }
};
typedef point vec;
vec toVec(point a, point b) { return vec(b - a); }
double dist(point a, point b) { return hypot(a.x - b.x, a.y - b.y); }
ll cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
bool ccw(point a, point b, point c) { return cross(toVec(a, b), toVec(a, c)) > 0; }
bool coll(point a, point b, point c) { return cross(toVec(a, b), toVec(a, c)) == 0; }
ll dot(vec a, vec b) { return a.x * b.x + a.y * b.y; }
double norm(vec v) { return sqrtl(v.x * v.x + v.y * v.y); }

double angle(point a, point o, point b) {
    vec oa = a - o, ob = b - o;
    return acosl(dot(oa, ob) / (norm(oa) * norm(ob)));
}

vector<point> CH_Andrew(vector<point>& Pts) {
    int n = Pts.size(), k = 0;
    vector<point> H(2 * n);
    sort(Pts.begin(), Pts.end());
    for (int i = 0; i < n; ++i) {
        while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while ((k >= t) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}

bool same_line(vector<point>& pts) {
    int n = pts.size();
    if (n <= 2) return true;

    for (int i = 0; i < n; i++) {
        if (!coll(pts[i], pts[(i + 1) % n], pts[(i + 2) % n])) return false;
    }
    return true;
}

bool on_segment(point p, point q, point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(point p, point q, point r) {
    ll cr = cross(toVec(p, q), toVec(p, r));
    if (cr == 0) return 0;
    return (cr > 0) ? 1 : -1;
}

bool seg_intersect(point p1, point q1, point p2, point q2) {
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

bool segpoly_inter(vector<point>& poly, point p, point q) {
    int n = poly.size();
    for (int i = 0; i < n; i++) {
        if (seg_intersect(poly[i], poly[i + 1], p, q)) return true;
    }
    return false;
}

void reorder_polygon(vector<point>& P) {
    P.pop_back();
    int pos = 0;
    for (int i = 1; i < P.size(); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
    P.push_back(P[0]);
}

vector<point> minkowski(vector<point>& P, vector<point>& Q) {
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);

    vector<point> result;
    int i = 0, j = 0;
    int n = P.size(), m = Q.size();
    while (i < n - 1 || j < m - 1) {
        result.push_back(P[i] + Q[j]);
        auto crs = cross(P[i + 1] - P[i], Q[j + 1] - Q[j]);
        if (crs >= 0 && i < P.size() - 1)
            ++i;
        if (crs <= 0 && j < Q.size() - 1)
            ++j;
    }
    result.push_back(result[0]);
    return result;
}

int insidePolygon(const vector<point>& P, point pt) {
    int n = P.size();
    if (n <= 3) return -1;  // avoid point or line
    bool on_polygon = false;
    for (int i = 0; i < n - 1; ++i)
        if (fabs(dist(P[i], pt) + dist(pt, P[i + 1]) - dist(P[i], P[i + 1])) < EPS)
            on_polygon = true;
    if (on_polygon) return 0;
    double sum = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        if (ccw(pt, P[i], P[i + 1]))
            sum += angle(P[i], pt, P[i + 1]);
        else
            sum -= angle(P[i], pt, P[i + 1]);
    }
    return fabs(sum) > PI ? 1 : -1;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<point> pts1(n), pts2(m);
    for (int i = 0; i < n; i++) {
        cin >> pts1[i].x >> pts1[i].y;
    }
    for (int i = 0; i < m; i++) {
        cin >> pts2[i].x >> pts2[i].y;
    }

    bool same1 = same_line(pts1),
         same2 = same_line(pts2);
    bool ok = 1;
    if (same1 && same2) {
        point l1, r1, l2, r2;
        l1 = *min_element(all(pts1));
        r1 = *max_element(all(pts1));
        l2 = *min_element(all(pts2));
        r2 = *max_element(all(pts2));
        if (seg_intersect(l1, r1, l2, r2)) ok = 0;
    } else if (same1) {
        vector<point> poly2 = CH_Andrew(pts2);
        point l1, r1;
        l1 = *min_element(all(pts1));
        r1 = *max_element(all(pts1));
        if (segpoly_inter(poly2, l1, r1) || insidePolygon(poly2, l1) >= 0 || insidePolygon(poly2, r1) >= 0) ok = 0;
    } else if (same2) {
        vector<point> poly1 = CH_Andrew(pts1);
        point l2, r2;
        l2 = *min_element(all(pts2));
        r2 = *max_element(all(pts2));
        if (segpoly_inter(poly1, l2, r2) || insidePolygon(poly1, l2) >= 0 || insidePolygon(poly1, r2) >= 0) ok = 0;
    } else {
        vector<point> poly1 = CH_Andrew(pts1), poly2 = CH_Andrew(pts2);
        for (auto& p : poly1) {
            p.x = -p.x;
            p.y = -p.y;
        }
        vector<point> mink_sum = minkowski(poly1, poly2);
        if (insidePolygon(mink_sum, point()) >= 0) ok = 0;
    }
    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    freopen("milano.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}