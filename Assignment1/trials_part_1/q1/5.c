#include <stdlib.h>
#include <stdio.h>
#define int long long int
typedef struct Matrix
{
    int n, m;
    int matrix[1000][1000];
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
Matrix *matrix_multiply(Matrix *a, Matrix *b)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    register int p = a->n, q = a->m, r = b->m, i, j, k, temp, *b1, *a1, *c;
    register int max = q ^ ((q ^ r) & -(q < r));
    for (i = 0; i < max; ++i)
    {
        for (j = 0; j < i; ++j)
        {
            b->matrix[i][j] ^= b->matrix[j][i];
            b->matrix[j][i] ^= b->matrix[i][j];
            b->matrix[i][j] ^= b->matrix[j][i];
        }
    }

    for (i = 0; i < p; ++i)
    {
        a1 = *(a->matrix + i);
        c = *(result->matrix + i);

        for (j = 0; j < r; ++j)
        {
            b1 = *(b->matrix + j);
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
    result->n = p;
    result->m = r;
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
