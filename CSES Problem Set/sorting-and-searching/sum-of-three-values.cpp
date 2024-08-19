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
    int n, x;
    cin >> n >> x;
    vector<array<int, 2>> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i][0];
        A[i][1] = i + 1;
    }
    sort(all(A));
    for (int i = 0; i < n; i++) {
        int y = x - A[i][0];
        int l = 0, r = n - 1;
        array<int, 3> ans{A[i][1]};
        while (l < r) {
            if (l == i)
                l++;
            else if (r == i)
                r--;
            else {
                int cur = A[l][0] + A[r][0];
                if (cur < y) {
                    l++;
                } else if (cur > y) {
                    r--;
                } else {
                    ans[1] = A[l][1];
                    ans[2] = A[r][1];
                    sort(all(ans));
                    for (int x : ans) cout << x << " ";
                    return;
                }
            }
        }
    }
    cout << "IMPOSSIBLE\n";
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