#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

int n = 21;

// Cria uma matriz identidade n x n
Matrix identidade(int n) {
    Matrix I(n, Vector(n, 0.0));
    for (int i = 0; i < n; i++) I[i][i] = 1.0;
    return I;
}

// Produto escalar entre dois vetores
double dot(const Vector& a, const Vector& b) {
    double s = 0;
    for (int i = 0; i < a.size(); ++i) s += a[i] * b[i];
    return s;
}

// Norma L2 de um vetor
double norm(const Vector& v) {
    return sqrt(dot(v, v));
}

// Produto externo v * v^T
Matrix outer(const Vector& v) {
    int n = v.size();
    Matrix result(n, Vector(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = v[i] * v[j];
    return result;
}

// Multiplicação de duas matrizes
Matrix matmul(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix result(n, Vector(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                result[i][j] += A[i][k] * B[k][j];
    return result;
}

// Transposta de uma matriz
Matrix transpose(const Matrix& A) {
    int n = A.size();
    Matrix T(n, Vector(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j];
    return T;
}

// Mostra uma matriz
void printMatrix(const Matrix& A, const string& nome) {
    cout << nome << ":\n";
    for (auto& row : A) {
        for (auto val : row) cout << fixed << setprecision(4) << setw(8) << val << " ";
        cout << "\n";
    }
    cout << endl;
}

int main() {
    Matrix A(n, Vector(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = (i == j) ? 0 : abs(i - j);

    Matrix R = A;
    Matrix Q = identidade(n);

    // Decomposição QR via Householder
    for (int k = 0; k < n; ++k) {
        Vector x(n - k);
        for (int i = k; i < n; ++i)
            x[i - k] = R[i][k];

        double alpha = -copysign(norm(x), x[0]);
        Vector e(n - k, 0.0); e[0] = 1.0;

        // vetor de relexão householder
        Vector v(n - k);
        for (int i = 0; i < n - k; ++i)
            v[i] = x[i] - alpha * e[i];
        double vnorm = norm(v);
        for (double& vi : v) vi /= vnorm;

        
        // H = I - 2 * (v * v^T)
        Matrix Hk = identidade(n);
        Matrix Hv = outer(v);
        for (int i = 0; i < n - k; ++i)
            for (int j = 0; j < n - k; ++j)
                Hk[i + k][j + k] -= 2.0 * Hv[i][j];

        R = matmul(Hk, R);
        Q = matmul(Q, transpose(Hk));
    }

    printMatrix(Q, "Q");
    printMatrix(R, "R");

    // Verifica se Q * R ≈ A
    Matrix QR = matmul(Q, R);
    bool igual = true;
    for (int i = 0; i < n && igual; ++i)
        for (int j = 0; j < n && igual; ++j)
            if (abs(QR[i][j] - A[i][j]) > 1e-6)
                igual = false;

    cout << "\nQ * R ≈ A? " << (igual ? "Sim" : "Não") << endl;

    return 0;
}
