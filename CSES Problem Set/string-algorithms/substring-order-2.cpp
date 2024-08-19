#include <bits/stdc++.h>

using namespace std;

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

const int N = 100010;
ll cnt[2 * N], dp[2 * N];

struct SuffixAuto {
    struct state {
        int len, link;
        int next[26];
        state() : len(0), link(-1) {
            memset(next, -1, sizeof next);
        }
    };

    state* st;
    int sz, last;

    SuffixAuto() : st(0) {}

    SuffixAuto(const string& s) {
        init(s);
    }

    void init(const string& s) {
        st = new state[2 * s.size()];

        sz = 1;
        last = 0;

        for (char c : s) {
            extend(c);
        }
    }

    void extend(char _c) {
        int c = _c - 'a';

        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;

        cnt[cur] = 1;  // added

        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;

                cnt[clone] = 0;  // added

                st[clone].len = st[p].len + 1;
                copy(st[q].next, st[q].next + 26, st[clone].next);
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
    ~SuffixAuto() {
        delete[] st;
    }
} sa;

ll dfs_dp(int u) {
    if (dp[u] != 0)
        return dp[u];
    for (int c = 0; c < 26; c++) {
        int v = sa.st[u].next[c];
        if (v != -1)
            dp[u] += dfs_dp(v);
    }
    return dp[u] += cnt[u];
}

string ans;
void dfs(int u, ll& k) {
    if (k < cnt[u])
        return;
    else
        k -= cnt[u];
    for (int c = 0; c < 26; c++) {
        int v = sa.st[u].next[c];
        if (v != -1) {
            if (k >= dp[v])
                k -= dp[v];
            else {
                ans += char(c + 'a');
                dfs(v, k);
                return;
            }
        }
    }
}

void solve() {
    string T;
    ll k;
    cin >> T >> k;

    sa.init(T);

    // added
    vector<ii> v(2 * T.size());
    for (int i = 0; i < v.size(); i++)
        v[i] = {sa.st[i].len, i};
    sort(rall(v));
    for (auto [len, id] : v)
        if (sa.st[id].link != -1)
            cnt[sa.st[id].link] += cnt[id];
    cnt[0] = 1;

    ans.clear();
    dfs_dp(0);
    dfs(0, k);

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