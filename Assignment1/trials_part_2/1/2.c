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

void multiply_naive(Matrix *A1, Matrix *B1, int *A, int *B, int m, int n, int p, int *dest, int doffset, int aoffset, int boffset)
{
    //A - m x n
    //B - p x n
    //dest - m x n
    // for (unsigned i = 0u; i < m; i++)
    // {
    //     for (unsigned j = 0u; j < p; j++)
    //     {
    //         for (unsigned k = 0u; k < n; k++)
    //         {
    //             dest[i][doffset + j] += A[i][aoffset + k] * B[j][boffset + k];
    //         }
    //     }
    // }

    register int i, j, k, n1 = A1->m, p1 = B1->n, temp, m1 = B1->m, *b1, *a1, *c;
    for (i = 0; i < m; ++i)
    {
        a1 = A + i * n1 + aoffset;
        c = dest + i * p1 + doffset;

        for (j = 0; j < p; ++j)
        {
            b1 = B + j * m1 + boffset;
            temp = 0;
            n = n - 16;
            for (k = 0; k < n; k += 16)
            {
                a1 += k;
                b1 += boffset + k;
                temp += (*(a1)) * (*(b1)) + (*(a1 + 1)) * (*(b1 + 1)) + (*(a1 + 2)) * (*(b1 + 2)) +
                        (*(a1 + 3)) * (*(b1 + 3)) + (*(a1 + 4)) * (*(b1 + 4)) + (*(a1 + 5)) * (*(b1 + 5)) +
                        (*(a1 + 6)) * (*(b1 + 6)) + (*(a1 + 7)) * (*(b1 + 7)) + (*(a1 + 8)) * (*(b1 + 8)) +
                        (*(a1 + 9)) * (*(b1 + 9)) + (*(a1 + 10)) * (*(b1 + 10)) + (*(a1 + 11)) * (*(b1 + 11)) +
                        (*(a1 + 12)) * (*(b1 + 12)) + (*(a1 + 13)) * (*(b1 + 13)) + (*(a1 + 14)) * (*(b1 + 14)) +
                        (*(a1 + 15)) * (*(b1 + 15));
                a1 -= k;
                b1 -= k;
            }

            n = n + 16;
            for (; k < n; k++)
                temp += (*(a1 + k)) * (*(b1 + k));

            *(c + j) = temp;
        }
    }
}
void multiply(Matrix *A1, Matrix *B1, int *A, int *B, unsigned const m, unsigned const n, unsigned const p, int *dest, unsigned const doffset, unsigned const aoffset, unsigned const boffset)
{

    if ((m * n + n * p) < 4096)
    {
        multiply_naive(A1, B1, A, B, m, n, p, dest, doffset, aoffset, boffset);
    }
    else if (m >= (n >= p ? n : p))
    {
        const unsigned split = m >> 1;
        const unsigned rest = m - split;
        multiply(A1, B1, A, B, split, n, p, dest, doffset, aoffset, boffset);
        multiply(A1, B1, A + split * (A1->m), B, rest, n, p, dest + split * (B1->n), doffset, aoffset, boffset);
    }
    else if (n >= (m >= p ? m : p))
    {

        const unsigned split = n >> 1;
        const unsigned rest = n - split;
        multiply(A1, B1, A, B, m, split, p, dest, doffset, aoffset, boffset);
        multiply(A1, B1, A, B, m, rest, p, dest, doffset, aoffset + split, boffset + split);
    }
    else
    {

        const unsigned split = p >> 1;
        const unsigned rest = p - split;
        multiply(A1, B1, A, B, m, n, split, dest, doffset, aoffset, boffset);
        multiply(A1, B1, A, B + split * (B1->m), m, n, rest, dest, doffset + split, aoffset, boffset);
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
Matrix *matrix_multiply(Matrix *a, Matrix *a2)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    register int p = a->n, q = a->m, r = a2->m, i, j, k, temp, *b1, *a1, *c;
    result->matrix = (int *)malloc(p * r * sizeof(int));
    Matrix *b = transpose(a2);
    result->n = p;
    result->m = r;
    multiply(a, b, a->matrix, b->matrix, p, q, r, result->matrix, 0, 0, 0);
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
