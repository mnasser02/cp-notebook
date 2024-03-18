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
int diam = 0;
int dfs(int u, int p) {
    int mx1 = -1, mx2 = -1;
    for (int v : AL[u]) {
        if (v == p) continue;
        int cur = dfs(v, u);
        if (cur > mx1) {
            mx2 = mx1;
            mx1 = cur;
        } else if (cur > mx2) {
            mx2 = cur;
        }
    }
    diam = max(diam, mx1 + mx2 + 2);
    return mx1 + 1;
}

void solve() {
    int n;
    cin >> n;
    AL.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }
    dfs(0, -1);
    cout << diam << "\n";
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
