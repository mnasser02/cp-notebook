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

const int N = 2e5 + 1;
vi AL[N];
int n, k1, k2;
ll ans;

int get_pre(deque<int>& a, int mx) {
    int n = a.size();
    if (mx < 0) return 0;
    if (mx + 1 >= n) return a[0];
    return a[0] - a[mx + 1];
}
void merge(deque<int>& a, deque<int>& b) {
    if (a.size() < b.size()) {
        swap(a, b);
    }
    int n = a.size(), m = b.size();
    for (int i = 0; i < m - 1; i++) {
        b[i] -= b[i + 1];
    }
    for (int i = 0; i < m; i++) {
        ans += (ll)b[i] * (get_pre(a, k2 - i) - get_pre(a, k1 - i - 1));
    }
    for (int i = m - 2; i >= 0; i--) b[i] += b[i + 1];
    for (int i = 0; i < m; i++) a[i] += b[i];
}
deque<int> dfs(int u, int p) {
    deque<int> res{1};
    for (int v : AL[u]) {
        if (v == p) continue;
        deque<int> cur = dfs(v, u);
        cur.push_front(cur.front());
        merge(res, cur);
    }
    return res;
}
void solve() {
    cin >> n >> k1 >> k2;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    dfs(0, -1);
    cout << ans << "\n";
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
