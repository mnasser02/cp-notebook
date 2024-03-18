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

const int N = 1 << 18;
vi AL[N];
int ans[N], a[N];

set<int> dfs(int u, int p) {
    set<int> st{a[u]};

    for (int v : AL[u]) {
        if (v == p) continue;
        set<int> cur = move(dfs(v, u));
        if (cur.size() > st.size()) {
            swap(cur, st);
        }
        for (int x : cur) st.insert(x);
    }
    ans[u] = st.size();
    return st;
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    dfs(0, -1);
    for (int u = 0; u < n; u++) cout << ans[u] << " \n"[u == n - 1];
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
