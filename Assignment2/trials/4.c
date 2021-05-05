#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define int long long int
typedef struct Matrix
{
    int **matrix;
    int n, m;
} Matrix;
Matrix matrices[5];
int p[7], m[7][7], s[7][7], n;
#define min(x, y) x < y ? x : y;
const int g_outputWidth = 9;      // Set the output width for elements.
const int g_outputPrecision = 15; // Output elements precision.
int g_cacheBlockSize = 8;

int **initialize_matrix(int m, int n)
{
    int **M;
    int *tmp = (int *)calloc(m * n, sizeof(int));
    M = (int **)calloc(m, sizeof(int *));
    for (int i = 0; i < m; ++i)
    {
        M[i] = tmp;
        tmp += n;
    }
    return M;
}
void destroy_matrix(int ***M)
{
    if (*M)
    {
        if (*M[0])
        {
            free(*M[0]);
        }
        free(M);
    }
}
void MATRIX_CHAIN_ORDER()
{
    register int i, l, j, k;
    int q;
    int old;
    int temp1, temp2;

    for (i = 1; i <= n; ++i)
        *(*(m + i) + i) = 0;
    for (l = 2; l <= n; ++l)
    {
        temp1 = n - l + 1;
        for (i = 1; i <= temp1; ++i)
        {
            j = i + l - 1;
            *(*(m + i) + j) = -1;
            temp2 = j - 1;
            for (k = i; k <= temp2; ++k)
            {
                q = *(*(m + i) + k) + *(*(m + k + 1) + j) + (*(p + i - 1)) * (*(p + k)) * (*(p + j));
                old = *(*(m + i) + j);
                if (q < old || old == -1)
                {
                    *(*(m + i) + j) = q;
                    *(*(s + i) + j) = k;
                }
            }
        }
    }
}

void matrixMultiplicationOptimized(int A_dim1, int A_dim2, int B_dim1, int **A, int **B, int **C)
{
#pragma omp parallel
    {
        int i, j, k, l;
        int limit0 = A_dim1; // Index i limit
        int limit1 = B_dim1; // Index j limit
        int limit2 = A_dim2; // Index k limit
        int aux_i, aux_j, aux_k;
        int aux_limit_i; // Block index limit i
        int aux_limit_j; // Block index limit j
        int aux_limit_k; // Block index limit k
        int unroll_factor = 5;
        int unroll_limit;                 // Loop unroll index limit
        int acc0, acc1, acc2, acc3, acc4; // Accumulators, eliminate data dependencies
#pragma omp for schedule(static)
        for (i = 0; i < limit0; i += g_cacheBlockSize)
        {
            // Blocking index i limit
            aux_limit_i = min((i + g_cacheBlockSize), limit0);

            for (j = 0; j < limit1; j += g_cacheBlockSize)
            {
                // Blocking index j limit
                aux_limit_j = min((j + g_cacheBlockSize), limit1);

                for (k = 0; k < limit2; k += g_cacheBlockSize)
                {
                    // Blocking index k limit
                    aux_limit_k = min((k + g_cacheBlockSize), limit2);

                    unroll_limit = aux_limit_k - (unroll_factor - 1); // Unrolling by factor of 5

                    for (aux_i = i; aux_i < aux_limit_i; ++aux_i)
                    {
                        for (aux_j = j; aux_j < aux_limit_j; ++aux_j)
                        {

                            acc0 = 0;
                            acc1 = 0;
                            acc2 = 0;
                            acc3 = 0;
                            acc4 = 0;

                            // Unrolling for k loop
                            for (aux_k = k; aux_k < unroll_limit; aux_k += unroll_factor)
                            {
                                acc0 += A[aux_i][aux_k] * B[aux_k][aux_j];
                                acc1 += A[aux_i][aux_k + 1] * B[aux_k + 1][aux_j];
                                acc2 += A[aux_i][aux_k + 2] * B[aux_k + 2][aux_j];
                                acc3 += A[aux_i][aux_k + 3] * B[aux_k + 3][aux_j];
                                acc4 += A[aux_i][aux_k + 4] * B[aux_k + 4][aux_j];
                            }

                            // Gather possible uncounted elements
                            for (; aux_k < aux_limit_k; ++aux_k)
                                C[aux_i][aux_j] += A[aux_i][aux_k] * B[aux_k][aux_j];

                            // Sum up everything
                            C[aux_i][aux_j] += acc0 + acc1 + acc2 + acc3 + acc4;
                        }
                    }
                }
            }
        }
    }
    return;
}
Matrix *matrix_multiply(Matrix *a, Matrix *b)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->matrix = initialize_matrix(a->n, b->m);
    result->n = a->n;
    result->m = b->m;
    //b = transpose(b);
    //(a->matrix, b->matrix, a->n, a->m, b->n, result->matrix, 0, 0, 0);
    matrixMultiplicationOptimized(a->n, a->m, b->m, a->matrix, b->matrix, result->matrix);

    return result;
}

Matrix *MATRIX_CHAIN_MULTIPLY(int i, int j)
{
    if (j == i + 1)
        return matrix_multiply(&matrices[i - 1], &matrices[j - 1]);
    if (i == j)
        return &matrices[i - 1];

    Matrix *B1 = MATRIX_CHAIN_MULTIPLY(i, *(*(s + i) + j));
    Matrix *B2 = MATRIX_CHAIN_MULTIPLY(*(*(s + i) + j) + 1, j);
    return matrix_multiply(B1, B2);
}
signed main()
{
    int xk, yk;
    register int i, j, k, temp;
    register int *a;
    scanf("%lld", &n);
    for (k = 1; k <= n; k++)
    {
        temp = k - 1;
        scanf("%lld %lld", &xk, &yk);
        matrices[temp].n = xk;
        p[temp] = xk;
        p[k] = yk;
        matrices[temp].m = yk;
        matrices[temp].matrix = initialize_matrix(xk, yk);
        for (i = 0; i < xk; i++)
            for (j = 0; j < yk; j++)
                scanf("%lld", &matrices[temp].matrix[i][j]);
    }
    MATRIX_CHAIN_ORDER();
    Matrix *result = MATRIX_CHAIN_MULTIPLY(1, n);
    k = result->n;
    temp = result->m;
    printf("%lld %lld\n", k, temp);

    for (i = 0; i < k; ++i)
    {
        a = *(result->matrix + i);
        for (j = 0; j < temp; ++j)
        {
            printf("%lld ", *(a + j));
        }
        printf("\n");
    }

    return 0;
}
