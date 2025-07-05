#include <bits/stdc++.h>
using namespace std;

using Matrix = vector<vector<double>>;

const int n = 21; 

Matrix criar_matriz_A() {
    Matrix A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = (i == j) ? 0 : abs(i - j);
    return A;
}

int main() {
    Matrix A = criar_matriz_A();
    vector<double> b(n, 0.0);

    for (int i = 0; i<n; i++) {
        b[i] = i+1;
    }

    for (int i=0; i<n; i++) {
        double pivoAtual = fabs(A[i][i]);
        int coordenadaLinhaPivo = i;
        for (int j=i; j<n; j++) {
            if (fabs(A[j][i]) > fabs(pivoAtual)) {
                coordenadaLinhaPivo = j;
                pivoAtual = A[j][i];
            }
        }

        if (coordenadaLinhaPivo != i) {
            swap(A[i], A[coordenadaLinhaPivo]);
            swap(b[i], b[coordenadaLinhaPivo]);
        }

        for (int j = i+1; j<n; j++) {
            double M = A[j][i] / A[i][i];
            A[j][i] = 0.0;
            for (int k = i+1; k<n; k++) {
                A[j][k] -= M * A[i][k];
            }
            b[j] -= M * b[i];
        }
    }

    vector<double> solucao(n, 0.0);
    for (int i = n-1; i >= 0; --i) {
        double s = b[i];
        for (int j = i+1; j < n; ++j) {
            s -= A[i][j] * solucao[j];
        }
        solucao[i] = s / A[i][i];
    }
    for (int i = 0; i < n; i++) {
        cout << "solucao[" << i << "] = " << fixed << setprecision(18) << solucao[i] << endl;
    }
}
