# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7025"><img src="https://i.loli.net/2021/10/14/xdH39a52foTyMbl.png"></a>

# 💡
首先分析一下等差数列求和公式：<img src="https://latex.codecogs.com/svg.image?\frac{(l&plus;r)*(r-l&plus;1)}{2}" title="\frac{(l+r)*(r-l+1)}{2}" />  
如果正数超过两项，则必然会产生一个因数，所以只有正数三项不行  
  
**先考虑一项：**  
1.就是n是质数的情况，就输出1    
**然后考虑两项：**  
2.首先是只有两个数，即(n-1)+n和(n+1)+n有一个是质数，就可以输出2  
3.然后是正数部分多出来两个数，就是从i=n+1开始往后找，如果i+(i+1)是质数，就需要i*2+1长度的数列  
  
**然后考虑暴力数列和为一项：**  
4.可以预处理出来素数表后，找出第一个比n大的质数p，这个答案是p*2  
  
在非1、2情况下拿3和4出的答案进行比较，输出较小的那个  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
namespace primeNumber {
        const int N = 5e7 + 10;
        vector<int> prime;
        bool notprime[N];
        inline void Sieve () {
                notprime[0] = notprime[1] = 1; 
                for ( int i = 2; i < N; i ++ ) {
                        if ( !notprime[i] ) prime.push_back(i);
                        for ( int j = 0; j < prime.size() && i * prime[j] < N; j ++ ) {
                                notprime[i * prime[j]] = 1;
                                if ( i % prime[j] == 0 ) break;
                        }
                }
        }
} using namespace primeNumber;

inline void Solve () {
        int n; cin >> n;
        if ( n > 0 && notprime[n] == 0 ) { cout << 1 << endl; return; } 
        if ( n > 0 && (notprime[n + n + 1] == 0 || notprime[n + n - 1] == 0) ) { cout << 2 << endl; return; }

        int res = prime[upper_bound(prime.begin(), prime.end(), abs(n)) - prime.begin()] * 2;
        for ( int i = abs(n) + 1; i * 2 + 1 < N; i ++ ) {
                if ( notprime[i * 2 + 1] == 0 ) { cout << min(res, i * 2 + 1) << endl; return;}
        }
        cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        Sieve();
        int cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
}
```
