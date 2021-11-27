# 🔗
<a href="https://www.luogu.com.cn/problem/P2522"><img src="https://img-blog.csdnimg.cn/20210608131244650.png"></a>

# 💡
题意让求:  
<img src="https://latex.codecogs.com/svg.image?f(k)=\sum_{x=A}^B\sum_{y=C}^D[gcd(x,y)=k]" title="f(k)=\sum_{x=A}^B\sum_{y=C}^D[gcd(x,y)=k]" />  
  
为了满足：  
<img src="https://latex.codecogs.com/svg.image?F(k)=\sum_{n|d}f(d)" title="F(k)=\sum_{n|d}f(d)" />  
  
设：  
<img src="https://latex.codecogs.com/svg.image?F(k)=\sum_{x=A}^B\sum_{x=C}^D[k|gcd(x,y)]" title="F(k)=\sum_{x=A}^B\sum_{x=C}^D[k|gcd(x,y)]" />  
  
为使枚举的<img src="https://latex.codecogs.com/svg.image?x,y" title="x,y" />均为<img src="https://latex.codecogs.com/svg.image?k" title="k" />的倍数  
令<img src="https://latex.codecogs.com/svg.image?x'&space;=&space;\frac&space;xk,\quad&space;y'&space;=&space;\frac&space;yk" title="x' = \frac xk,\quad y' = \frac yk" />，我们枚举倍数  
则$F(k)=\sum_{x'=\frac{A - 1}{k}}^{\frac Bk}\sum_{y'=\frac{C-1}{k}}^{\frac Dk}=(\left \lfloor \frac Bk \right \rfloor-\left \lfloor \frac{A-1}k \right \rfloor)*(\left \lfloor \frac Dk\right \rfloor -\left \lfloor \frac{C-1}k \right \rfloor)$  
  
根据莫比乌斯反演定理得：  
<img src="https://latex.codecogs.com/svg.image?f(k)=\sum_{k|d}\mu(\frac&space;dk)F(d)" title="f(k)=\sum_{k|d}\mu(\frac dk)F(d)" />  
为了使枚举到的d均为k的倍数  
我们设<img src="https://latex.codecogs.com/svg.image?d'&space;=&space;\frac&space;dk\quad&space;H'=\frac&space;Hk" title="d' = \frac dk\quad H'=\frac Hk" />，此时<img src="https://latex.codecogs.com/svg.image?d=d'k" title="d=d'k" />  
  
则<img src="https://latex.codecogs.com/svg.image?f(k)=\sum_{d'=1}^{min(\frac&space;Bk,\frac&space;Dk)}\mu(d')F(d'k)" title="f(k)=\sum_{d'=1}^{min(\frac Bk,\frac Dk)}\mu(d')F(d'k)" />  
  
<img src="https://latex.codecogs.com/svg.image?\because&space;F(d'k)=(\left&space;\lfloor&space;\frac&space;B{d'k}&space;\right&space;\rfloor-\left&space;\lfloor&space;\frac{A-1}{d'k}&space;\right&space;\rfloor)*(\left&space;\lfloor&space;\frac&space;D{d'k}\right&space;\rfloor&space;-\left&space;\lfloor&space;\frac{C-1}{d'k}&space;\right&space;\rfloor" title="\because F(d'k)=(\left \lfloor \frac B{d'k} \right \rfloor-\left \lfloor \frac{A-1}{d'k} \right \rfloor)*(\left \lfloor \frac D{d'k}\right \rfloor -\left \lfloor \frac{C-1}{d'k} \right \rfloor" />  
  
令<img src="https://latex.codecogs.com/svg.image?A'=\frac{A-1}k,\quad&space;B'=\frac&space;Bk,\quad&space;C'=\frac{C-1}k,\quad&space;D'=\frac&space;Dk" title="A'=\frac{A-1}k,\quad B'=\frac Bk,\quad C'=\frac{C-1}k,\quad D'=\frac Dk" />  
  
<img src="https://latex.codecogs.com/svg.image?\therefore&space;f(k)=\sum_{d'=1}^{min(B',D')}\mu(d')(\left&space;\lfloor&space;\frac&space;{B'}{d'}&space;\right&space;\rfloor-\left&space;\lfloor&space;\frac{A'}{d'}&space;\right&space;\rfloor)(\left&space;\lfloor&space;\frac&space;{D'}{d'}\right&space;\rfloor&space;-\left&space;\lfloor&space;\frac{C'}{d'}&space;\right&space;\rfloor" title="\therefore f(k)=\sum_{d'=1}^{min(B',D')}\mu(d')(\left \lfloor \frac {B'}{d'} \right \rfloor-\left \lfloor \frac{A'}{d'} \right \rfloor)(\left \lfloor \frac {D'}{d'}\right \rfloor -\left \lfloor \frac{C'}{d'} \right \rfloor" />  
  
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll maxn = 2e6 + 10;//杜教筛的安全maxn

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


map<ll, ll> S;//杜教筛处理出的前缀和


inline ll SUM(ll x){//杜教筛
        if(x < maxn) return sum[x];
        if(S[x]) return S[x];
        ll res = 1;
        for(ll L = 2, R; L <= x; L = R + 1){
                R = MIN(x, g(x, L));
                res -= (R - L + 1) * SUM(x / L);//模数相减会出负数，所以加上一个mod
        }return S[x] = res;
}

inline void solve(){
        ll A, B, C, D, K; cin >> A >> B >> C >> D >> K;
        A = (A - 1) / K, B = B / K, C = (C - 1) / K, D = D / K;
        ll n = MIN(B, D);
        ll res = 0;
        for(ll l = 1, r; l <= n; l = r + 1){
                ll cmp1 = (A / l)? MIN(g(A, l), g(B, l)) : g(B, l);//防止除0
                ll cmp2 = (C / l)? MIN(g(C, l), g(D, l)) : g(D, l); //防止除0
                r = MIN(cmp1, cmp2);//确定块右端点

                res += (sum[r] - sum[l - 1]) * (B / l - A / l) * (D / l - C / l);//公式
        }cout << res << endl;
}

CHIVAS_{Mobius();
        ll cass;
        EACH_CASE(cass){
                solve();
        }
        _REGAL;
}
```
