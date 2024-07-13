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
    int n;
    cin >> n;
    vector<array<int, 3>> A(n);
    multiset<int> st, st2;
    for (int i = 0; i < n; i++) {
        cin >> A[i][0] >> A[i][1];
        st.insert(A[i][1]);
        A[i][2] = i;
    }
    st2 = st;
    sort(all(A), [](array<int, 3>& a, array<int, 3>& b) {
        if (a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    });

    vector<bool> s1(n), s2(n);
    for (auto [l, r, i] : A) {
        st.extract(r);
        if (!st.empty() && *st.begin() <= r) {
            s1[i] = 1;
        }
    }

    swap(st2, st);
    reverse(all(A));
    for (auto [l, r, i] : A) {
        st.extract(r);
        if (!st.empty() && *st.rbegin() >= r) {
            s2[i] = 1;
        }
    }

    for (int x : s1) cout << x << " ";
    cout << "\n";
    for (int x : s2) cout << x << " ";
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