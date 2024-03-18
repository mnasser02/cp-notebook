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
#define LSOne(S) ((S) & (-S))

void solve() {
    int n, q;
    cin >> n >> q;
    vi x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    vll pre(n + 1);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + x[i];
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << pre[b + 1] - pre[a] << "\n";
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
