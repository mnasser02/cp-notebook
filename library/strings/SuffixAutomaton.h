/**
 * string S, substring t of S
 * DFA that accepts all suffixes of S (only)
 * endpos(t) = {positions of S ending in t}
 *     - a state corresponds to an equivalence class of endpos
 *     - 2 non-empty strings u, w with len(u) <= len(w)
 *         + are endpos-equiv iff u occurs in S only as a suffix of w
 *         + endpos(w) \subseteq endpos(u) if u suffix of w else they're disjoint
 *     - in an equiv class (state v), shorter substrings are suffixes of longer ones and take all possible lengths in some [minlen(v), len(v)]
 * v state, w = longest(v), link(v) = longest suffix of w in another equiv class
 *     - suffix links form a tree with root t0, with inclusion relationship b/w sets of endpos
 *     - minlen(v) = len(link(v)) + 1
 *     - v -> t0 seq of disjoint intervals, in union [0, len(v)]
 * a substring corresponds to a path from t0 and vice versa
 *
 **/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int K = 26;
const char C = 'a';
struct SuffixAuto {
    struct state {
        int len, link;
        vector<int> next;
        state() : len(0), link(-1), next(K, -1) {}
    };

    int n;
    const string& S;
    vector<state> st;
    int sz, last;
    // optional
    vector<int> firstpos, cnt;  // firstpos <-> min(endpos), cnt <-> endpos_size

    SuffixAuto(const string& S_) : S(S_) {
        n = S.size();
        st.resize(2 * n);

        st[0].len = 0;
        st[0].link = -1;
        last = 0;
        sz = 1;

        cnt.resize(2 * n);
        firstpos.resize(2 * n);
        for (char c : S) {
            extend(c);
        }

        vector<pair<int, int>> v(2 * S.size());
        for (int i = 0; i < v.size(); i++)
            v[i] = {st[i].len, i};
        sort(v.rbegin(), v.rend());
        for (auto [len, id] : v)
            if (st[id].link != -1)
                cnt[st[id].link] += cnt[id];
        cnt[0] = 1;
    }

    void extend(char c_) {
        int c = c_ - C;

        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        cnt[cur] = 1;
        firstpos[cur] = st[cur].len - 1;

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
                cnt[clone] = 0;
                firstpos[clone] = firstpos[q];
                st[clone].len = st[p].len + 1;
                st[clone].link = st[q].link;
                st[clone].next = st[q].next;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // applications
    ll get_diff_strings() {
        ll tot = 0;
        for (int i = 1; i < sz; i++) {
            tot += st[i].len - st[st[i].link].len;
        }
        return tot;
    }

    ll get_tot_len_diff_substings() {
        ll tot = 0;
        for (int i = 1; i < sz; i++) {
            ll shortest = st[st[i].link].len + 1;
            ll longest = st[i].len;

            ll num_strings = longest - shortest + 1;
            ll cur = num_strings * (longest + shortest) / 2;
            tot += cur;
        }
        return tot;
    }

    int first_match(const string& P) {
        int cur = 0;
        for (char c_ : P) {
            int c = c_ - C;
            if (st[cur].next[c] == -1) return -1;

            cur = st[cur].next[c];
        }
        return firstpos[cur] - P.size() + 1;
    }

    string lcs(const string& T) {
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < T.size(); i++) {
            int c = T[i] - C;
            while (v && st[v].next[c] == -1) {
                v = st[v].link;
                l = st[v].len;
            }
            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                l++;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        return T.substr(bestpos - best + 1, best);
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
        return ++dp[u];  // *if not-distinct: dp += cnt*
    }
    void dfs(int u, ll& k, string& s) {
        if (k == 0)  // empty string starting from u. *if not-distinct: k<cnt*
            return;
        k--;  // remove empty string. *if not-distinct: k -= cnt*
        for (int c = 0; c < K; c++) {
            int v = st[u].next[c];
            if (v == -1) continue;
            if (k >= dp[v])
                k -= dp[v];
            else {
                s += char(c + C);
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

    string longest_repeating() {
        int best_len = -1, bfp = -1;

        for (int u = 1; u < 2 * n; u++) {
            if (cnt[u] <= 1 || st[u].len == 0) continue;
            int len = st[u].len;
            if (len > best_len) {
                best_len = len;
                bfp = firstpos[u];
            }
        }
        if (best_len == -1) return "-1";
        return S.substr(bfp - best_len + 1, best_len);
    }

    string shortest_unique() {
        int best_len = 1e9, bfp = 1e9;

        for (int u = 1; u < 2 * n; u++) {
            if (cnt[u] > 1 || st[u].len == 0) continue;
            int mn_len = st[st[u].link].len + 1;
            if (mn_len < best_len) {
                best_len = mn_len;
                bfp = firstpos[u];
            } else if (mn_len == best_len && firstpos[u] < bfp) {
                bfp = firstpos[u];
            }
        }

        return S.substr(bfp - best_len + 1, best_len);
    }
};