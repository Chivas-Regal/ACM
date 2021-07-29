//Nimm博弈，共有a1,a2…an, 若a1^a2^…an为1，
//(^为异或运算)则先手胜，否则后手胜
// http://acm.hdu.edu.cn/showproblem.php?pid=1849
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
typedef long long int ll;

int main()
{
	int M, i, k, a;
    while(scanf("%d", &M),M!=0)
    {
        scanf("%d", &k);
        M--;
        while(M--)
        {
            scanf("%d", &a);
            k = a ^ k;
        }
        if(k)
            printf("Rabbit Win!\n");
        else
            printf("Grass Win!\n");
    }
    return 0;
 } 
