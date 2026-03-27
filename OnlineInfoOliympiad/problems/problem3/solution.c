#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    int v[N];

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (v[j] > v[j+1])
            {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++)
        printf("%d ", v[i]);

    printf("\n");
    
    return 0;
}