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
using os_tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    string s;
    cin >> s;

    int dr[] = {0, 0, 1, -1}, dc[] = {1, -1, 0, 0};
    map<char, int> mp{{'R', 0}, {'L', 1}, {'D', 2}, {'U', 3}};

    bool vis[9][9];
    auto bruteforce = [&](auto self, int r, int c, int k) -> int {
        if (k == 48) {
            if (r == 7 && c == 1) {
                return 1;
            }
            return 0;
        }
        //   1
        // 0 1 0
        //   1
        if (vis[r - 1][c] && vis[r + 1][c] && !vis[r][c - 1] && !vis[r][c + 1]) return 0;
        if (!vis[r - 1][c] && !vis[r + 1][c] && vis[r][c - 1] && vis[r][c + 1]) return 0;

        int dist = 7 - r + c - 1;
        int rem = 48 - k;
        if (rem < dist) return 0;

        vis[r][c] = 1;
        int ans = 0;
        if (r == 7 && c == 1) {
            ans = 0;
        } else if (s[k] != '?') {
            int nr = dr[mp[s[k]]] + r;
            int nc = dc[mp[s[k]]] + c;

            if (vis[nr][nc])
                ans = 0;
            else {
                ans = self(self, nr, nc, k + 1);
            }
        } else {
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (vis[nr][nc]) continue;
                ans += self(self, nr, nc, k + 1);
            }
        }

        vis[r][c] = 0;
        return ans;
    };

    memset(vis, 0, sizeof vis);
    for (int i = 0; i < 9; i++) {
        vis[8][i] = vis[i][8] = vis[0][i] = vis[i][0] = 1;
    }

    cout << bruteforce(bruteforce, 1, 1, 0) << "\n";
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