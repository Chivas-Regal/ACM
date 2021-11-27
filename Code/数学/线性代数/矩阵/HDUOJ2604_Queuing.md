# 🔗
http://acm.hdu.edu.cn/showproblem.php?pid=2604

# 💡


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  
  
```cpp
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <queue>
#include <cmath>
#define fir(i, a, n) for (int i = a; i <= n; i++)
#define rif(i, a, n) for (int i = a; i >= n; i--)
#define mm(a, b) memset(a, b, sizeof(a))
#define SP system("pause")
typedef long long ll;
const int INF = 0x7FFFFFFF;
const double G = 10;
const double eps = 1e-6;
const double PI = acos(-1.0);
using namespace std;

ll n=4;
ll l,mod;
struct Mat{
    ll m[10][10];
    Mat(ll flag){
        fir(i,1,n)
            fir(j,1,n)
                m[i][j]=flag*(i==j);
    }
    Mat Mul(Mat a,Mat b)
    {
        Mat ans(0);
        fir(i,1,n)
            fir(j,1,n)
                fir(k,1,n)
                    ans.m[i][j]=(ans.m[i][j]+a.m[i][k]*b.m[k][j]%mod)%mod;
        return ans;
    }
    Mat ksm(Mat a,ll b){
        Mat ans(1);
        while(b){
            if(b&1) ans=Mul(ans,a);
            a=Mul(a,a);
            b>>=1;
        }
        return ans;
    }
};

int main(){
    ll a[5];
    a[1]=2;a[2]=4;a[3]=6;a[4]=9;
    while(scanf("%lld%lld",&l,&mod)==2){
        if(l<=4) 
        {
            printf("%lld\n",a[l]%mod);
            continue;
        }
        Mat cur(0);
        cur.m[1][1]=cur.m[1][3]=cur.m[1][4]=1;
        cur.m[1][2]=0;
        fir(i,2,4)
            fir(j,1,4)
                cur.m[i][j]=1*(i-1==j);
        cur=cur.ksm(cur,l-4);
        ll ans=0;
        fir(i,1,4) ans=(ans+cur.m[1][i]*a[n-i+1]%mod)%mod;
        printf("%lld\n",ans);
    }
}
```
