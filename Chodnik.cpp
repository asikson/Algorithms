// Joanna Mielniczuk

#include <bits/stdc++.h>

using namespace std;

int n;
int cycleCTRL;

struct plate
{
    int l;
    int m;
    int r;
};

bool Visited[10001]; // visited vertices
vector<plate> Path; // used plates
vector<plate> Edges[10001]; // list of edges

void DFS(int vertice)
{
    Visited[vertice] = true;

    for (int i=0; i < Edges[vertice].size(); i++)
    {
        plate newPlate = Edges[vertice][i];

        if (newPlate.r == 0)
        {
            Path.push_back(newPlate);
            cycleCTRL++;
            return;
        }
        else if (!(Visited[newPlate.r]))
        {
            Path.push_back(newPlate);
            DFS(newPlate.r);
            if (cycleCTRL > 0) return;
        }
    }
    Path.pop_back();
}

int main()
{
    cycleCTRL = 0;
    scanf("%d", &n);

    int d1, d2, d3;
    for (int i=0; i<n; i++)
    {
        scanf("%d %d %d", &d1, &d2, &d3);
        plate newPlate = {d1, d2, d3};
        Edges[d1].push_back(newPlate);
    }
    
    DFS(0);

    if (cycleCTRL == 1)
    {
        printf("%lu\n", Path.size());

        for (int i=0; i < Path.size(); i++)
            printf("%d %d %d\n", Path[i].l, Path[i].m, Path[i].r);
    }
    else printf("BRAK\n");

    return 0;
}
