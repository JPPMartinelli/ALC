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
    for j in range(n):
        if j > i:
            a = R[i, i] #elemento da diagonal principal
            b = R[j, i] #elemento que queremos zerar
            r = np.sqrt(a**2 + b**2)
            c = a/r
            s = -b/r

            G = np.identity(n)
            G[i, i] = c
            G[j, j] = c
            G[i, j] = -s
            G[j, i] = s

            R = G @ R
            Q = Q @ G.T

print("Q:")
print(np.round(Q, 4))
print("\nR:")
print(np.round(R, 4))
print("\nQ @ R ≈ A?")
print(np.allclose(Q @ R, A))



