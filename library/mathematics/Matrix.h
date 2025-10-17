template <class T>
struct Matrix {
    vector<vector<T>> A;
    int n;
    bool e;
    Matrix(int n_, bool e = 0) : A(n_, vector<T>(n_)), n(n_), e(e) {}
    T& operator()(int i, int j) { return A[i][j]; }
    Matrix operator*(Matrix oth) {
        if (e) return oth;
        if (oth.e) return *this;
        Matrix ans(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ans(i, j) += A[i][k] * oth(k, j) % M;
                    ans(i, j) %= M;
                }                                                                                   
            }
        }
        return ans;
    }
};
// Solving System of Linear Equations
const double EPS = 1e-9;
const int INF = 2;
// O(min(n, m) * nm)
int gauss(vector<vector<double>> a, vector<double>& ans) {
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vi where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < EPS)
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
// General Matrix Operations
struct Matrix {
    int n, m;
    vector<vector<double>> v;

    Matrix() {}
    Matrix(const vector<vector<double>>& _v) : n(_v.size()), m(_v[0].size()), v(_v) {}

    Matrix operator*(const Matrix& b) const {
        assert(m == b.n);
        Matrix res;
        res.n = n, res.m = b.m;
        for (int i = 0; i < res.n; i++) {
            for (int j = 0; j < res.m; j++) {
                for (int k = 0; k < m; k++) {
                    res.v[i][j] += v[i][k] * b.v[k][j];
                    res.v[i][j] %= M;
                }
            }
        }
        return res;
    }
    double determinant() {  // O(n^3)
        double det = 1;
        for (int i = 0; i < n; ++i) {
            int k = i;
            for (int j = i + 1; j < n; ++j)
                if (abs(v[j][i]) > abs(v[k][i]))
                    k = j;
            if (abs(v[k][i]) < EPS) {
                det = 0;
                break;
            }
            swap(v[i], v[k]);
            if (i != k)
                det = -det;
            det *= v[i][i];
            for (int j = i + 1; j < n; ++j)
                v[i][j] /= v[i][i];
            for (int j = 0; j < n; ++j)
                if (j != i && abs(v[j][i]) > EPS)
                    for (int k = i + 1; k < n; ++k)
                        v[j][k] -= v[i][k] * v[j][i];
        }
    }

    int rank() {  // O(n^3)
        int n = v.size();
        int m = v[0].size();

        int rank = 0;
        vector<bool> row_selected(n, false);
        for (int i = 0; i < m; ++i) {
            int j;
            for (j = 0; j < n; ++j) {
                if (!row_selected[j] && abs(v[j][i]) > EPS)
                    break;
            }

            if (j != n) {
                ++rank;
                row_selected[j] = true;
                for (int p = i + 1; p < m; ++p)
                    v[j][p] /= v[j][i];
                for (int k = 0; k < n; ++k) {
                    if (k != j && abs(v[k][i]) > EPS) {
                        for (int p = i + 1; p < m; ++p)
                            v[k][p] -= v[j][p] * v[k][i];
                    }
                }
            }
        }
        return rank;
    }
};
