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
Q = np.zeros((n, n))

for i in range(n):
    v = np.zeros(n)
    for j in range(n):
        v[j] = A[j, i]
    
    Q[:, i] = v
    for j in range(i):
        Q[:, i] -= np.dot(Q[:, i], Q[:, j])/np.dot(Q[:, j], Q[:, j]) * Q[:, j]
    
    Q[:, i] = Q[:, i] / np.linalg.norm(Q[:, i])

R = Q.T @ A

print("Q:")
print(np.round(Q, 4))
print("\nR:")
print(np.round(R, 4))
print("\nQ @ R ≈ A?")
print(np.allclose(Q @ R, A))
