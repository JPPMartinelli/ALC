#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<double>>;

const int n = 21;

// Cria matriz A como no código Python
Matrix criar_matriz_A() {
    Matrix A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = (i == j) ? 0 : abs(i - j);
    return A;
}

// Retorna matriz identidade nxn
Matrix identidade(int n) {
    Matrix I(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) I[i][i] = 1;
    return I;
}

// Multiplicação de matrizes
Matrix matmul(const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Transposta
Matrix transposta(const Matrix& A) {
    Matrix T(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = A[i][j];
    return T;
}

// Impressão
void imprimir(const Matrix& M, string nome) {
    cout << nome << ":\n";
    for (const auto& row : M) {
        for (double x : row)
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
    Matrix R = A;
    Matrix Q = identidade(n);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double a = R[i][i];
            double b = R[j][i];
            if (abs(b) < 1e-12) continue;

            double r = sqrt(a * a + b * b);
            double c = a / r;
            double s = -b / r;

            // Cria matriz de Givens G
            Matrix G = identidade(n);
            G[i][i] = c;
            G[j][j] = c;
            G[i][j] = -s;
            G[j][i] = s;

            R = matmul(G, R);
            Q = matmul(Q, transposta(G));
        }
    }

    imprimir(Q, "Q");
    imprimir(R, "R");

    Matrix QR = matmul(Q, R);
    cout << "\nQ @ R ≈ A? " << (aproximadamente_iguais(QR, A) ? "Sim" : "Não") << endl;

    return 0;
}
