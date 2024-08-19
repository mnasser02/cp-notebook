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
    int n, m, k;
    cin >> n >> m >> k;

    vector<vi> AL(n);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        AL[u].push_back(v + n);
    }

    vi match(n + m, -1), vis;

    auto aug = [&](auto self, int L) -> bool {
        if (vis[L]) return 0;
        vis[L] = 1;
        for (int& R : AL[L])
            if ((match[R] == -1) || self(self, match[R])) {
                match[R] = L;
                return 1;
            }
        return 0;
    };

    set<int> freeV;
    for (int L = 0; L < n; ++L)
        freeV.insert(L);

    int MCBM = 0;

    for (int L = 0; L < n; ++L) {  // speedup
        vi candidates;
        for (int& R : AL[L])
            if (match[R] == -1)
                candidates.push_back(R);
        if (!candidates.empty()) {
            ++MCBM;
            freeV.erase(L);
            int a = rand() % (int)candidates.size();
            match[candidates[a]] = L;
        }
    }
    for (auto& f : freeV) {
        vis.assign(n, 0);
        MCBM += aug(aug, f);
    }

    cout << MCBM << "\n";
    for (int R = n; R < n + m; R++) {
        if (match[R] != -1) cout << match[R] + 1 << " " << R - n + 1 << "\n";
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