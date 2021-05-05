#include <stdio.h>
int dist[2505][2505];
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
    int v1, e, x, y, w;
    register int i, j, k, v;
    register int temp, ik;
    register int *a, *b, *c, *d;
    scan_int(&v1);
    scan_int(&e);
    v = v1;
    for (i = 1; i <= v; ++i)
    {
        a = *(dist + i);

        for (j = 1; j <= v; ++j)
        {
            if (i != j)
            {
                *(a + j) = 1000000007;
            }
        }
    }
    for (i = 0; i < e; ++i)
    {
        scan_int(&x);
        scan_int(&y);
        scan_int(&w);
        a = *(dist + x) + y;
        if (*a > w)
            *a = w;
    }
    for (k = 1; k <= v; ++k)
    {
        d = *(dist + k);
        for (i = 1; i <= v; ++i)
        {
            if (i == k)
                continue;

            ik = *(*(dist + i) + k);
            if (ik == 1000000007)
                continue;

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

    for (i = 1; i <= v; ++i)
    {
        a = *(dist + i);
        for (j = 1; j <= v; ++j)
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

    return 0;
}