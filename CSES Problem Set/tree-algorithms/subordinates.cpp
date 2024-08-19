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

vector<vi> AL;
vi sz;
void dfs(int u, int p) {
    for (int v : AL[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += 1 + sz[v];
    }
}
void solve() {
    int n;
    cin >> n;
    AL.assign(n, vi());
    sz.resize(n);
    for (int v = 1; v < n; v++) {
        int u;
        cin >> u;
        u--;
        AL[u].push_back(v);
    }
    dfs(0, -1);
    for (int x : sz) cout << x << " ";
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
