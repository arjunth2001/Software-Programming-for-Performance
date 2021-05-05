#include <stdio.h>
int dist[2505][2505];
int main()
{
    int v1, e, x, y, w, INF = 1e9 + 7;
    register int i, j, k, v;
    register int temp, ik, vdash = v - 32;
    register int *a, *b, *c, *d;
    scanf("%d %d", &v1, &e);
    v = v1;
    for (i = 1; i <= v; ++i)
    {
        for (j = 1; j <= v; ++j)
        {
            if (i == j)
            {
                dist[i][j] = 0;
            }
            else
                dist[i][j] = INF;
        }
    }
    for (i = 0; i < e; ++i)
    {
        scanf("%d %d %d", &x, &y, &w);
        if (dist[x][y] > w)
            dist[x][y] = w;
    }
    for (k = 1; k <= v; ++k)
    {
        d = *(dist + k);
        for (i = 1; i <= v; ++i)
        {

            ik = *(*(dist + i) + k);
            if (ik != INF)
            {
                c = *(dist + i);
                for (j = 1; j <= vdash; j += 32)
                {
                    a = c + j;
                    b = d + j;
                    temp = ik + *(b);
                    if (temp < *(a))
                        *(a) = temp;
                    temp = ik + *(b + 1);
                    if (temp < *(a + 1))
                        *(a + 1) = temp;
                    temp = ik + *(b + 2);
                    if (temp < *(a + 2))
                        *(a + 2) = temp;
                    temp = ik + *(b + 3);
                    if (temp < *(a + 3))
                        *(a + 3) = temp;
                    temp = ik + *(b + 4);
                    if (temp < *(a + 4))
                        *(a + 4) = temp;
                    temp = ik + *(b + 5);
                    if (temp < *(a + 5))
                        *(a + 5) = temp;
                    temp = ik + *(b + 6);
                    if (temp < *(a + 6))
                        *(a + 6) = temp;
                    temp = ik + *(b + 7);
                    if (temp < *(a + 7))
                        *(a + 7) = temp;
                    temp = ik + *(b + 8);
                    if (temp < *(a + 8))
                        *(a + 8) = temp;
                    temp = ik + *(b + 9);
                    if (temp < *(a + 9))
                        *(a + 9) = temp;
                    temp = ik + *(b + 10);
                    if (temp < *(a + 10))
                        *(a + 10) = temp;
                    temp = ik + *(b + 11);
                    if (temp < *(a + 11))
                        *(a + 11) = temp;
                    temp = ik + *(b + 12);
                    if (temp < *(a + 12))
                        *(a + 12) = temp;
                    temp = ik + *(b + 13);
                    if (temp < *(a + 13))
                        *(a + 13) = temp;
                    temp = ik + *(b + 14);
                    if (temp < *(a + 14))
                        *(a + 14) = temp;
                    temp = ik + *(b + 15);
                    if (temp < *(a + 15))
                        *(a + 15) = temp;
                    temp = ik + *(b + 16);
                    if (temp < *(a + 16))
                        *(a + 16) = temp;
                    temp = ik + *(b + 17);
                    if (temp < *(a + 17))
                        *(a + 17) = temp;
                    temp = ik + *(b + 18);
                    if (temp < *(a + 18))
                        *(a + 18) = temp;
                    temp = ik + *(b + 19);
                    if (temp < *(a + 19))
                        *(a + 19) = temp;
                    temp = ik + *(b + 20);
                    if (temp < *(a + 20))
                        *(a + 20) = temp;
                    temp = ik + *(b + 21);
                    if (temp < *(a + 21))
                        *(a + 21) = temp;
                    temp = ik + *(b + 22);
                    if (temp < *(a + 22))
                        *(a + 22) = temp;
                    temp = ik + *(b + 23);
                    if (temp < *(a + 23))
                        *(a + 23) = temp;
                    temp = ik + *(b + 24);
                    if (temp < *(a + 24))
                        *(a + 24) = temp;
                    temp = ik + *(b + 25);
                    if (temp < *(a + 25))
                        *(a + 25) = temp;
                    temp = ik + *(b + 26);
                    if (temp < *(a + 26))
                        *(a + 26) = temp;
                    temp = ik + *(b + 27);
                    if (temp < *(a + 27))
                        *(a + 27) = temp;
                    temp = ik + *(b + 28);
                    if (temp < *(a + 28))
                        *(a + 28) = temp;
                    temp = ik + *(b + 29);
                    if (temp < *(a + 29))
                        *(a + 29) = temp;
                    temp = ik + *(b + 30);
                    if (temp < *(a + 30))
                        *(a + 30) = temp;
                    temp = ik + *(b + 31);
                    if (temp < *(a + 31))
                        *(a + 31) = temp;
                }
                for (; j <= v; ++j)
                {
                    temp = ik + *(d + j);
                    if (temp < *(c + j))
                        *(c + j) = temp;
                }
            }
        }
    }

    for (i = 1; i <= v; ++i)
    {
        for (j = 1; j <= v; ++j)
        {
            if (dist[i][j] == INF)
            {
                printf("-1");
            }
            else
                printf("%d", dist[i][j]);
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}