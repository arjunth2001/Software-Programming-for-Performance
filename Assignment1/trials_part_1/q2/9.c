#include <stdio.h>
int dist[2505][2505];
int main()
{
    int v1, e, x, y, w, INF = 1e9 + 7;
    register int i, j, k, v;
    register int temp, ik;
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
                v = v - 16;
                for (j = 1; j <= v; j += 16)
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
                }
                v = v + 16;
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