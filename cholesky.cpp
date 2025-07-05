// #include<iostream>
#include"bits/stdc++.h"
using namespace std;
using Matrix = vector<vector<double>>;

const int n=21;

Matrix criar_matriz_A() {
    Matrix A(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i][j] = (i == j) ? 0 : abs(i - j);
    return A;
}

void printMatrix(const Matrix& A, const string& nome) {
    cout << nome << ":\n";
    for (auto& row : A) {
        for (auto val : row) cout << fixed << setprecision(1) << setw(8) << val << " ";
        cout << "\n";
    }
    cout << endl;
}

int main()
{
    Matrix A = criar_matriz_A();
    for(int j = 0; j < n; j++) {
        // limpeza da coluna
        for(int i = j; i <n; i++) {

            double soma = 0.0;

            for(int k = 0; k < j; k++) {
                soma = soma + A[i][k]*A[j][k];
            }

            A[i][j] = A[i][j] - soma;
        }
        

        if(A[j][j] <= 0) {
            cout <<"A matriz não é definida positiva." << endl;
            printMatrix(A ,"A");
            break;
        }

        double diagonal_val = sqrt(A[j][j]);
        for(int i = j; i < n; i++) {
            A[i][j] = A[i][j]/diagonal_val;
        }
                
    }
}
