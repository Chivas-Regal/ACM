# 🔗
<a href="https://www.luogu.com.cn/problem/P1829"><img src="https://i.loli.net/2021/10/29/thDkJ42B71fyEVF.png"></a>

# 💡
<img src="https://latex.codecogs.com/svg.image?(1)\\\begin{aligned}mian(n,m)=&\sum\limits_{i=1}^n\sum\limits_{j=1}^mlcm(i,j)\\=&\sum\limits_{k=1}^{mn}\sum\limits_{i=1}^n\sum\limits_{j=1}^m\frac&space;{i\times&space;j\times[(i,j)=k]}k\end{aligned}" title="(1)\\\begin{aligned}mian(n,m)=&\sum\limits_{i=1}^n\sum\limits_{j=1}^mlcm(i,j)\\=&\sum\limits_{k=1}^{mn}\sum\limits_{i=1}^n\sum\limits_{j=1}^m\frac {i\times j\times[(i,j)=k]}k\end{aligned}" />  
  
<img src="https://latex.codecogs.com/svg.image?i'=\frac&space;ik,\;j'=\frac&space;jk" title="i'=\frac ik,\;j'=\frac jk" />  
  
<img src="https://latex.codecogs.com/svg.image?{\color{red}main(n,m)}=\sum\limits_{k=1}^{mn}k\sum\limits_{i'=1}^{\left\lfloor\frac&space;nk\right\rfloor}\sum\limits_{j'=1}^{\left\lfloor\frac&space;mk\right\rfloor}i'\times&space;j'\times&space;[(i',j')=1]{\color{red}=\sum\limits_{k=1}^{mn}solve(\left\lfloor\frac&space;nk\right\rfloor,\left\lfloor\frac&space;mk\right\rfloor)}" title="{\color{red}main(n,m)}=\sum\limits_{k=1}^{mn}k\sum\limits_{i'=1}^{\left\lfloor\frac nk\right\rfloor}\sum\limits_{j'=1}^{\left\lfloor\frac mk\right\rfloor}i'\times j'\times [(i',j')=1]{\color{red}=\sum\limits_{k=1}^{mn}solve(\left\lfloor\frac nk\right\rfloor,\left\lfloor\frac mk\right\rfloor)}" />   

<img src="https://latex.codecogs.com/svg.image?(2)\\solve(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mi\times&space;j\times&space;[gcd(i,j)=1]" title="(2)\\solve(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mi\times j\times [gcd(i,j)=1]" />

<img src="https://latex.codecogs.com/svg.image?f(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[(i,j)=k]ij" title="f(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[(i,j)=k]ij" />

<img src="https://latex.codecogs.com/svg.image?F(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[k\mid(i,j)]ij" title="F(k)=\sum\limits_{i=1}^n\sum\limits_{j=1}^m[k\mid(i,j)]ij" />

<img src="https://latex.codecogs.com/svg.image?i',j'" title="i',j'" /> 枚举 <img src="https://latex.codecogs.com/svg.image?k" title="k" /> 倍数， <img src="https://latex.codecogs.com/svg.image?n'=\left\lfloor\frac&space;nk\right\rfloor,\;m'=\left\lfloor\frac&space;mk\right\rfloor,\;i'=\frac&space;ik,\;j'=\frac&space;jk,\;i=i'k,\;j=j'k" title="n'=\left\lfloor\frac nk\right\rfloor,\;m'=\left\lfloor\frac mk\right\rfloor,\;i'=\frac ik,\;j'=\frac jk,\;i=i'k,\;j=j'k" />

<img src="https://latex.codecogs.com/svg.image?F(k)=\sum\limits_{i'=1}^{n'}\sum\limits_{j'=1}^{m'}i'kj'k=k^2\frac{n'(1&plus;n')}2\frac{m'(1&plus;m')}2=k^2\frac{k^2n'(1&plus;n')m'(1&plus;m')}4" title="F(k)=\sum\limits_{i'=1}^{n'}\sum\limits_{j'=1}^{m'}i'kj'k=k^2\frac{n'(1+n')}2\frac{m'(1+m')}2=k^2\frac{k^2n'(1+n')m'(1+m')}4" /> 

<img src="https://latex.codecogs.com/svg.image?f(k)=\sum\limits_{k\mid&space;d}\mu(\frac&space;dk)F(d)" title="f(k)=\sum\limits_{k\mid d}\mu(\frac dk)F(d)" />

<img src="https://latex.codecogs.com/svg.image?{\color{red}solve(n,m)}=f(1)=\sum\limits_{d=1}^{mn}\mu(d)F(d)=\sum\limits_{d=1}^{mn}\mu(d)\frac{d^2\left\lfloor\frac&space;nd\right\rfloor(1&plus;\left\lfloor\frac&space;nd\right\rfloor)\left\lfloor\frac&space;md\right\rfloor(1&plus;\left\lfloor\frac&space;md\right\rfloor)}4{\color{red}=\sum\limits_{d=1}^{mn}\mu(d)d^2calc(\left\lfloor\frac&space;nd\right\rfloor,\left\lfloor\frac&space;md\right\rfloor)}" title="{\color{red}solve(n,m)}=f(1)=\sum\limits_{d=1}^{mn}\mu(d)F(d)=\sum\limits_{d=1}^{mn}\mu(d)\frac{d^2\left\lfloor\frac nd\right\rfloor(1+\left\lfloor\frac nd\right\rfloor)\left\lfloor\frac md\right\rfloor(1+\left\lfloor\frac md\right\rfloor)}4{\color{red}=\sum\limits_{d=1}^{mn}\mu(d)d^2calc(\left\lfloor\frac nd\right\rfloor,\left\lfloor\frac md\right\rfloor)}" /> 

<img src="https://latex.codecogs.com/svg.image?(3)\\calc(n,m)=\frac{n(1&plus;n)m(1&plus;m)}4" title="(3)\\calc(n,m)=\frac{n(1+n)m(1+m)}4" />

**综上所述**

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{aligned}&main(n,m)=\sum\limits_{k=1}^{mn}solve(\left\lfloor\frac&space;nk\right\rfloor,\left\lfloor\frac&space;mk\right\rfloor)\\&solve(n,m)=\sum\limits_{d=1}^{mn}\mu(d)d^2calc(\left\lfloor\frac&space;nd\right\rfloor,\left\lfloor\frac&space;md\right\rfloor)\end{aligned}\right." title="\left\{\begin{aligned}&main(n,m)=\sum\limits_{k=1}^{mn}solve(\left\lfloor\frac nk\right\rfloor,\left\lfloor\frac mk\right\rfloor)\\&solve(n,m)=\sum\limits_{d=1}^{mn}\mu(d)d^2calc(\left\lfloor\frac nd\right\rfloor,\left\lfloor\frac md\right\rfloor)\end{aligned}\right." />

<img src="https://latex.codecogs.com/svg.image?\left\{\begin{aligned}&(1)\quad&space;mian(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mlcm(i,j)\\&(2)\quad&space;solve(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mi\times&space;j\times&space;[gcd(i,j)=1]\\&(3)\quad&space;calc(n,m)=\frac&space;{n(1&plus;n)m(1&plus;m)}4\end{aligned}\right." title="\left\{\begin{aligned}&(1)\quad mian(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mlcm(i,j)\\&(2)\quad solve(n,m)=\sum\limits_{i=1}^n\sum\limits_{j=1}^mi\times j\times [gcd(i,j)=1]\\&(3)\quad calc(n,m)=\frac {n(1+n)m(1+m)}4\end{aligned}\right." />


剩下的就是利用这个公式进行两重数论分块写了






# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
namespace Number {
        const ll N = 1e7 + 10;
        const ll mod = 20101009;
        ll mu[N], sum[N];
        bool notprime[N];
        vector<ll> prime;
        inline ll ksm ( ll a, ll b ) {
                ll res = 1;
                while ( b ) {
                        if ( b & 1 ) res = res * a % mod;
                        a = a * a % mod;
                        b >>= 1;
                }
                return res;
        }
        inline void Sieve () {
                notprime[0] = notprime[1] = mu[1] = 1;
                for ( ll i = 2; i < N; i ++ ) {
                        if ( !notprime[i] ) 
                                prime.push_back(i),
                                mu[i] = -1;
                        for ( ll j = 0; j < prime.size() && prime[j] * i < N; j ++ ) {
                                notprime[i * prime[j]] = 1;
                                if ( i % prime[j] == 0 ) break;
                                mu[i * prime[j]] = -mu[i];
                        }
                }
                for ( int i = 1; i < N; i ++ ) sum[i] = (sum[i - 1] + (mu[i] + mod) * i % mod * i % mod) % mod;
        }
        inline ll g ( ll n, ll k ) { return n / (n / k); }
        inline ll inv ( ll x ) { return ksm(x, mod - 2); }
} using namespace Number;

inline ll Calc ( ll x, ll y ) {
        return (1 + x) * x % mod * (1 + y) % mod * y % mod * inv(4) % mod;
}

inline ll Solve (ll n, ll m, ll k) {
        n /= k, m /= k;
        ll mn = min ( m, n );
        ll res = 0;
        for ( ll l = 1, r; l <= mn; l = r + 1 ) {
                r = min(g(n, l), g(m, l));
                res = (res + (sum[r] - sum[l - 1] + mod) % mod * Calc(n / l, m / l) % mod) % mod;
        }
        return res;
}

int main () {
        ios::sync_with_stdio(false); Sieve ();
        ll n, m; cin >> n >> m;
        ll mn = min ( m, n );
        ll res = 0;
        for ( ll l = 1, r; l <= mn; l = r + 1 ) {    
                r = min(g(n, l), g(m, l));
                res = (res + ( l + r ) * ( r - l + 1 ) % mod * inv(2) % mod * Solve ( n, m, l ) % mod) % mod;
        }
        cout << res << endl;
}
```
