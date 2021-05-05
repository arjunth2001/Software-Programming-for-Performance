#include <stdio.h>
#include <stdlib.h>
void FW(int *A, int *B, int *C, int N, int dm, int dn, int dp)
{

    if ((dm * dp + dm * dn + dn * dp) < 8192)
    {
        register int k, i, j, bik, *aij, temp, *ck, *ai;
        for (k = 0; k < dn; ++k)
        {
            ck = C + k * N;

            for (i = 0; i < dm; ++i)
            {
                bik = *(B + (i * N + k));

                if (bik == 1000000007)
                    continue;
                ai = A + i * N;

                dp = dp - 16;
                for (j = 0; j < dp; j += 16)
                {
                    ck += j;
                    temp = bik + *(ck);
                    aij = ai + j;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 1);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 2);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 3);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 4);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 5);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 6);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 7);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 8);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 9);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 10);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 11);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 12);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 13);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 14);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;
                    temp = bik + *(ck + 15);
                    ++aij;
                    if (*aij > temp)
                        *aij = temp;

                    ck -= j;
                }
                dp = dp + 16;
                for (; j < dp; ++j)
                {
                    temp = bik + *(ck + j);
                    aij = ai + j;
                    if (*aij > temp)
                        *aij = temp;
                }
            }
        }
    }
    else
    {
        int dm_dash = dm >> 1, dn_dash = dn >> 1, dp_dash = dp >> 1;
        FW(A, B, C, N, dm_dash, dn_dash, dp_dash);

        FW(A + dp_dash, B, C + dp_dash, N, dm_dash, dn_dash, dp - dp_dash);

        FW(A + dm_dash * N, B + dm_dash * N, C, N, dm - dm_dash, dn_dash, dp_dash);

        FW(A + (dm_dash)*N + (dp_dash), B + (dm_dash)*N, C + dp_dash, N, dm - dm_dash, dn_dash, dp - dp_dash);

        FW(A + (dm_dash)*N + (dp_dash), B + (dm_dash)*N + (dn_dash), C + (dn_dash)*N + (dp_dash), N, dm - dm_dash, dn - dn_dash, dp - dp_dash);

        FW(A + (dm_dash)*N, B + (dm_dash)*N + (dn_dash), C + (dn_dash)*N, N, dm - dm_dash, dn - dn_dash, dp_dash);

        FW(A + dp_dash, B + dn_dash, C + (dn_dash)*N + (dp_dash), N, dm_dash, dn - dn_dash, dp - dp_dash);

        FW(A, B + dn_dash, C + (dn_dash)*N, N, dm_dash, dn - dn_dash, dp_dash);
    }
}
int main()
{
    int v1, e, x, y, w;
    register int *dist, i, j, k, vtemp, ik, *a, *b, *c, *d, v, temp;
    scanf("%d %d", &v1, &e);
    v = v1;
    dist = (int *)calloc(v * v, sizeof(int));
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

        a = dist + (x - 1) * v + y - 1;
        if (*a > w)
            *a = w;
    }
    FW(dist, dist, dist, v, v, v, v);

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
                printf("%d ", temp);
        }
        printf("\n");
    }
    free(dist);

    return 0;
}