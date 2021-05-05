#include <stdio.h>
int INF = 1e9 + 7;
int dist[2505][2505] = {0};
void FW(register int v)
{
    register int i, j, k;
    register int temp;
    register int vdash = v - 16;
    for (k = 1; k <= v; ++k)
        for (i = 1; i <= v; ++i)
        {

            if (dist[i][k] != INF)
            {
                for (j = 1; j <= vdash; j += 16)
                {
                    temp = dist[i][k] + dist[k][j];
                    if (temp < dist[i][j])
                        dist[i][j] = temp;
                    temp = dist[i][k] + dist[k][j + 1];
                    if (temp < dist[i][j + 1])
                        dist[i][j + 1] = temp;
                    temp = dist[i][k] + dist[k][j + 2];
                    if (temp < dist[i][j + 2])
                        dist[i][j + 2] = temp;
                    temp = dist[i][k] + dist[k][j + 3];
                    if (temp < dist[i][j + 3])
                        dist[i][j + 3] = temp;
                    temp = dist[i][k] + dist[k][j + 4];
                    if (temp < dist[i][j + 4])
                        dist[i][j + 4] = temp;
                    temp = dist[i][k] + dist[k][j + 5];
                    if (temp < dist[i][j + 5])
                        dist[i][j + 5] = temp;
                    temp = dist[i][k] + dist[k][j + 6];
                    if (temp < dist[i][j + 6])
                        dist[i][j + 6] = temp;
                    temp = dist[i][k] + dist[k][j + 7];
                    if (temp < dist[i][j + 7])
                        dist[i][j + 7] = temp;
                    temp = dist[i][k] + dist[k][j + 8];
                    if (temp < dist[i][j + 8])
                        dist[i][j + 8] = temp;
                    temp = dist[i][k] + dist[k][j + 9];
                    if (temp < dist[i][j + 9])
                        dist[i][j + 9] = temp;
                    temp = dist[i][k] + dist[k][j + 10];
                    if (temp < dist[i][j + 10])
                        dist[i][j + 10] = temp;
                    temp = dist[i][k] + dist[k][j + 11];
                    if (temp < dist[i][j + 11])
                        dist[i][j + 11] = temp;
                    temp = dist[i][k] + dist[k][j + 12];
                    if (temp < dist[i][j + 12])
                        dist[i][j + 12] = temp;
                    temp = dist[i][k] + dist[k][j + 13];
                    if (temp < dist[i][j + 13])
                        dist[i][j + 13] = temp;
                    temp = dist[i][k] + dist[k][j + 14];
                    if (temp < dist[i][j + 14])
                        dist[i][j + 14] = temp;
                    temp = dist[i][k] + dist[k][j + 15];
                    if (temp < dist[i][j + 15])
                        dist[i][j + 15] = temp;
                }
                for (; j <= v; ++j)
                {
                    temp = dist[i][k] + dist[k][j];
                    if (temp < dist[i][j])
                        dist[i][j] = temp;
                }
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