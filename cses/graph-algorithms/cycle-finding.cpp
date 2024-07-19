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
    vector<vii> AL(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        AL[u].push_back({v, w});
    }

    vll dist(n, 1e18);
    vi freq(n, 0), par(n, -1);
    vector<bool> in_queue(n);

    auto SPFA = [&](int u) {
        queue<int> q;
        q.push(u);
        dist[u] = 0;
        in_queue[u] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in_queue[u] = 0;
            for (auto& [v, w] : AL[u]) {
                if (dist[u] + w >= dist[v]) continue;
                dist[v] = dist[u] + w;
                par[v] = u;
                freq[v]++;
                if (freq[v] > n) {
                    cout << "YES\n";
                    vi ans;
                    int x = v;
                    stack<int> st;
                    vector<bool> in_st(n);
                    while (!in_st[x]) {
                        st.push(x);
                        in_st[x] = 1;
                        x = par[x];
                    }
                    cout << x + 1 << " ";
                    while (st.top() != x) {
                        cout << st.top() + 1 << " ";
                        st.pop();
                    }
                    cout << x + 1 << " ";
                    return 1;
                }
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = 1;
                }
            }
        }
        return 0;
    };

    for (int u = 0; u < n; u++) {
        if (dist[u] == 1e18) {
            if (SPFA(u)) {
                return;
            }
        }
    }
    cout << "NO";
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