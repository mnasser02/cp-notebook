vi idl(n), idr(n);
int nleft = 0, nright = 0;
for (int u = 0; u < n; u++) {
    if (out[u]) idl[u] = nleft++;
}
for (int u = 0; u < n; u++) {
    if (in[u]) idr[u] = nleft + nright++;
}
for (int u = 0; u < n; u++) {
    for (int v : ALt[u]) {
        AL[idl[u]].push_back(idr[v]);
    }
}
// n - MCBM
