#include <stdio.h>
int INF = 1e9 + 7;
int dist[2505][2505] = {0};
void FW(int v)
{
    register int i, j, k;
    int temp, ik;
    for (k = 1; k <= v; ++k)
        for (i = 1; i <= v; ++i)
        {
            ik = *(*(dist + i) + k);
            if (ik != INF)
                for (j = 1; j <= v; ++j)
                {
                    temp = ik + *(*(dist + k) + j);
                    if (temp < *(*(dist + i) + j))
                        *(*(dist + i) + j) = temp;
                }
        }
}

int main()
{
    int v, e, x, y, w;
    scanf("%d %d", &v, &e);
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            if (i == j)
            {
                dist[i][j] = 0;
            }
            else
                dist[i][j] = INF;
        }
    }
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &x, &y, &w);
        if (dist[x][y] > w)
            dist[x][y] = w;
    }
    FW(v);
    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
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