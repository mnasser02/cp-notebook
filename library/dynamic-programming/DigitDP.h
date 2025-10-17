ll mem[20][10][2][2];
string num;
ll dp(int i, int prev, int pref, int start) {
    if (i == num.size()) {
        return 1;
    }

    // current digit
    // previous digit
    // prefix same as prefix of num (whether you haven't gone below the actual num yet)
    // start: to check if we still have leading zeros
    // add other info if needed
    ll& ans = mem[i][prev][pref][start];
    if (ans != -1) return ans;

    int D = 9;
    if (pref) {
        D = num[i] - '0';
    }
    ans = 0;
    for (int d = 0; d <= D; d++) {
        int np = pref;
        int ns = start;
        if (d < D) np = 0;
        if (d) ns = 1;
        if (prev != d || !ns) {
            ans += dp(i + 1, d, np, ns);
        }
    }
    return ans;
}

ll solve(ll x) {
    num = to_string(x);
    memset(mem, -1, sizeof mem);
    return dp(0, 0, 1, 0);
}

void solve() {
    ll x, y;
    cin >> x >> y;
    cout << solve(y) - solve(x - 1) << "\n";
}
