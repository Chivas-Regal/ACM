# 🔗
<a href="https://codeforces.com/problemset/problem/1511/C"><img src="https://img-blog.csdnimg.cn/20210413082830467.png"></a>

# 💡
题目中也说了，我们只需要移动id最小的找到的数就行，  
所以这个题分两步  
  
1.构造：记录每个数第一次出现的位置  
2.移动：我们输入x，将id[x]变成1。在此之前应该先将id比它小的数全后移1（因为插入）  
  
3e5的数据量我们用不到，  
因为我们只改变小于id[x]的数的位置，  
而我们每个数也就记录了那打头的数的位置，  
所以每次循环内只需要从1~50判断一次id[i]的大小即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int maxn = 3e5 + 10;
void solve()
{
    int n, m;
    cin >> n >> m;
    int id[55];
    for (int i = 0; i < 55; i++)
        id[i] = -1;//初始化为-1
    for (int i = 0, x; i < n; i++)
    {
    	cin >> x;
        if (id[x] == -1)
            id[x] = i+1;//记录一下位置
    }
    for (int i = 0, x; i < m; i++){
        cin >> x;
        cout << id[x] << " ";
        for (int j = 1; j <= 50; j++){
            if(id[j]<id[x])//小了说明会因本次移动而改变位置
                id[j]++;
        }
        id[x] = 1;
    }
}
 
int main()
{
    solve();
    return 0;
}
```
