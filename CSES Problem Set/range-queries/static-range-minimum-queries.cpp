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

const int LOG = 18, MXN = 200'005;
int st[MXN][LOG];

int query(int L, int R) {
    int length = R - L + 1;
    int k = 31 - __builtin_clz(length);
    return min(st[L][k], st[R - (1 << k) + 1][k]);
}
void solve() {
    int n, q;
    cin >> n >> q;
    vi x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        st[i][0] = x[i];
    }
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
        }
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << query(a, b) << "\n";
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
