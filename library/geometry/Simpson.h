double simpson(double a, double b) {
    int steps = 1e6;
    double dx = 1.0 * (b - a) / steps;
    double x = a;
    double ans = f(x);
    for (int i = 1; i < steps; i++) {
        x += dx;
        double curr = f(x);
        ans += ((i & 1) ? 4 * curr : 2 * curr);
    }
    x += dx;
    ans += f(x);
    return ans * dx / 3.0;
}
