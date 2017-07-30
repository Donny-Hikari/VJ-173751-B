#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

const int MAXSD = 1e5 + 5;
int D[6][MAXSD];
int S[6];
int n, m, k;

bool chk(int md)
{
    bool bF = false;
    int lS[6];
    for (int i = 1; i <= n - md + 1 && !bF; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < m && cnt <= k; ++j)
        {
            lS[j] = *max_element(D[j] + i, D[j] + i + md);
            cnt += lS[j];
        }
        if (cnt <= k)
        {
            bF = true;
            for (int o = 0; o < m; ++o) S[o] = lS[o];
        }
    }
    return bF;
}

int main()
{
    while (scanf("%d %d %d", &n, &m, &k) != EOF)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d", &D[j][i]);
        memset(S, 0, sizeof(S));
        int l = 0, r = n;
        while (r >= l)
        {
            int md = (r + l) >> 1;
            if (chk(md))
                l = md + 1;
            else
                r = md - 1;
        }
        printf("%d", S[0]);
        for (int o = 1; o < m; ++o) printf(" %d", S[o]);
    }

    return 0;
}