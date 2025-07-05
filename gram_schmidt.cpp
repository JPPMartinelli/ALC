#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<double>>;

const int n = 21;

// Cria a matriz A como no Python
Matrix criar_matriz_A() {
    Matrix A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = (i == j) ? 0 : abs(i - j);
    return A;
}

// Transposta de uma matriz
Matrix transposta(const Matrix& A) {
    Matrix T(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j];
    return T;
}

// Produto de matrizes
Matrix matmul(const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Produto interno entre dois vetores coluna
double dot(const vector<double>& a, const vector<double>& b) {
    double soma = 0;
    for (int i = 0; i < n; ++i)
        soma += a[i] * b[i];
    return soma;
}

// Norma 2 de um vetor
double norma(const vector<double>& v) {
    return sqrt(dot(v, v));
}

// Impressão de matriz
void imprimir(const Matrix& M, string nome) {
    cout << nome << ":\n";
    for (const auto& linha : M) {
        for (double x : linha)
            cout << setw(8) << fixed << setprecision(4) << x << " ";
        cout << "\n";
    }
    cout << "\n";
}

// Verifica se duas matrizes são aproximadamente iguais
bool aproximadamente_iguais(const Matrix& A, const Matrix& B, double eps = 1e-6) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (abs(A[i][j] - B[i][j]) > eps)
                return false;
    return true;
}

int main() {
    Matrix A = criar_matriz_A();
    Matrix Q(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        vector<double> v(n);
        for (int j = 0; j < n; ++j)
            v[j] = A[j][i];  // coluna i de A

        for (int j = 0; j < i; ++j) {
            // proj = v - (dot(v, q)/dot(q, q)) * q ... 
            double proj = dot(v, Q[j]) / dot(Q[j], Q[j]);
            for (int k = 0; k < n; ++k)
                v[k] -= proj * Q[j][k];
        }

        double norm_v = norma(v);
        for (int k = 0; k < n; ++k)
            Q[i][k] = v[k] / norm_v;
    }

    Matrix Qt(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            Qt[j][i] = Q[i][j];

    Matrix R = matmul(transposta(Qt), A);

    imprimir(Qt, "Q");
    imprimir(R, "R");

    Matrix QR = matmul(Qt, R);
    cout << "\nQ @ R ≈ A? " << (aproximadamente_iguais(QR, A) ? "Sim" : "Não") << endl;

    return 0;
}
