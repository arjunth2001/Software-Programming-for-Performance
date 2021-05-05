#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#define int long long int
typedef struct Matrix
{
    int n, m;
    int *matrix;
} Matrix;
Matrix matrices[5];
int p[7], m[7][7], s[7][7], n;
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
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->matrix = (int *)malloc(N * M * sizeof(int));
    result->n = M;
    result->m = N;
    register int *A = a->matrix;
    register int *B = result->matrix;

    int d_val = 0;
    int diag = 0;
    register int n, m;
    register int row, col;

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
Matrix *matrix_multiply(Matrix *a, Matrix *a2)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));

    result->matrix = (int *)malloc((a->n) * (a2->m) * sizeof(int));
    Matrix *b = transpose(a2);
    result->n = a->n;
    result->m = a2->m;

    register int p = a->n, q = a->m, r = a2->m, i, j, k, temp, *b1, *a1, *c;

    for (i = 0; i < p; ++i)
    {
        a1 = a->matrix + i * q;
        c = result->matrix + i * r;

        for (j = 0; j < r; ++j)
        {
            b1 = b->matrix + j * q;
            temp = 0;
            q = q - 16;
            for (k = 0; k < q; k += 16)
            {
                a1 += k;
                b1 += k;
                temp += (*(a1)) * (*(b1)) + (*(a1 + 1)) * (*(b1 + 1)) + (*(a1 + 2)) * (*(b1 + 2)) +
                        (*(a1 + 3)) * (*(b1 + 3)) + (*(a1 + 4)) * (*(b1 + 4)) + (*(a1 + 5)) * (*(b1 + 5)) +
                        (*(a1 + 6)) * (*(b1 + 6)) + (*(a1 + 7)) * (*(b1 + 7)) + (*(a1 + 8)) * (*(b1 + 8)) +
                        (*(a1 + 9)) * (*(b1 + 9)) + (*(a1 + 10)) * (*(b1 + 10)) + (*(a1 + 11)) * (*(b1 + 11)) +
                        (*(a1 + 12)) * (*(b1 + 12)) + (*(a1 + 13)) * (*(b1 + 13)) + (*(a1 + 14)) * (*(b1 + 14)) +
                        (*(a1 + 15)) * (*(b1 + 15));
                a1 -= k;
                b1 -= k;
            }

            q = q + 16;
            for (; k < q; k++)
                temp += (*(a1 + k)) * (*(b1 + k));

            *(c + j) = temp;
        }
    }
    free(a->matrix);
    free(a2->matrix);
    free(b->matrix);
    return result;
}

Matrix *MATRIX_CHAIN_MULTIPLY(int i, int j)
{
    if (j == i + 1)
        return matrix_multiply(&matrices[i - 1], &matrices[j - 1]);
    if (i == j)
        return &matrices[i - 1];
    Matrix *B1, *B2;
    omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel sections
    {
#pragma omp section
        B1 = MATRIX_CHAIN_MULTIPLY(i, *(*(s + i) + j));
#pragma omp section
        B2 = MATRIX_CHAIN_MULTIPLY(*(*(s + i) + j) + 1, j);
    }
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
        a = result->matrix + i * temp;
        for (j = 0; j < temp; ++j)
        {
            printf("%lld ", *(a + j));
        }
        printf("\n");
    }
    free(result->matrix);

    return 0;
}
