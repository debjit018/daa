#include <stdio.h>
#include <stdlib.h>

void strassen(int **A, int **B, int **C, int n);
void add(int **A, int **B, int **C, int n);
void subtract(int **A, int **B, int **C, int n);

int main() {
    int n;
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    // Dynamic memory allocation for matrices
    int **A = (int **)calloc(n, sizeof(int *));
    int **B = (int **)calloc(n, sizeof(int *));
    int **C = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = (int *)calloc(n, sizeof(int));
        B[i] = (int *)calloc(n, sizeof(int));
        C[i] = (int *)calloc(n, sizeof(int));
    }

    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(A, B, C, n);

    printf("Resulting matrix C after multiplication:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}

void strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int new_size = n / 2;
    int **A11 = (int **)calloc(new_size, sizeof(int *));
    int **A12 = (int **)calloc(new_size, sizeof(int *));
    int **A21 = (int **)calloc(new_size, sizeof(int *));
    int **A22 = (int **)calloc(new_size, sizeof(int *));
    int **B11 = (int **)calloc(new_size, sizeof(int *));
    int **B12 = (int **)calloc(new_size, sizeof(int *));
    int **B21 = (int **)calloc(new_size, sizeof(int *));
    int **B22 = (int **)calloc(new_size, sizeof(int *));
    int **C11 = (int **)calloc(new_size, sizeof(int *));
    int **C12 = (int **)calloc(new_size, sizeof(int *));
    int **C21 = (int **)calloc(new_size, sizeof(int *));
    int **C22 = (int **)calloc(new_size, sizeof(int *));
    int **M1 = (int **)calloc(new_size, sizeof(int *));
    int **M2 = (int **)calloc(new_size, sizeof(int *));
    int **M3 = (int **)calloc(new_size, sizeof(int *));
    int **M4 = (int **)calloc(new_size, sizeof(int *));
    int **M5 = (int **)calloc(new_size, sizeof(int *));
    int **M6 = (int **)calloc(new_size, sizeof(int *));
    int **M7 = (int **)calloc(new_size, sizeof(int *));
    int **AResult = (int **)calloc(new_size, sizeof(int *));
    int **BResult = (int **)calloc(new_size, sizeof(int *));
    
    for (int i = 0; i < new_size; i++) {
        A11[i] = (int *)calloc(new_size, sizeof(int));
        A12[i] = (int *)calloc(new_size, sizeof(int));
        A21[i] = (int *)calloc(new_size, sizeof(int));
        A22[i] = (int *)calloc(new_size, sizeof(int));
        B11[i] = (int *)calloc(new_size, sizeof(int));
        B12[i] = (int *)calloc(new_size, sizeof(int));
        B21[i] = (int *)calloc(new_size, sizeof(int));
        B22[i] = (int *)calloc(new_size, sizeof(int));
        C11[i] = (int *)calloc(new_size, sizeof(int));
        C12[i] = (int *)calloc(new_size, sizeof(int));
        C21[i] = (int *)calloc(new_size, sizeof(int));
        C22[i] = (int *)calloc(new_size, sizeof(int));
        M1[i] = (int *)calloc(new_size, sizeof(int));
        M2[i] = (int *)calloc(new_size, sizeof(int));
        M3[i] = (int *)calloc(new_size, sizeof(int));
        M4[i] = (int *)calloc(new_size, sizeof(int));
        M5[i] = (int *)calloc(new_size, sizeof(int));
        M6[i] = (int *)calloc(new_size, sizeof(int));
        M7[i] = (int *)calloc(new_size, sizeof(int));
        AResult[i] = (int *)calloc(new_size, sizeof(int));
        BResult[i] = (int *)calloc(new_size, sizeof(int));
    }

    // Split matrices A and B into submatrices
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_size];
            A21[i][j] = A[i + new_size][j];
            A22[i][j] = A[i + new_size][j + new_size];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_size];
            B21[i][j] = B[i + new_size][j];
            B22[i][j] = B[i + new_size][j + new_size];
        }
    }

    // Implement Strassen's algorithm
    add(A11, A22, AResult, new_size);
    add(B11, B22, BResult, new_size);
    strassen(AResult, BResult, M1, new_size);
    
    add(A21, A22, AResult, new_size);
    strassen(AResult, B11, M2, new_size);

    subtract(B12, B22, BResult, new_size);
    strassen(A11, BResult, M3, new_size);

    subtract(B21, B11, BResult, new_size);
    strassen(A22, BResult, M4, new_size);

    add(A11, A12, AResult, new_size);
    strassen(AResult, B22, M5, new_size);

    subtract(A21, A11, AResult, new_size);
    add(B11, B12, BResult, new_size);
    strassen(AResult, BResult, M6, new_size);

    subtract(A12, A22, AResult, new_size);
    add(B21, B22, BResult, new_size);
    strassen(AResult, BResult, M7, new_size);

    // Combine M1 to M7 to get the result matrix C
    add(M1, M4, C11, new_size);
    subtract(C11, M5, C11, new_size);
    add(C11, M7, C11, new_size);

    add(M3, M5, C12, new_size);

    add(M2, M4, C21, new_size);

    add(M1, M3, C22, new_size);
    subtract(C22, M6, C22, new_size);

    // Place C11, C12, C21, C22 into the result matrix C
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            C[i][j] = C11[i][j];
            C[i][j + new_size] = C12[i][j];
            C[i + new_size][j] = C21[i][j];
            C[i + new_size][j + new_size] = C22[i][j];
        }
    }

    // Free allocated memory for submatrices
    for (int i = 0; i < new_size; i++) {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);
        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);
        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);
        free(M1[i]);
        free(M2[i]);
        free(M3[i]);
        free(M4[i]);
        free(M5[i]);
        free(M6[i]);
        free(M7[i]);
        free(AResult[i]);
        free(BResult[i]);
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(B11);
    free(B12);
    free(B21);
    free(B22);
    free(C11);
    free(C12);
    free(C21);
    free(C22);
    free(M1);
    free(M2);
    free(M3);
    free(M4);
    free(M5);
    free(M6);
    free(M7);
    free(AResult);
    free(BResult);
}

void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}
