#include <bits/stdc++.h>

using namespace std;

bitset<100001> dp;
// bool dp[100001];  // 2nd method

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        dp = dp | (dp << x[i]);
    }

    // dp[0] = 1;  // 2nd method
    // for (int i = 0; i < n; i++) {
    //     for (int s = 100001; s >= x[i]; s--) {
    //         dp[s] |= dp[s - x[i]];
    //     }
    // }

    vector<int> ans;
    for (int s = 1; s <= 100000; s++) {
        if (dp[s]) ans.push_back(s);
    }
    cout << ans.size() << "\n";
    for (int s : ans) cout << s << " ";
    return 0;
}
