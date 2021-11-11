# 🔗
<a href="https://codeforces.com/gym/102800/attachments"><img src="https://i.loli.net/2021/11/11/vqLZV6SGARBt38T.png"></a>

# 💡
一个埃氏筛的思想  
从  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" />  枚举  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  然后改变  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" />  的倍数的话  
每个数有多少个因数就会被筛几次  
  
我们设  <img src="https://latex.codecogs.com/svg.image?\inline&space;dv[i]" title="\inline dv[i]" /> 表示  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 的因数个数  
那么一个位置在  <img src="https://latex.codecogs.com/svg.image?\inline&space;(i,j)" title="\inline (i,j)" /> 的元素会被筛  <img src="https://latex.codecogs.com/svg.image?\inline&space;dv[i]\times&space;dv[j]" title="\inline dv[i]\times&space;dv[j]" /> 次  
为了使一个位置的元素筛奇数次，则  <img src="https://latex.codecogs.com/svg.image?\inline&space;i" title="\inline i" /> 和  <img src="https://latex.codecogs.com/svg.image?\inline&space;j" title="\inline j" /> 都具有奇数个因数才可以  
性质：具有奇数个因数的数都是完全平方数  
所以我们计算  <img src="https://latex.codecogs.com/svg.image?\inline&space;\left\lfloor\sqrt[]{n}\right\rfloor\times\left\lfloor\sqrt{m}\right\rfloor" title="\inline \left\lfloor\sqrt[]{n}\right\rfloor\times\left\lfloor\sqrt{m}\right\rfloor" /> 即可

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                ll n, m; cin >> n >> m;
                cout << (ll)sqrt(n) * (ll)sqrt(m) << endl;
        }
}
```
