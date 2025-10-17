vi get_pi(const string& s) {
    int n = s.size();
    vi pi(n);

    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}
int count_occurences(const string& T, const string& P) {
    vi pi = get_pi(P);
    int i = 0, j = 0, freq = 0;
    while (i < T.size()) {
        while (j > 0 && T[i] != P[j]) j = pi[j - 1];
        if (T[i] == P[j])
            j++;
        i++;
        if (j == P.size()) {
            freq++;
            j = pi[j - 1];
        }
    }
    return freq;
}
