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

const int N = 2e5 + 5;
vi AL[N];
int h1[N], h2[N], ans[N];

void dfs1(int u, int p) {
    h1[u] = h2[u] = 0;
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs1(v, u);
        if (h1[v] + 1 > h1[u]) {
            h2[u] = h1[u];
            h1[u] = h1[v] + 1;
        } else if (h1[v] + 1 > h2[u]) {
            h2[u] = h1[v] + 1;
        }
    }
}

void dfs2(int u, int p, int thru_p) {
    ans[u] = max(h1[u], thru_p);
    for (int v : AL[u]) {
        if (v == p) continue;
        if (h1[v] + 1 == h1[u]) {
            dfs2(v, u, max(thru_p, h2[u]) + 1);
        } else {
            dfs2(v, u, ans[u] + 1);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    dfs1(0, -1), dfs2(0, -1, 0);
    for (int u = 0; u < n; u++) cout << ans[u] << " ";
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
