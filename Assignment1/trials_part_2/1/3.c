#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define int long long int
typedef struct Matrix
{
    int n, m;
    int *matrix;
} Matrix;
Matrix matrices[5];
int p[7], m[7][7], s[7][7], n;
const int g_outputWidth = 9;      // Set the output width for elements.
const int g_outputPrecision = 15; // Output elements precision.
int g_cacheBlockSize = 16;
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
Matrix *transpose(Matrix *a)
{
    register int N = a->n;
    register int M = a->m;
    register int n, m;
    register int row, col;
    int d_val = 0;
    int diag = 0;
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->matrix = (int *)malloc(N * M * sizeof(int));
    result->n = M;
    result->m = N;
    register int *A = a->matrix;
    register int *B = result->matrix;
    for (col = 0; col < M; col += 8)
    {
        for (row = 0; row < N; row += 8)
        {

            for (n = row; (n < row + 8) && (n < N); ++n)
            {
                for (m = col; (m < col + 8) && (m < M); ++m)
                {

                    if (n != m)
                    {

                        *(B + m * N + n) = *(A + n * M + m);
                    }
                    else
                    {
                        diag = n;
                        d_val = *(A + n * M + m);
                    }
                }
                if (row == col)
                {
                    *(B + diag * N + diag) = d_val;
                }
            }
        }
    }
    return result;
}
void matrixMultiplicationOptimized(int A_dim1, int A_dim2, int B_dim1, int **A, int **B, int **C)
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
    return;
}
void matrix_mult_wiki_block(int *A, int *B, int *C,
                            const int N, const int M, const int K)
{
    const int block_size = 64 / sizeof(int);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < K; j++)
        {
            C[K * i + j] = 0;
        }
    }
    for (int i0 = 0; i0 < N; i0 += block_size)
    {
        int imax = i0 + block_size > N ? N : i0 + block_size;

        for (int j0 = 0; j0 < M; j0 += block_size)
        {
            int jmax = j0 + block_size > M ? M : j0 + block_size;

            for (int k0 = 0; k0 < K; k0 += block_size)
            {
                int kmax = k0 + block_size > K ? K : k0 + block_size;

                for (int j1 = j0; j1 < jmax; ++j1)
                {
                    int sj = M * j1;

                    for (int i1 = i0; i1 < imax; ++i1)
                    {
                        int mi = M * i1;
                        int ki = K * i1;
                        int kij = ki + j1;

                        for (int k1 = k0; k1 < kmax; ++k1)
                        {
                            C[kij] += A[mi + k1] * B[sj + k1];
                        }
                    }
                }
            }
        }
    }
}
Matrix *matrix_multiply(Matrix *a, Matrix *a2)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    register int p = a->n, q = a->m, r = a2->m, i, j, k, temp, *b1, *a1, *c;
    result->matrix = (int *)calloc(p * r, sizeof(int));
    //Matrix *b = transpose(a2);
    result->n = p;
    result->m = r;
    matrixMultiplicationOptimized(a->n, a->m, a2->m, a->matrix, a2->matrix, result->matrix);

    // for (i = 0; i < p; ++i)
    // {
    //     a1 = a->matrix + i * q;
    //     c = result->matrix + i * r;

    //     for (j = 0; j < r; ++j)
    //     {
    //         b1 = b->matrix + j * q;
    //         temp = 0;
    //         q = q - 16;
    //         for (k = 0; k < q; k += 16)
    //         {
    //             a1 += k;
    //             b1 += k;
    //             temp += (*(a1)) * (*(b1)) + (*(a1 + 1)) * (*(b1 + 1)) + (*(a1 + 2)) * (*(b1 + 2)) +
    //                     (*(a1 + 3)) * (*(b1 + 3)) + (*(a1 + 4)) * (*(b1 + 4)) + (*(a1 + 5)) * (*(b1 + 5)) +
    //                     (*(a1 + 6)) * (*(b1 + 6)) + (*(a1 + 7)) * (*(b1 + 7)) + (*(a1 + 8)) * (*(b1 + 8)) +
    //                     (*(a1 + 9)) * (*(b1 + 9)) + (*(a1 + 10)) * (*(b1 + 10)) + (*(a1 + 11)) * (*(b1 + 11)) +
    //                     (*(a1 + 12)) * (*(b1 + 12)) + (*(a1 + 13)) * (*(b1 + 13)) + (*(a1 + 14)) * (*(b1 + 14)) +
    //                     (*(a1 + 15)) * (*(b1 + 15));
    //             a1 -= k;
    //             b1 -= k;
    //         }

    //         q = q + 16;
    //         for (; k < q; k++)
    //             temp += (*(a1 + k)) * (*(b1 + k));

    //         *(c + j) = temp;
    //     }
    // }
    free(a->matrix);
    free(a2->matrix);
    //free(b->matrix);
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
        matrices[temp].matrix = (int *)malloc(xk * yk * sizeof(int));
        for (i = 0; i < xk; i++)
            for (j = 0; j < yk; j++)
                scanf("%lld", matrices[temp].matrix + i * yk + j);
    }
    MATRIX_CHAIN_ORDER();
    Matrix *result = MATRIX_CHAIN_MULTIPLY(1, n);
    k = result->n;
    temp = result->m;
    printf("%lld %lld\n", k, temp);
    for (i = 0; i < k; ++i)
    {
        for (j = 0; j < temp; ++j)
        {
            printf("%lld ", *(result->matrix + i * temp + j));
        }
        printf("\n");
    }
    free(result->matrix);

    return 0;
}
