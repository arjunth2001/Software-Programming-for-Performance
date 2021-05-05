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
Matrix *transpose(Matrix *a)
{
    int N = a->n;
    int M = a->m;
    register int n, m;
    register int row, col;
    int d_val = 0;
    int diag = 0;
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->matrix = initialize_matrix(M, N);
    result->n = M;
    result->m = N;
    register int **A = a->matrix;
    register int **B = result->matrix;
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

                        *(*(B + m) + n) = *(*(A + n) + m);
                    }
                    else
                    {
                        diag = n;
                        d_val = *(*(A + n) + m);
                    }
                }
                if (row == col)
                {
                    *(*(B + diag) + diag) = d_val;
                }
            }
        }
    }
    return result;
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
void multiply_naive(int **A, int **B, int m, int n, int p, int **dest, int doffset, int aoffset, int boffset)
{
    register int i, j, k, temp, *b1, *a1, *c;

    for (i = 0; i < m; ++i)
    {
        a1 = *(A + i) + aoffset;
        c = *(dest + i) + doffset;

        for (j = 0; j < p; ++j)
        {
            b1 = *(B + j) + boffset;
            temp = *(c + j);
            n = n - 16;
            for (k = 0; k < n; k += 16)
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

            n = n + 16;
            for (; k < n; k++)
                temp += (*(a1 + k)) * (*(b1 + k));
            *(c + j) = temp;
        }
    }
}
void multiply(int **A, int **B, int m, int n, int p, int **dest, int doffset, int aoffset, int boffset)
{
    int min = m * n < n * p ? m * n : n * p;
    if (min <= 32768)
    {
        multiply_naive(A, B, m, n, p, dest, doffset, aoffset, boffset);
    }
    else if (m >= (n >= p ? n : p))
    {

        int split = m >> 1;
        int rest = m - split;
#pragma omp parallel sections
        {
#pragma omp section
            multiply(A, B, split, n, p, dest, doffset, aoffset, boffset);
#pragma omp section
            multiply(A + split, B, rest, n, p, dest + split, doffset, aoffset, boffset);
        }
    }
    else if (n >= (m >= p ? m : p))
    {

        int split = n >> 1;
        int rest = n - split;
#pragma omp parallel sections
        {
#pragma omp section
            multiply(A, B, m, split, p, dest, doffset, aoffset, boffset);
#pragma omp section
            multiply(A, B, m, rest, p, dest, doffset, aoffset + split, boffset + split);
        }
    }
    else
    {

        int split = p >> 1;
        int rest = p - split;
#pragma omp parallel sections
        {
#pragma omp section
            multiply(A, B, m, n, split, dest, doffset, aoffset, boffset);
#pragma omp section
            multiply(A, B + split, m, n, rest, dest, doffset + split, aoffset, boffset);
        }
    }
}
Matrix *matrix_multiply(Matrix *a, Matrix *b)
{
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));
    result->matrix = initialize_matrix(a->n, b->m);
    result->n = a->n;
    result->m = b->m;
    b = transpose(b);
    multiply(a->matrix, b->matrix, a->n, a->m, b->n, result->matrix, 0, 0, 0);
    //matrixMultiplicationOptimized(a->n, a->m, b->m, a->matrix, b->matrix, result->matrix);

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
