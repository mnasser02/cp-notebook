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
    int r1, c1, r2, c2;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 'A') {
                r1 = i, c1 = j;
            }
            if (A[i][j] == 'B') {
                r2 = i, c2 = j;
            }
        }
    }
    queue<ii> q;
    vector<vi> dist(n, vi(m, -1));
    vector<vector<iii>> par(n, vector<iii>(m));

    q.push({r1, c1}), dist[r1][c1] = 0;

    int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nc < 0 || nr >= n || nc >= m || A[nr][nc] == '#' || dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            par[nr][nc] = {r, c, i};
            q.push({nr, nc});
        }
    }
    if (dist[r2][c2] == -1) {
        cout << "NO\n";
        return;
    }
    string path;
    int r = r2, c = c2, i;
    while (r != r1 || c != c1) {
        tie(r, c, i) = par[r][c];
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
        path.push_back(x);
    }
    reverse(all(path));
    cout << "YES\n"
         << dist[r2][c2] << "\n"
         << path << "\n";
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