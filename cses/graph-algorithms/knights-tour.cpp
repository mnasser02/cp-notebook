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
    int x, y;
    cin >> x >> y;
    x--, y--;
    int dr[] = {1, 1, -1, -1, 2, 2, -2, -2};
    int dc[] = {2, -2, 2, -2, 1, -1, 1, -1};

    vector<vi> deg(8, vi(8));
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            for (int i = 0; i < 8; i++) {
                int nr = r + dr[i], nc = c + dc[i];
                if (nr < 0 || nc < 0 || nr >= 8 || nc >= 8) continue;
                deg[r][c]++;
            }
        }
    }

    vector<vi> A(8, vi(8));
    auto dfs = [&](auto self, int r, int c, int timer) -> bool {
        A[r][c] = timer;
        if (timer == 64) return 1;

        vector<array<int, 3>> v;
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr < 0 || nc < 0 || nr >= 8 || nc >= 8 || A[nr][nc]) continue;
            deg[nr][nc]--;
            v.push_back({deg[nr][nc], nr, nc});
        }

        sort(all(v));
        for (auto [d, nr, nc] : v) {
            if (self(self, nr, nc, timer + 1)) return 1;
        }
        A[r][c] = 0;
        return 0;
    };

    dfs(dfs, y, x, 1);

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) cout << A[r][c] << " ";
        cout << "\n";
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