// min of a unimodal function f
for (int i = 0; i < 50; ++i) {
    double delta = (r - l) / 3.0;
    double m1 = l + delta;
    double m2 = r - delta;
    (f(m1) > f(m2)) ? l = m1 : r = m2;
}

// discrete, max
while (l + 3 < r) {
    int m1 = (2 * l + r) / 3;
    int m2 = (l + 2 * r) / 3;
    f(m1) <= f(m2) ? l = m1 : r = m2;
}
ll mx = f(l++);
while (l <= r) chmax(mx, f(l++));
return mx;