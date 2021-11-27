# 🔗
<a href="https://codeforces.com/contest/1594/problem/B"><img src="https://i.loli.net/2021/10/09/RMkqpLPQY5TFEr1.png"></a>

# 💡
对一个b进行分割  
首先看一下按顺序的排列情况：  
0 (1)  
1 0+1 (2)   
2 0+2 1+2 0+1+2 (4)   
3 0+3 1+3 2+3 0+1+3 0+2+3 1+2+3 0+1+2+3 (8)  
...  
首先想到对b进行查找，看看是存在于哪一组（设为bas）中  
然后`b -= (1ll << bas)`  
可以发现剩下的也就是被拆过之后的值，可以继续进行分割，然后查找  
那么每次 `res` 也就是加上 a^bas，直到b被拆到0  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int mod = 1e9 + 7;

inline ll ksm ( ll a, ll b ) {
	ll res = 1;
	while ( b ) {
		if ( b & 1 ) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

inline void Solve() {
	ll a, b; cin >> a >> b;
	ll res = 0;
	while ( b > 0 ) {
		ll bas = 0, sum = 0;
		while ( sum + (1ll << bas) < b ) {
			sum += (1ll << bas);
			bas ++;
		}
		res = (res + ksm(a, bas)) % mod;
		b -= (1ll << bas);
	}
	cout << res << endl;

}

int main () {
	int cass; cin >> cass; while ( cass -- ) {
		Solve();
	}
        return 0;
}
```
