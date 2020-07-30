// Joanna Mielniczuk

#include <bits/stdc++.h>
#define INF INT_MAX

using namespace std;

int choose_m(vector<int> Numbers)
{
    int l = Numbers.size();
    vector<int> current;

    if (l < 10) 
    {
        current = Numbers;
        sort(current.begin(), current.end());
        if (l%2 == 0) return (current[l/2 - 1] + current[l/2])/ 2;
        else return current[l/2];
    }

    vector<int> thirdNumbers;
    
    for (int i=0; l > 0; i++)
    {
        for (int j=0; j<5; j++)
        {
            if (l > 0) 
            {
                current.push_back(Numbers[5*i + j]);
                l--;
            }
            else current.push_back(INF);
        }
        sort(current.begin(), current.end());
        thirdNumbers.push_back(current[2]);
        current.clear();
    }

    return choose_m(thirdNumbers);
}

int find_kth_element(vector<int> Numbers, int k)
{
    if (Numbers.size() < 10)
    {
        sort(Numbers.begin(), Numbers.end());
        return Numbers[k-1];
    }

    int m = choose_m(Numbers);
    vector<int> L;
    vector<int> R;
    vector<int> temp;

    for (int i=0; i<Numbers.size(); i++)
    {
        if (Numbers[i] > m) R.push_back(Numbers[i]);
        else 
        {
            if (Numbers[i] == m) temp.push_back(Numbers[i]);
            else L.push_back(Numbers[i]);
        }
    }

    int r = L.size();
    if (k <= r) return find_kth_element(L, k);
    if (k <= r + temp.size()) return temp[0];
    else return find_kth_element(R, k - r - temp.size());
}


int main()
{
    int n, k;

    scanf("%d %d", &n, &k);

    vector<int> Numbers;

    int current;

    for (int i=0; i<n; i++)
    {
        scanf("%d", &current);
        Numbers.push_back(current);
    }

    int result = find_kth_element(Numbers, k);
    printf("%d\n", result);

    return 0;
}



