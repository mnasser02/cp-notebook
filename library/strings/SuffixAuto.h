// DAWG; use dp.
struct SuffixAuto {
    struct state {
        int len, link;
        int next[28];
        state() : len(0), link(-1) {
            memset(next, -1, sizeof next);
        }
    };

    state* st;
    int sz, last;

    SuffixAuto() : st(0) {}

    SuffixAuto(const string& s) {
        build(s);
    }

    void build(const string& s) {
        delete[] st;
        st = new state[2 * s.size()];

        last = 0;
        sz = 1;

        for (char c : s) {
            extend(c);
        }
    }

    void extend(char _c) {
        int c = _c - 'A';

        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        // cnt[cur] = 1;

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
                // cnt[clone] = 0;
                st[clone].len = st[p].len + 1;
                copy(st[q].next, st[q].next + 28, st[clone].next);
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
    ~SuffixAuto() { delete[] st; }
} sa;
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --int memo1[2 * N];
ll memo2[2 * N], memo3[2 * N];
// common substrings
int dp1(int u) {
    int& ans = memo1[u];
    if (~ans) return ans;
    ans = 0;
    for (int c = 0; c < 28; c++) {
        int v = sa.st[u].next[c];
        if (v == -1) continue;
        if (c == 26) {
            ans |= 1;
        } else if (c == 27)
            ans |= 2;
        else
            ans |= dp1(v);
    }
    return ans;
}
// number of distinct substrings (paths) starting at state u
ll dp2(int u) {
    if (dp1(u) != 3 || u == sa.last) return 0;
    ll& ans = memo2[u];
    if (~ans) return ans;
    ans = 1;
    for (int c = 0; c < 28; c++) {
        int v = sa.st[u].next[c];
        if (v == -1) continue;
        ans += dp2(v);
    }
    return ans;
}
ll dfs(int u) {
    if (dp1(u) != 3) return 0;
    ll& ans = memo3[u];
    if (~ans) return ans;
    if (u) {
        ll concat = (dp2(u) - 1 + M) % M;
        ans = concat % M * concat % M;
    } else
        ans = 0;
    for (int c = 0; c < 26; c++) {
        int v = sa.st[u].next[c];
        if (v == -1) continue;
        ans = (ans + dfs(v)) % M;
    }
    return ans;
}

// cnt[u]: nb of occurences of state u substrings (endpos size).
// uncomment: cnt[cur] = 1, cnt[clone] = 0
// case distinct: replace cnt by 1
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
// kth substring
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
vector<ii> v(2 * T.size());
for (int i = 0; i < v.size(); i++)
    v[i] = {sa.st[i].len, i};
sort(rall(v));
for (auto [len, id] : v)
    if (sa.st[id].link != -1)
        cnt[sa.st[id].link] += cnt[id];
cnt[0] = 1;

ll get_tot_len_diff_substings() {
    ll tot = 0;
    for (int i = 1; i < sz; i++) {
        ll shortest = sa.st[st[i].link].len + 1;
        ll longest = sa.st[i].len;

        ll num_strings = longest - shortest + 1;
        ll cur = num_strings * (longest + shortest) / 2;
        tot += cur;
    }
    return tot;
}
