// O(n^2)
for (int v = 1; v < N; v++) {
    for (int s = v; s < N; s++) {
        dp[s] += dp[s - v];
        dp[s] %= M;
    }
}
// O(n*sqrt(n))
dp[0] = dp[1] = 1;
for (int i = 2; i < N; i++) {
    dp[i] = 0;
    for (int j = 1; i > (ll)j * (3 * j - 1) / 2; j++) {
        int x = i - j * (3 * j - 1) / 2;
        int y = i - j * (3 * j + 1) / 2;
        if (j & 1) {
            dp[i] += dp[x];
            if (y > 0) dp[i] += dp[y];
        } else {
            dp[i] -= dp[x];
            if (y > 0) dp[i] -= dp[y];
        }
        dp[i] = (dp[i] + M) % M;
    }
}
