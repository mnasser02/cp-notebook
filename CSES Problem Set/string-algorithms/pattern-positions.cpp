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

vi sort_cyclic_shifts(string const &s) {
    int n = s.size();
    vi p(n), c(n), cnt(max(256, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < 256; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i - 1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    vi pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            ii cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            ii prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }

    return p;
}
vi suffix_array_construction(string s) {
    s += "$";
    vi sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

const int LOG = 18, MXN = 200'005;
int stable[MXN][LOG];

int query(int L, int R) {
    int length = R - L + 1;
    int k = 31 - __builtin_clz(length);
    return min(stable[L][k], stable[R - (1 << k) + 1][k]);
}

void solve() {
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    vi SA = suffix_array_construction(s);

    for (int i = 0; i < n; i++) {
        stable[i][0] = SA[i];
    }
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; i++) {
            stable[i][k] = min(stable[i][k - 1], stable[i + (1 << (k - 1))][k - 1]);
        }
    }

    while (q--) {
        string p;
        cin >> p;

        int l = 0, r = n - 1, ans = -1;
        int lb = n, ub = n;
        while (l <= r) {
            int m = l + r >> 1;
            string sub = s.substr(SA[m], p.size());
            if (sub >= p) {
                lb = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        l = 0, r = n - 1;
        while (l <= r) {
            int m = l + r >> 1;
            string sub = s.substr(SA[m], p.size());
            if (sub > p) {
                ub = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        if (lb != ub) {
            ans = query(lb, ub - 1) + 1;
        }
        cout << ans << "\n";
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
