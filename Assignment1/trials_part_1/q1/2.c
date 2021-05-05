#include <stdlib.h>
#include <stdio.h>
typedef struct Matrix
{
    int n, m;
    long long int matrix[1000][1000];
} Matrix;
Matrix matrices[5];
long long int p[7], m[7][7], s[7][7], n;
void MATRIX_CHAIN_ORDER()
{
    register int i, l, j, k;
    int q;
    int old;

    for (i = 1; i <= n; ++i)
        *(*(m + i) + i) = 0;
    for (l = 2; l <= n; ++l)
    {
        for (i = 1; i <= (n - l + 1); ++i)
        {
            j = i + l - 1;
            *(*(m + i) + j) = -1;
            for (k = i; k <= (j - 1); ++k)
            {

                q = *(*(m + i) + k) + *(*(m + k + 1) + j) + p[i - 1] * p[k] * p[j];
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
Matrix *matrix_multiply(Matrix *a, Matrix *b)
{
    Matrix *result = malloc(sizeof(Matrix));
    int p = a->n;
    int q = a->m;
    int r = b->m;

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

Matrix *MATRIX_CHAIN_MULTIPLY(int i, int j)
{
    if (i == j)
        return &matrices[i - 1];
    if (j == i + 1)
        return matrix_multiply(&matrices[i - 1], &matrices[j - 1]);
    else
    {
        Matrix *B1 = MATRIX_CHAIN_MULTIPLY(i, *(*(s + i) + j));
        Matrix *B2 = MATRIX_CHAIN_MULTIPLY(*(*(s + i) + j) + 1, j);
        return matrix_multiply(B1, B2);
    }
}
signed main()
{
    int xk, yk;
    scanf("%lld", &n);
    for (int k = 1; k <= n; k++)
    {
        scanf("%d %d", &xk, &yk);
        matrices[k - 1].n = xk;
        p[k - 1] = xk;
        p[k] = yk;
        matrices[k - 1].m = yk;
        for (int i = 0; i < xk; i++)
            for (int j = 0; j < yk; j++)
                scanf("%lld", &matrices[k - 1].matrix[i][j]);
    }
    MATRIX_CHAIN_ORDER();
    int i, j;
    Matrix *result = MATRIX_CHAIN_MULTIPLY(1, n);
    printf("%d %d\n", result->n, result->m);
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
