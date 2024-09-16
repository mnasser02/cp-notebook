#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;
typedef pair<ll, ll> pll;
typedef vector<ii> vii;
typedef vector<ll> vll;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    int x, k, n, m;
    cin >> x >> k >> n >> m;
    vector<string> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    vector<vi> vis(n, vi(m));
    int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
    int sz = 0;
    auto dfs = [&](auto self, int r, int c) -> void {
        vis[r][c] = 1;
        sz++;
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m || vis[nr][nc] || A[nr][nc] != '.') continue;
            self(self, nr, nc);
        }
    };
    int ans = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (!vis[r][c] && A[r][c] == '.') {
                sz = 0;
                dfs(dfs, r, c);
                ans += sz / k;
            }
        }
    }
    cout << min(ans, x) * k << '\n';
}

int main() {
    freopen("zamalek.in", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0);

    int tc = 1;
    cin >> tc;

    while (tc--) {
        solve();
    }
    return 0;
}