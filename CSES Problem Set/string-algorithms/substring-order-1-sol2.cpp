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
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> os_tree;
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define LSOne(S) ((S) & -(S))

const int K = 26;
const char X = 'a';
struct SuffixAuto {
    struct state {
        int len, link;
        vector<int> next;
        state() : len(0), link(-1), next(K, -1) {}
    };

    int n;
    vector<state> st;
    int sz, last;

    SuffixAuto(const string& S) {
        n = S.size();
        st.resize(2 * n);

        st[0].len = 0;
        st[0].link = -1;
        last = 0;
        sz = 1;

        for (char c : S) {
            extend(c);
        }
    }

    void extend(char _c) {
        int c = _c - X;

        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;

        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[q].len == st[p].len + 1) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    vector<ll> dp;
    ll dfs_dp(int u) {
        if (dp[u] != 0)
            return dp[u];
        for (int c = 0; c < K; c++) {
            int v = st[u].next[c];
            if (v != -1)
                dp[u] += dfs_dp(v);
        }
        return ++dp[u];
    }
    void dfs(int u, ll& k, string& s) {
        if (k == 0)  // empty string starting from u
            return;
        k--;  // remove empty string
        for (int c = 0; c < K; c++) {
            int v = st[u].next[c];
            if (v == -1) continue;
            if (k >= dp[v])
                k -= dp[v];
            else {
                s += char(c + X);
                dfs(v, k, s);
                return;
            }
        }
    }
    string kth_distinct_substring(ll k) {
        dp.resize(2 * n);
        string s;
        dfs_dp(0);
        dfs(0, k, s);
        return s;
    }
};

void solve() {
    string T;
    ll k;
    cin >> T >> k;

    SuffixAuto sa(T);
    cout << sa.kth_distinct_substring(k);
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