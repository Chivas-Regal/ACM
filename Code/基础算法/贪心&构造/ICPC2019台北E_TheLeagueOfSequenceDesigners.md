# 🔗
<a href="https://codeforces.com/gym/102460/attachments"><img src="https://s2.loli.net/2022/01/18/lVzb8C4uv1ByO7W.png"></a>

# 💡  
因为有数大小的限制，所以我们想让数列尽可能长，最长就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;2000" title="\inline 2000" />  
我们构建一个这样的数列  
 <img src="https://latex.codecogs.com/svg.image?\inline&space;-1,\underset{sum}{\underbrace{a_2,a_3,\dots,a_{1999}}} " title="\inline -1,\underset{sum}{\underbrace{a_2,a_3,\dots,a_{1999}}} " />   
 那么即可得出  
 我们设  <img src="https://latex.codecogs.com/svg.image?\inline&space;Natasha" title="\inline Natasha" /> 得出的结果是  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" /> ，那么  <img src="https://latex.codecogs.com/svg.image?\inline&space;Burce" title="\inline Burce" /> 得出的结果是  <img src="https://latex.codecogs.com/svg.image?\inline&space;x+k" title="\inline x+k" />   
 列出方程  
  <img src="https://latex.codecogs.com/svg.image?\inline&space;\left\{\begin{aligned}&1999(sum-1)=x+k\\&1998sum=k\end{aligned}\right.\Rightarrow&space;sum=k+1999" title="\inline \left\{\begin{aligned}&1999(sum-1)=x+k\\&1998sum=k\end{aligned}\right.\Rightarrow&space;sum=k+1999" />  
  那么就将  <img src="https://latex.codecogs.com/svg.image?\inline&space;1999+k" title="\inline 1999+k" /> 给  <img src="https://latex.codecogs.com/svg.image?\inline&space;sum" title="\inline sum" /> 分一下就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void Solve () {
        int k, l; cin >> k >> l;
        if ( l >= 2000 ) { cout << "-1" << endl; return; }
        cout << 1999 << endl << -1;

        int num0 = (k + 1999) % 1998;
        int num1 = 1998 - num0;
        int add = (k + 1999) / 1998;
        for ( int i = 0; i < 1998; i ++ ) {
                if ( i < num0 ) cout << " " << add + 1;
                else cout << " " << add;
        } cout << endl;
}
```
