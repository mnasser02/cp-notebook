ll eval(pll l, ll x) {
    auto [a, b] = l;
    return a * x + b;
}
ll inter_x(pll l1, pll l2) {
    auto [a1, b1] = l1;
    auto [a2, b2] = l2;
    return (b2 - b1) / (a1 - a2);
}
// decreasing x, decreasing slopes, max query
int m = dq.size();
while (m >= 2 && eval(dq[m - 1], x) <= eval(dq[m - 2], x)) {
    dq.pop_back();
    m--;
}
dp[i] = ... + eval(dq.back(), x);
pll cur = {a, b};
while (m >= 2 && inter_x(cur, dq[0]) >= inter_x(dq[0], dq[1])) {
    dq.pop_front();
    m--;
}
dq.push_front(cur);
