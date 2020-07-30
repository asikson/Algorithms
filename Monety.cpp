// Joanna Mielniczuk

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int waga;
    scanf("%d", &waga);
    int n;
    scanf("%d", &n);

    int p[n];
    int w[n];
    for (int i=0; i<n; i++) scanf("%d %d", &p[i], &w[i]);

    int waga_max[waga+1][2];
    int waga_min[waga+1][2];
    for (int i=0; i<waga+1; i++) 
    {
        waga_max[i][0] = -1;
        waga_max[i][1] = -1;
        waga_min[i][0] = -1;
        waga_min[i][1] = -1;
    }
    waga_max[0][0] = 0;
    waga_min[0][0] = 0;

    int l_min[n];
    int l_max[n];
    for (int i=0; i<n; i++)
    {
        l_min[i] = 0;
        l_max[i] = 0;
    }


    for (int i=0; i<n; i++)
    {
        for (int j=1; j < waga+1; j++)
        {
            if (j >= w[i] && waga_max[j - w[i]][0] != -1) 
            {
                if (waga_max[j][0] < waga_max[j - w[i]][0] + p[i])
                {
                    waga_max[j][0] = waga_max[j - w[i]][0] + p[i];
                    waga_max[j][1] = i;
                }

                if (waga_min[j][0] > waga_min[j - w[i]][0] + p[i] || waga_min[j][0] == -1)
                {
                    waga_min[j][0] = waga_min[j - w[i]][0] + p[i];
                    waga_min[j][1] = i;
                }
            }
        }
    }

    if (waga_max[waga][0] == -1)
    {
        printf("NIE\n");
        return 0;
    }
    else
    {
        int index = waga;
        while (index > 0)
        {
            l_min[ waga_min[index][1] ] ++;
            index = index - w[ waga_min[index][1] ];
        }

        index = waga;
        while (index > 0)
        {
            l_max[ waga_max[index][1] ] ++;
            index = index - w[ waga_max[index][1] ];
        }

        printf("TAK\n");
        printf("%d\n", waga_min[waga][0]);
        for (int i=0; i<n; i++) printf("%d ", l_min[i]);
        printf("\n");
        printf("%d\n", waga_max[waga][0]);
        for (int i=0; i<n; i++) printf("%d ", l_max[i]);
        printf("\n");
    }

}

