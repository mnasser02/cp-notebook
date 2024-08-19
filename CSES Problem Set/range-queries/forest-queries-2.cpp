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

const int N = 1024;
int stree[2 * N][2 * N], a[N][N];

void build_y(int px, int lx, int rx, int py, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            stree[px][py] = a[lx][ly];
        } else {
            stree[px][py] = stree[px << 1][py] + stree[px << 1 | 1][py];
        }
    } else {
        int my = ly + ry >> 1;
        build_y(px, lx, rx, py << 1, ly, my);
        build_y(px, lx, rx, py << 1 | 1, my + 1, ry);
        stree[px][py] = stree[px][py << 1] + stree[px][py << 1 | 1];
    }
}

void build_x(int px, int lx, int rx) {
    if (lx != rx) {
        int mx = lx + rx >> 1;
        build_x(px << 1, lx, mx);
        build_x(px << 1 | 1, mx + 1, rx);
    }
    build_y(px, lx, rx, 1, 0, N - 1);
}

int query_y(int px, int py, int ly, int ry, int i2, int j2) {
    if (i2 <= ly && ry <= j2) {
        return stree[px][py];
    }
    if (ry < i2 || ly > j2) {
        return 0;
    }
    int my = ly + ry >> 1;
    return query_y(px, py << 1, ly, my, i2, j2) + query_y(px, py << 1 | 1, my + 1, ry, i2, j2);
}

int query_x(int px, int lx, int rx, int i1, int j1, int i2, int j2) {
    if (i1 <= lx && rx <= j1) {
        return query_y(px, 1, 0, N - 1, i2, j2);
    }
    if (rx < i1 || lx > j1) {
        return 0;
    }
    int mx = lx + rx >> 1;
    return query_x(px << 1, lx, mx, i1, j1, i2, j2) + query_x(px << 1 | 1, mx + 1, rx, i1, j1, i2, j2);
}
void update_y(int px, int lx, int rx, int py, int ly, int ry, int x, int y, int v) {
    if (ly == ry) {
        if (lx == rx) {
            stree[px][py] = v;
        } else {
            stree[px][py] = stree[px << 1][py] + stree[px << 1 | 1][py];
        }
    } else {
        int my = ly + ry >> 1;
        if (y <= my)
            update_y(px, lx, rx, py << 1, ly, my, x, y, v);
        else
            update_y(px, lx, rx, py << 1 | 1, my + 1, ry, x, y, v);
        stree[px][py] = stree[px][py << 1] + stree[px][py << 1 | 1];
    }
}
void update_x(int px, int lx, int rx, int x, int y, int v) {
    if (lx != rx) {
        int mx = lx + rx >> 1;
        if (x <= mx)
            update_x(px << 1, lx, mx, x, y, v);
        else
            update_x(px << 1 | 1, mx + 1, rx, x, y, v);
    }
    update_y(px, lx, rx, 1, 0, N - 1, x, y, v);
}

void solve() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '*') {
                a[i][j] = 1;
            }
        }
    }
    build_x(1, 0, N - 1);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            a[x][y] ^= 1;
            update_x(1, 0, N - 1, x, y, a[x][y]);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            cout << query_x(1, 0, N - 1, x1, x2, y1, y2) << "\n";
        }
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
