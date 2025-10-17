// O(kE)
vi match, vis;

int aug(int L) {
    if (vis[L]) return 0;
    vis[L] = 1;
    for (auto& R : AL[L])
        if ((match[R] == -1) || aug(match[R])) {
            match[R] = L;
            return 1;
        }
    return 0;
}

unordered_set<int> freeV;
for (int L = 0; L < nleft; ++L)
    freeV.insert(L);  // initial assumption
match.assign(nleft + nright, -1);
int MCBM = 0;

for (int L = 0; L < nleft; ++L) {  // O(V+E)
    vi candidates;
    for (int& R : AL[L])
        if (match[R] == -1)
            candidates.push_back(R);
    if (!candidates.empty()) {
        ++MCBM;
        freeV.erase(L);
        int a = rand() % (int)candidates.size();
        match[candidates[a]] = L;
    }
}
for (auto& f : freeV) {
    vis.assign(nleft, 0);
    MCBM += aug(f);
}
