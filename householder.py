import numpy as np

n=21
A = np.zeros((n, n))
for i in range(n):
    for j in range(n):
        if i == j:
            A[i,j] = 0
        elif i < j:
            A[i,j] = j-i
        else:
            A[i,j] = i-j

R = A.copy()
Q = np.identity(n)

for i in range(n):
    x = R[i:, i]  # subvetor da coluna i
    norma_x = np.linalg.norm(x)
    sinal = -1 if x[0] >= 0 else 1
    e = np.zeros_like(x)
    e[0] = 1

    v = x - sinal * norma_x * e
    v = v / np.linalg.norm(v)

    # matriz de Householder do tamanho reduzido
    H = np.identity(len(x)) - 2 * np.outer(v, v)

    # expandir para Hfull
    Hfull = np.identity(n)
    Hfull[i:, i:] = H

    R = Hfull @ R
    Q = Q @ Hfull.T

print("Q:")
print(np.round(Q, 4))
print("\nR:")
print(np.round(R, 4))
print("\nQ @ R ≈ A?")
print(np.allclose(Q @ R, A))

