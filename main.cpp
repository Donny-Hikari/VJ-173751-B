#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <exception>
using namespace std;

const int MAXSD = 1e5 + 5;
int ST[21][6][MAXSD];
int S[6];
int n, m, k;

void buildST()
{
    for (int o = 0; o < m; ++o)
        for (int j = 1; j <= 20; ++j)
            for (int i = 1; i <= n; ++i)
                if (i + (1 << j) - 1 <= n)
                    ST[j][o][i] = max(ST[j - 1][o][i], ST[j - 1][o][i + (1 << (j-1))]);
}

inline bool chk(int md)
{
    bool bF = false;
    int lS[6];
    for (int i = 1; i <= n - md + 1 && !bF; ++i)
    {
        int cnt = 0;
        for (int j = 0; j < m && cnt <= k; ++j)
        {
            int iST = log2(md);
            if ((1 << iST) < md)
                lS[j] = max(ST[iST][j][i], ST[iST][j][i + md - (1 << iST)]);
            else
                lS[j] = ST[iST][j][i];
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
    freopen("IN.txt", "r", stdin);

    while (scanf("%d %d %d", &n, &m, &k) != EOF)
    {
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d", &ST[0][j][i]);
        buildST();
        memset(S, 0, sizeof(S));
        int l = 1, r = n;
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
