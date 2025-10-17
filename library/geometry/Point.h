#define M_PI 3.14159265358979323846
struct point {
    double x, y;
    point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
    bool operator<(point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator==(point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};
double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}
// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad));
}
