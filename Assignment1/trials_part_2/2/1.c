#include <stdio.h>
#include <stdlib.h>
const int L1_CACHE_SIZE = 12582912;
long long int min(long long int a, long long int b) { return a > b ? b : a; }
void FWR_All(long long *A, long long *B, long long *C, const int N,
             const int dm, const int dn, const int dp)
{
    printf("rec\n");
    int memSize = (dm * dp + dm * dn + dn * dp) * (sizeof(long long));
    if (memSize <= L1_CACHE_SIZE)
    {
        register long long int k, i, j, bik, *aij, temp;
        for (k = 0; k < dn; ++k)
        {
            for (i = 0; i < dm; ++i)
            {
                bik = *(B + (i * N + k));
                if (bik == 1000000007)
                    continue;
                for (j = 0; j < dp; ++j)
                {
                    temp = bik + *(C + (k * N + j));
                    aij = A + (i * N + j);
                    if (*aij > temp)
                        *aij = temp;
                }
            }
        }
    }
    else
    {
        FWR_All(A, B, C, N, dm / 2, dn / 2, dp / 2);

        FWR_All(A + dp / 2, B, C + dp / 2, N, dm / 2, dn / 2, dp - dp / 2);

        FWR_All(A + dm / 2 * N, B + dm / 2 * N, C, N, dm - dm / 2, dn / 2, dp / 2);

        FWR_All(A + (dm / 2) * N + (dp / 2), B + (dm / 2) * N, C + dp / 2, N, dm - dm / 2, dn / 2, dp - dp / 2);

        FWR_All(A + (dm / 2) * N + (dp / 2), B + (dm / 2) * N + (dn / 2), C + (dn / 2) * N + (dp / 2), N, dm - dm / 2, dn - dn / 2, dp - dp / 2);

        FWR_All(A + (dm / 2) * N, B + (dm / 2) * N + (dn / 2), C + (dn / 2) * N, N, dm - dm / 2, dn - dn / 2, dp / 2);

        FWR_All(A + dp / 2, B + dn / 2, C + (dn / 2) * N + (dp / 2), N, dm / 2, dn - dn / 2, dp - dp / 2);

        FWR_All(A, B + dn / 2, C + (dn / 2) * N, N, dm / 2, dn - dn / 2, dp / 2);
    }
}
int main()
{
    int v1, e, x, y, w;
    register long long int *dist, i, j, k, vtemp, ik, *a, *b, *c, *d, v, temp;
    scanf("%d %d", &v1, &e);
    v = v1;
    dist = (long long int *)malloc(v * v * sizeof(long long int));
    for (i = 0; i < v; ++i)
    {
        a = dist + i * v;

        for (j = 0; j < v; ++j)
        {
            if (i != j)
            {
                *(a + j) = 1000000007;
            }
        }
    }
    for (i = 0; i < e; ++i)
    {
        scanf("%d %d %d", &x, &y, &w);
        x--;
        y--;
        a = dist + x * v + y;
        if (*a > w)
            *a = w;
    }
    FWR_All(dist, dist, dist, v, v, v, v);

    for (i = 0; i < v; ++i)
    {
        a = dist + i * v;
        for (j = 0; j < v; ++j)
        {
            temp = *(a + j);
            if (temp == 1000000007)
            {
                printf("-1 ");
            }
            else
                printf("%lld ", temp);
        }
        printf("\n");
    }

    return 0;
}