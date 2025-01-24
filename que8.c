#include <stdio.h>
#include <stdlib.h>

int matrixChainOrder(int *p, int n);

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int *p = (int *)calloc(n + 1, sizeof(int));

    printf("Enter the dimensions of the matrices:\n");
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Minimum number of multiplications is: %d\n", matrixChainOrder(p, n));

    free(p);
    return 0;
}

int matrixChainOrder(int *p, int n) {
    int **m = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        m[i] = (int *)calloc(n, sizeof(int));
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = 2147483647; // Set initial to a large number
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    int result = m[0][n - 1];

    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    free(m);

    return result;
}
