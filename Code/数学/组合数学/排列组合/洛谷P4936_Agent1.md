# 🔗
<a href="https://www.luogu.com.cn/problem/P4936"><img src="https://i.loli.net/2021/11/14/Q5Y7Z8RilKTuLyV.png"></a>

# 💡
AB两队，每队必出一个人  
我们可以枚举每队谁必出，然后为了保证  <img src="https://latex.codecogs.com/svg.image?\inline&space;max\{A\}<min\{B\}" title="\inline max\{A\}<min\{B\}" /> 我们让每队出的两个人中间的数必不出，两侧的数选出  
这样的话就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times&space;2^{n-j})" title="\inline \sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times&space;2^{n-j})" />   
这是一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;O(n^2)" title="\inline O(n^2)" /> 的柿子，我们优化一下  
  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;\begin{aligned}&\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times&space;2^{n-j})\\=&\sum\limits_{i=1}^n\sum\limits_{j=0}^{n-i-1}(2^{i-1}\times&space;2^j)\\=&\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-i-2}(2^i\times&space;2^j)\\=&\sum\limits_{i=0}^{n-1}2^i\sum\limits_{j=0}^{n-i-2}2^j\\=&\sum\limits_{i=0}^{n-1}(2^i\times(2^{n-i-1}-1))\\=&\sum\limits_{i=0}^{n-1}(2^{n-1}-2^i)\\=&n2^{n-1}-(2^n-1)\end{aligned}" title="\inline \begin{aligned}&\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n(2^{i-1}\times&space;2^{n-j})\\=&\sum\limits_{i=1}^n\sum\limits_{j=0}^{n-i-1}(2^{i-1}\times&space;2^j)\\=&\sum\limits_{i=0}^{n-1}\sum\limits_{j=0}^{n-i-2}(2^i\times&space;2^j)\\=&\sum\limits_{i=0}^{n-1}2^i\sum\limits_{j=0}^{n-i-2}2^j\\=&\sum\limits_{i=0}^{n-1}(2^i\times(2^{n-i-1}-1))\\=&\sum\limits_{i=0}^{n-1}(2^{n-1}-2^i)\\=&n2^{n-1}-(2^n-1)\end{aligned}" />   
   
好了，这么一个  <img src="https://latex.codecogs.com/svg.image?\inline&space;O(logn)" title="\inline O(1)" /> 的柿子就出来了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
cout << (n * ksm(2, n - 1) % mod - (ksm(2, n) + mod - 1) % mod + mod) % mod << endl;
```
