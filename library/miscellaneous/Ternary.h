// min of a unimodal function f
for (int i = 0; i < 50; ++i) {
    double delta = (r - l) / 3.0;
    double m1 = l + delta;
    double m2 = r - delta;
    (f(m1) > f(m2)) ? l = m1 : r = m2;
}
