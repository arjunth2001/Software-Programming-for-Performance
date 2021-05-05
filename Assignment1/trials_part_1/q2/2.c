#include <stdio.h>
int INF = 1e9 + 7;
int dist[2505][2505] = {0};
void FW(int v)
{
    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}
int scan_int(int *a)
{
    int x = 0, negative = 0;
    register int c = getchar_unlocked();
    if (c == '-')
    {
        negative = 1;
        c = getchar_unlocked();
    }
    for (; c > 47 && c < 58; c = getchar_unlocked())
    {
        x = (x << 1) + (x << 3) + c - 48;
    }
    *a = (negative == 1) ? -(x) : x;
}

int main()
{
    int v, e, x, y, w;
    scan_int(&v);
    scan_int(&e);
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
        scan_int(&x);
        scan_int(&y);
        scan_int(&w);
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