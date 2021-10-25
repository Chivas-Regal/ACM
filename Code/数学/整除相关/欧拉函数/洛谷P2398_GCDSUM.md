# 🔗
<a href="https://www.luogu.com.cn/problem/P2398"><img src="https://img-blog.csdnimg.cn/c778e79a96624c4b89b12b9fbb8aff14.png"></a>

# 💡
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}&\sum\limits_{i=1}^n\sum\limits_{j=1}^ngcd(i,j)\\=&\sum\limits_{k=1}^nk\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[gcd(i,j)=k]\\=&\sum\limits_{k=1}^nk\sum\limits_{i=1}^{\left\lfloor\frac&space;nk\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac&space;nk\right\rfloor}[gcd(i,j)=1]\end{aligned}" title="\begin{aligned}&\sum\limits_{i=1}^n\sum\limits_{j=1}^ngcd(i,j)\\=&\sum\limits_{k=1}^nk\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}[gcd(i,j)=k]\\=&\sum\limits_{k=1}^nk\sum\limits_{i=1}^{\left\lfloor\frac nk\right\rfloor}\sum\limits_{j=1}^{\left\lfloor\frac nk\right\rfloor}[gcd(i,j)=1]\end{aligned}" />
在转化完之后变成了在 n / k 内求两个数互质的个数  
那么可以利用欧拉函数，不重复地计算任选两个数互质的个数，即1~n/k的phi和  
由于每个数的区间都一样所以会重复，就是将当前答案*2，减去重复的(1,1)  
对每一个结果乘k累加  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
namespace Number {
        const ll N = 2e6 + 10;
        bool notprime[N];
        ll phi[N];
        vector<ll> prime;
        ll sum[N];

        inline void Sieve () {
                notprime[1] = notprime[0] = phi[1] = 1;
                for ( ll i = 2; i < N; i ++ ) {
                        if ( !notprime[i] ) 
                                prime.push_back(i),
                                phi[i] = i - 1;
                        for ( ll j = 0; j < prime.size() && i * prime[j] < N; j ++ ) {
                                notprime[i * prime[j]] = 1;
                                if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break; }
                                else                     phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                        }
                }
                for ( ll i = 1; i < N; i ++ ) sum[i] = sum[i - 1] + phi[i];
        }
} using namespace Number;

int main () {
        ios::sync_with_stdio(false); Sieve ();
        ll n; cin >> n;
        ll res = 0;
        for ( ll k = 1; k <= n; k ++ ) {
                res += k * (sum[n / k] * 2 - 1);
        }
        cout << res << endl;
}
```
