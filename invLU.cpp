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

void printMatrix(const Matrix& A, const string& nome) {
    cout << nome << ":\n";
    for (auto& row : A) {
        for (auto val : row) cout << fixed << setprecision(18) << setw(8) << val << " ";
        cout << "\n";
    }
    cout << endl;
}

struct Troca {
    int colunaA;
    int colunaB;
};


vector<double> decLU(Matrix& A, vector<double>& b) {
    vector<Troca> trocas;

    double M = 0.0;
    for (int k = 0; k < n - 1; k++){

        double pivoAtual = fabs(A[k][k]);
        int coordenadaLinhaPivo = k;
        int coordenadaColunaPivo = k;
        
        for (int x = k; x < n; x++){
            for (int y = k; y < n; y++){
                if (fabs(A[x][y]) > fabs(pivoAtual)){
                    coordenadaLinhaPivo = x;
                    coordenadaColunaPivo = y;
                    pivoAtual = A[x][y];
                }
            }
        }

        if (coordenadaLinhaPivo != k){
            swap(A[k], A[coordenadaLinhaPivo]);
            swap(b[k], b[coordenadaLinhaPivo]);
        } 

        if(coordenadaColunaPivo != k){
            for(int x = 0; x < n; x++){
                swap(A[x][coordenadaColunaPivo], A[x][k]);
            }
            Troca atual = {coordenadaColunaPivo, k};
            trocas.push_back(atual); 
        }

        for (int i = k+1; i < n; i++){ 
            M = A[i][k] / A[k][k];
            A[i][k] = M;
            for (int j = k+1; j < n; j++){
                A[i][j] = A[i][j] - (M * A[k][j]);
            }
        }
    }

    

    // foward substitution
    vector<double> y (n, 0.0);
    double soma = 0.0;
    for (int k = 0; k <= n-1; k++){
        soma = b[k];
        for (int j = 0; j < k; j++){
            soma = soma - (A[k][j] * y[j]);
        }
        y[k] = soma;
    }


    // back substitution
    vector<double> solucao (n, 0.0);
    soma = 0.0;
    for (int k = n - 1; k >= 0; k--){
        soma = y[k];
        for (int j = k + 1; j < n; j++){
            soma = soma - (A[k][j] * solucao[j]);
        }
        solucao[k] = soma / A[k][k];
    }

    for (int i = trocas.size() - 1; i >= 0; i--){
        swap(solucao[trocas[i].colunaA], solucao[trocas[i].colunaB]);
    }

    return solucao;
    
}

int main()
{
    Matrix A = criar_matriz_A();
    Matrix inv(n, vector<double>(n, 0.0));

    for (int i=0; i<n; i++){
        vector<double> e(n, 0.0);
        e[i] = 1.0;
        Matrix A_copia(A);
        vector<double> colunaj = decLU(A_copia, e);
        for (int j=0; j<n; j++) {
            inv[j][i] = colunaj[j];
        }
    }

    printMatrix(inv, "A");
}
