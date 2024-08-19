#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

const int N = 1e6 + 5;
ll dp[N] = {0};

void solve() {
    int n;
    cin >> n;
    vi x(n), cnt(N);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        cnt[x[i]]++;
    }

    for (int gd = N - 1; gd >= 1; gd--) {
        ll nb = 0;
        for (int d = gd; d < N; d += gd) {
            nb += cnt[d];
            if (d != gd)
                dp[gd] -= dp[d];
        }
        dp[gd] += nb * (nb - 1) / 2;
    }
    cout << dp[1] << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    // cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}
