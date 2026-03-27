#include <stdio.h>

int main ()
{
    int N;
    scanf("%d", &N);

    int v[N];

    for (int i = 0; i < N; i++)
        scanf("%d", &v[i]);

    int X;
    scanf("%d", &X);

    int pozitie = -1;

    for (int i = 0; i < N; i++)
        if (v[i] == X)
        {
            pozitie = i;
            break;
        }

    printf("%d\n", pozitie);

    return 0;
}