# 🔗
<a href="https://www.luogu.com.cn/problem/P3455"><img src="https://img-blog.csdnimg.cn/20210609173007312.png"></a>

# 💡
题意让求:  
<img src="https://latex.codecogs.com/svg.image?\sum\limits_{x=1}^a\sum\limits_{y=1}^b[gcd(x,&space;y)=k]" title="\sum\limits_{x=1}^a\sum\limits_{y=1}^b[gcd(x, y)=k]" />  
  
我们只需要设置：  
<img src="https://latex.codecogs.com/svg.image?f(k)=\sum\limits_{x=1}^a\sum\limits_{y=1}^b[gcd(x,&space;y)=k]" title="f(k)=\sum\limits_{x=1}^a\sum\limits_{y=1}^b[gcd(x, y)=k]" />  
  
为使<img src="https://latex.codecogs.com/svg.image?F(n)=\sum\limits_{n|d}f(d)" title="F(n)=\sum\limits_{n|d}f(d)" />成立  
  
我们设置  
<img src="https://latex.codecogs.com/svg.image?F(k)=\sum\limits_{x=1}^a\sum\limits_{y=1}^b[k|gcd(x,&space;y)]" title="F(k)=\sum\limits_{x=1}^a\sum\limits_{y=1}^b[k|gcd(x, y)]" />  
  
为了准确计算所有<img src="https://latex.codecogs.com/svg.image?[k|gcd(x,y)]=1" title="[k|gcd(x,y)]=1" />的情况  
我们用<img src="https://latex.codecogs.com/svg.image?x'=\frac&space;xk,\quad&space;y'=\frac&space;yk" title="x'=\frac xk,\quad y'=\frac yk" />来表示我们枚举的都是k的倍数  
  
则此时<img src="https://latex.codecogs.com/svg.image?F(k)=\sum\limits_{x'=1}^{\frac&space;ak}\sum\limits_{y'=1}^{\frac&space;bk}1&space;=&space;\left&space;\lfloor&space;\frac&space;ak&space;\right&space;\rfloor&space;*&space;\left&space;\lfloor\frac&space;bk&space;&space;\right&space;\rfloor" title="F(k)=\sum\limits_{x'=1}^{\frac ak}\sum\limits_{y'=1}^{\frac bk}1 = \left \lfloor \frac ak \right \rfloor * \left \lfloor\frac bk \right \rfloor" />  
  
根据莫比乌斯反演定理得  
<img src="https://latex.codecogs.com/svg.image?f(k)=\sum\limits_{k|d}\mu(\frac&space;dk)F(d)" title="f(k)=\sum\limits_{k|d}\mu(\frac dk)F(d)" />  
  
我们枚举k的倍数，所以设<img src="https://latex.codecogs.com/svg.image?d'=\frac&space;dk,\quad&space;d=d'k" title="d'=\frac dk,\quad d=d'k" />，枚举<img src="https://latex.codecogs.com/svg.image?d'" title="d'" />  
  
则<img src="https://latex.codecogs.com/svg.image?f(k)=\sum\limits_{d'=1}^{min(a,b)}\mu(d')F(d'k)" title="f(k)=\sum\limits_{d'=1}^{min(a,b)}\mu(d')F(d'k)" />  
  
<img src="https://latex.codecogs.com/svg.image?\because&space;F(d'k)=&space;\left&space;\lfloor&space;\frac&space;a{d'k}&space;\right&space;\rfloor&space;*&space;\left&space;\lfloor\frac&space;b{d'k}&space;&space;\right&space;\rfloor" title="\because F(d'k)= \left \lfloor \frac a{d'k} \right \rfloor * \left \lfloor\frac b{d'k} \right \rfloor" />  
  
我们设<img src="https://latex.codecogs.com/svg.image?a'=\frac&space;ak,\quad&space;b'=\frac&space;bk" title="a'=\frac ak,\quad b'=\frac bk" />  
则<img src="https://latex.codecogs.com/svg.image?F(d'k)=\left&space;\lfloor&space;\frac&space;{a'}{d'}&space;\right&space;\rfloor&space;*&space;\left&space;\lfloor\frac&space;{b'}{d'}&space;&space;\right&space;\rfloor" title="F(d'k)=\left \lfloor \frac {a'}{d'} \right \rfloor * \left \lfloor\frac {b'}{d'} \right \rfloor" />  
  
<img src="https://latex.codecogs.com/svg.image?\therefore&space;f(k)=\sum\limits_{d'=1}^{min(a,b)}\mu(d')\left&space;\lfloor&space;\frac&space;{a'}{d'}&space;\right&space;\rfloor&space;\left&space;\lfloor\frac&space;{b'}{d'}&space;&space;\right&space;\rfloor" title="\therefore f(k)=\sum\limits_{d'=1}^{min(a,b)}\mu(d')\left \lfloor \frac {a'}{d'} \right \rfloor \left \lfloor\frac {b'}{d'} \right \rfloor" />  
  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll maxn = 5e4 + 10;

ll mu[maxn];//Mobius函数表
vector<ll> prime;
ll isprime[maxn];
ll sum[maxn];//mu的前缀和

inline void Mobius(){//线性筛
        mu[1] = 1;//特判mu[i] = 1
        isprime[0] = isprime[1] = 1;
        for(ll i = 2; i < maxn; i ++){
                if(!isprime[i]) mu[i] = -1, prime.push_back(i);//质数的质因子只有自己，所以为-1
                for(ll j = 0; j < prime.size() && i * prime[j] < maxn; j ++){
                        isprime[i * prime[j]] = 1;
                        if(i % prime[j] == 0) break;
                        mu[i * prime[j]] = - mu[i];//积性函数性质： (i * prime[j])多出来一个质数因数(prime[j])，修正为 (-1) * mu[i]
                }
        }
        //剩余的没筛到的是其他情况，为0
        for(ll i = 1; i < maxn; i ++) sum[i] = sum[i - 1] + mu[i];//记录前缀和，为了整除分块
}

inline ll g(ll k, ll x){ return k / (k / x); }//整除分块的r值

inline void solve(){
        ll a, b, d; scanf("%lld%lld%lld", &a, &b, &d); a /= d, b /= d;
        ll res = 0;
        ll n = MIN(a, b);//求最小边界
        for(ll l = 1, r; l <= n; l = r + 1){
                r = MIN(n, MIN(g(a, l), g(b, l)));//解块
                res += (sum[r] - sum[l - 1]) * (a / l) * (b / l);//套公式
        }printf("%lld\n", res);
}

CHIVAS_{Mobius();
        int cass;
        scanf("%d", &cass);
        while(cass --){
                solve();
        }
        _REGAL;
}
```
