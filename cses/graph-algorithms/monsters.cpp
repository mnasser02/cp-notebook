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
    int n, m;
    cin >> n >> m;
    vector<string> A(n);

    queue<ii> q;
    vector<vi> dist(n, vi(m, 1e9));
    vector<vector<iii>> par(n, vector<iii>(m));
    int r1, c1;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 'A') {
                dist[i][j] = 0;
                r1 = i, c1 = j;
                q.push({i, j});
            } else if (A[i][j] == 'M') {
                q.push({i, j});
                dist[i][j] = 0;
            }
        }
    }
    int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
    int r2, c2;
    int ans = 1e9;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (A[r][c] == 'A') {
            if (r * c == 0 || r == n - 1 || c == m - 1) {
                r2 = r, c2 = c;
                ans = dist[r2][c2];
                break;
            }
        }
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];

            if (nr < 0 || nc < 0 || nr >= n || nc >= m || A[nr][nc] == '#') continue;
            int new_d = dist[r][c] + 1;
            if (new_d > dist[nr][nc]) continue;

            if (A[r][c] == 'A' && A[nr][nc] != 'M')
                A[nr][nc] = 'A';
            else
                A[nr][nc] = 'M';

            if (new_d < dist[nr][nc]) {
                par[nr][nc] = {r, c, i};
                dist[nr][nc] = new_d;
                q.push({nr, nc});
            }
        }
    }

    if (ans == 1e9) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n"
         << ans << "\n";
    auto path = [&](auto self, int r, int c) -> void {
        if (r == r1 && c == c1) return;
        int i;
        tie(r, c, i) = par[r][c];
        self(self, r, c);
        char x;
        if (i == 0) {
            x = 'R';
        } else if (i == 1) {
            x = 'L';
        } else if (i == 2) {
            x = 'D';
        } else {
            x = 'U';
        }
        cout << x;
    };
    path(path, r2, c2);
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