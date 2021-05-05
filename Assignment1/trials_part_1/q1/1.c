#include <stdlib.h>
#include <stdio.h>
#define int long long int
typedef struct Matrix
{
    int n, m;
    int matrix[1000][1000];
} Matrix;
Matrix matrices[6];
void MATRIX_CHAIN_ORDER(int *p, int n, int **m, int **s)
{
    int i;
    int row = n + 1;
    for (i = 1; i <= n; i++)
        *((int *)m + row * i + i) = 0;

    int l;
    for (l = 2; l <= n; l++)
    {
        for (i = 1; i <= (n - l + 1); i++)
        {
            int j = i + l - 1;
            *((int *)m + row * i + j) = -1;
            int k;
            for (k = i; k <= (j - 1); k++)
            {
                int tmp1 = *((int *)m + row * i + k);
                int tmp2 = *((int *)m + row * (k + 1) + j);
                int q = tmp1 + tmp2 + p[i - 1] * p[k] * p[j];

                int old = *((int *)m + row * i + j);
                if (q < old || old == -1)
                {
                    *((int *)m + row * i + j) = q;
                    *((int *)s + row * i + j) = k;
                }
            }
        }
    }
}
Matrix *matrix_multiply(Matrix *a, Matrix *b, int p, int q, int r)
{
    Matrix *result;
    result = malloc(sizeof(Matrix));

    for (int i = 0; i < p; i++)
    {
        for (int k = 0; k < q; k++)
        {
            for (int j = 0; j < r; j++)
            {
                result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
            }
        }
    }
    result->n = p;
    result->m = r;
    return result;
}

Matrix *MATRIX_CHAIN_MULTIPLY(int **s, int i, int j, int row)
{
    if (i == j)
        return &matrices[i];
    if (j == i + 1)
        return matrix_multiply(&matrices[i], &matrices[j], matrices[i].n, matrices[i].m, matrices[j].m);
    else
    {
        Matrix *B1 = MATRIX_CHAIN_MULTIPLY(s, i, *((int *)s + row * i + j), row);
        Matrix *B2 = MATRIX_CHAIN_MULTIPLY(s, *((int *)s + row * i + j) + 1, j, row);
        return matrix_multiply(B1, B2, B1->n, B1->m, B2->m);
    }
}
signed main()
{
    int n, xk, yk;
    int p[7];
    scanf("%lld", &n);
    for (int k = 1; k <= n; k++)
    {
        scanf("%lld %lld", &xk, &yk);
        matrices[k].n = xk;
        p[k] = xk;
        matrices[k].m = yk;
        for (int i = 0; i < xk; i++)
            for (int j = 0; j < yk; j++)
                scanf("%lld", &matrices[k].matrix[i][j]);
    }

    int m[n + 1][n + 1];
    int s[n + 1][n + 1];

    MATRIX_CHAIN_ORDER(p, n, (int **)m, (int **)s);
    int i, j;
    Matrix *result = MATRIX_CHAIN_MULTIPLY((int **)s, 1, n, n + 1);
    printf("%lld %lld\n", result->n, result->m);
    for (i = 0; i < result->n; i++)
    {
        for (j = 0; j < result->m; j++)
        {
            printf("%lld ", result->matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
