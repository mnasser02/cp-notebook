struct line {
    double a, b, c;
};
void pointsToLine(point p1, point p2, line& l) {
    if (fabs(p1.x - p2.x) < EPS)
        l = {1.0, 0.0, -p1.x};
    else {
        double a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l = {a, 1.0, -(double)(a * p1.x) - p1.y};
    }
}
struct line2 {
    double m, c;
};

int pointsToLine2(point p1, point p2, line2& l) {
    if (p1.x == p2.x) {
        l.m = INF;
        l.c = p1.x;
        return 0;
    } else {
        l.m = (double)(p1.y - p2.y) / (p1.x - p2.x);
        l.c = p1.y - l.m * p1.x;
        return 1;
    }
}

bool areParallel(line l1, line l2) {
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(line l1, line l2) {
    return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

bool areIntersect(line l1, line l2, point& p) {
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS)
        p.y = -(l1.a * p.x + l1.c);
    else
        p.y = -(l2.a * p.x + l2.c);
    return true;
}

struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(const point& a, const point& b) {
    return vec(b.x - a.x, b.y - a.y);
}
vec scale(const vec& v, double s) {
    return vec(v.x * s, v.y * s);
}

point translate(const point& p, const vec& v) {
    return point(p.x + v.x, p.y + v.y);
}

// convert point and slope to line
void pointSlopeToLine(point p, double m, line& l) {
    l.a = -m;
    l.b = 1;
    l.c = -((l.a * p.x) + (l.b * p.y));
}

void closestPoint(line l, point p, point& ans) {
    line perpendicular;
    if (fabs(l.b) < EPS) {
        ans.x = -(l.c);
        ans.y = p.y;
        return;
    }
    if (fabs(l.a) < EPS) {
        ans.x = p.x;
        ans.y = -(l.c);
        return;
    }
    pointSlopeToLine(p, 1 / l.a, perpendicular);
    areIntersect(l, perpendicular, ans);
}

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point& ans) {
    point b;
    closestPoint(l, p, b);
    vec v = toVec(p, b);
    ans = translate(translate(p, v), v);
}

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

double angle(const point& a, const point& o, const point& b) {
    vec oa = toVec(o, a), ob = toVec(o, b);  // a != o != b
    return acos(dot(oa, ob) / (sqrt(norm_sq(oa)) * sqrt(norm_sq(ob))));
}  // angle aob in rad, sqrt both to avoid overflow

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter
double distToLine(point p, point a, point b, point& c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    // formula: c = a + u*ab
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

double distToLineSegment(point p, point a, point b, point& c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {
        c = point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0) {
        c = point(b.x, b.y);
        return dist(p, b);
    }
    return distToLine(p, a, b, c);
}

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > EPS;
}

bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}
