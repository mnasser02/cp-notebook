// O(n) | p[0][i]: even pal right center
//      | p[1][i]: odd pal center
// pal[x][l + len / 2] >= len / 2 -> [l, r] pal
vector<vi> manacher(string &s) {
    int n = s.size();
    vector<vi> p(2, vi(n, 0));
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++) {
            if (i < r) p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
            if (R > r) l = L, r = R;
        }
    return p;
}
