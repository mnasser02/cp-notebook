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
#define LSOne(S) ((S) & -(S))

void solve() {
    int n, q;
    cin >> n >> q;

    vector<vi> pre(n + 1, vi(n + 1));
    for (int i = 0; i < n; i++) {
        string forest;
        cin >> forest;
        for (int j = 0; j < n; j++) {
            if (forest[j] == '*') {
                pre[i + 1][j + 1] = 1;
            }
            pre[i + 1][j + 1] += pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
        }
    }
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, x2--, y1--, y2--;
        cout << pre[x2 + 1][y2 + 1] + pre[x1][y1] - pre[x2 + 1][y1] - pre[x1][y2 + 1] << "\n";
    }
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
