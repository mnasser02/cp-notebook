for (int i = 0; i < V; ++i)
    for (int j = 0; j < V; ++j)
        p[i][j] = i;
for (int k = 0; k < V; ++k)
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (AM[i][k] + AM[k][j] < AM[i][j]) {
                AM[i][j] = AM[i][k] + AM[k][j];
                p[i][j] = p[k][j];
            }

void print_path(int i, int j) {
    if (i != j) print_path(i, p[i][j]);
    printf(" %d", v);
}
