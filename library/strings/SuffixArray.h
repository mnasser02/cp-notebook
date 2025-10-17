struct SuffixArray {
    vi sa, lcp;
    string s;
    // vector<vi> C;

    void build(string& s_) {
        s = s_;
        // C.clear();
        sa = suffix_array_construction(s);
        lcp = lcp_construction(s);
    }

    vi suffix_array_construction(string s) {
        s += "$";
        vi sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    vi sort_cyclic_shifts(string& s) {
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
        // C.push_back(c);
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
            swap(c, cn);
            // C.push_back(c);
        }

        return p;
    }

    vi lcp_construction(string& s) {
        int n = s.size();
        vi rank(n, 0);
        for (int i = 0; i < n; i++)
            rank[sa[i]] = i;

        int k = 0;
        vi lcp(n - 1, 0);
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }

    ii string_matching(string& p) {
        int n = s.size();
        int l = 0, r = n - 1;
        int lb = n, ub = n;
        while (l <= r) {
            int m = l + r >> 1;
            string sub = s.substr(sa[m], (int)p.size());
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
            string sub = s.substr(sa[m], (int)p.size());
            if (sub > p) {
                ub = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return {lb, ub};
    }

    /*int compare(int i, int j, int l) {
        int n = s.size(), k = lg2[l];
        pair<int, int> a = {C[k][i], C[k][(i + l - (1 << k)) % n]};
        pair<int, int> b = {C[k][j], C[k][(j + l - (1 << k)) % n]};
        return a == b ? 0 : a < b ? -1
                                  : 1;
    }*/
};
