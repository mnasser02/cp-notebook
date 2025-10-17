double perimeter(const vector<point>& P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)
        // note: P[n-1] = P[0]
        ans += dist(P[i], P[i + 1]);
    return ans;
}
double area(const vector<point>& P) {
    double ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return fabs(ans) / 2.0;
}
// returns true if we always make the same turn
bool isConvex(const vector<point>& P) {
    int n = (int)P.size();
    // a point/sz=2 or a line/sz=3 is not convex
    if (n <= 3) return false;
    bool firstTurn = ccw(P[0], P[1], P[2]);
    for (int i = 1; i < n - 1; ++i)
        if (ccw(P[i], P[i + 1], P[(i + 2) == n ? 1 : i + 2]) != firstTurn)
            return false;  // different -> concave
    return true;           // otherwise -> convex
}

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point>& P) {
    int n = (int)P.size();
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
    return fabs(sum) > M_PI ? 1 : -1;  // 360d->in, 0d->out
}

// compute the intersection point between line segment p-q and line A-B
point lineIntersectSeg(point p, point q, point A, point B) {
    double a = B.y - A.y, b = A.x - B.x, c = B.x * A.y - A.x * B.y;
    double u = fabs(a * p.x + b * p.y + c);
    double v = fabs(a * q.x + b * q.y + c);
    return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}

// cuts polygon Q along the line formed by point A->point B (order matters)
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point A, point B, const vector<point>& Q) {
    vector<point> P;
    for (int i = 0; i < (int)Q.size(); ++i) {
        double left1 = cross(toVec(A, B), toVec(A, Q[i])), left2 = 0;
        if (i != (int)Q.size() - 1) left2 = cross(toVec(A, B), toVec(A, Q[i + 1]));
        if (left1 > -EPS) P.push_back(Q[i]);
        if (left1 * left2 < -EPS)
            P.push_back(lineIntersectSeg(Q[i], Q[i + 1], A, B));
    }
    if (!P.empty() && !(P.back() == P.front()))
        P.push_back(P.front());
    return P;
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

// P has no repeated vertix at the back
vii antipodal_pairs(vector<point>& P) {
    int n = P.size();

    if (n == 1) return {};
    if (n == 2) return {{0, 1}};

    vii ans;
    int i0 = n - 1;
    int i = 0;
    int j = i + 1;
    int j0 = j;
    while (tri_area(P[i], P[i + 1], P[j + 1]) - tri_area(P[i], P[i + 1], P[j]) > EPS) {
        j = j + 1;
        j0 = j;
    }
    ans.push_back({i, j});
    while (j != i0) {
        i = i + 1;
        ans.push_back({i, j});

        while (tri_area(P[i], P[i + 1], P[j + 1]) - tri_area(P[i], P[i + 1], P[j]) > EPS) {
            j = j + 1;
            if ((i != j0 && j != i0))
                ans.push_back({i, j});
            else
                return ans;
        }
        if (fabs(tri_area(P[j], P[i + 1], P[j + 1]) - tri_area(P[i], P[i + 1], P[j])) < EPS) {
            if (i != j0 && j != i0)
                ans.push_back({i, j + 1});
            else
                ans.push_back({i + 1, j});
        }
    }
    return ans;
}
// Minkowski Sum
void reorder_polygon(vector<point>& P) {
    P.pop_back();
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
    P.push_back(P[0]);
}
vector<point> minkowski(vector<point>& P, vector<point>& Q) {
    reorder_polygon(P);
    reorder_polygon(Q);

    vector<point> result;
    size_t i = 0, j = 0;
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
// for (auto& p : poly1) {
//     p.x = -p.x;
//     p.y = -p.y;
// }
// vector<point> mink_sum = minkowski(poly1, poly2);
// min_dist b/w polygons is min_dist from (0, 0) to mink_sum
// insidePolygon(mink_sum, point()) >= 0 (polygons intersect)
