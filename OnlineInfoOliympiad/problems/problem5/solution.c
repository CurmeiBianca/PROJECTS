#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    int v[N];

    for (int i = 0; i < N; i++)
        scanf("%d", &v[i]);

    int X;
    scanf("%d", &X);

    int count = 0;

    for (int i = 0; i < N; i++)
        if (v[i] == X)
            count++;

    printf("%d\n", count);

    return 0;
}