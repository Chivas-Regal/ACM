# 🔗
<a href="https://codeforces.com/problemset/problem/1512/E"><img src="https://img-blog.csdnimg.cn/20210411092911826.png"></a>

# 💡
在[l,r]这个区间内既然每个数都不能被选超过一次，  
我们得到S的最小值Min=(1+r-l+1) * (r-l+1)/2（从1到r-l+1），最大值Max=(n+n-r+l+3) * (r-l+1)/2（从n-r+l到n），  
若不在这个区间内则输出"-1"  
  
而S可以由Min改变一些数得来，  
设cha=S-Min  
我们想尽可能的让每一个数都增加相同的数使得这个区间内的数保持连续且cha尽可能减小  
这个数就是cha/(r-l+1)  
因为这样可以不重复  
  
然后若cha减去这些增加的数还有剩余，  
就向前几个最大的数分配1使得cha=0也就是S等于这个集合的和  
因为几个最大的数都+1可以防止重复  
  
输出的时候，使用前、中、后三个数组保存，  
我们上面求得的[l,r]区间就是"中"数组  
并记录vis，使得每个数只能出现过一次  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
void solve()
{
    ll n, l, r, s;
    cin >> n >> l >> r >> s;
    ll Min = (1 + r - l + 1) * (r - l + 1) / 2;
    ll Max = (n + n - r + l) * (r - l + 1) / 2;
    if (s > Max || s < Min)
    {
        cout << "-1" << endl;
        return;
    }
    int cha = s - Min;
    vector<int> zhong;
    vector<int> qian;
    vector<int> hou;
    int pingduo = cha / (r - l + 1);//代表[1~(r-l+r)]每个数至少要加的数
    int len = r - l + 1;
    for (int i = 1; i <= len; i++)
        zhong.push_back(i+pingduo),cha-=pingduo;
    if (cha)//如果cha不为0，就最大的几个数+1直到cha=0
    {
        for (int i = zhong.size() - 1; cha && i >= 0; i--)
        {
            zhong[i]++;
            cha--;
        }
    }
    
    int vis[10000] = {0};//记录，防止重复
    for (int i = 0; i < zhong.size(); i++)
        vis[zhong[i]] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (qian.size() == l - 1)//前面的数是(l-1)个
            break;
        if (!vis[i])
            qian.push_back(i), vis[i] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        if (hou.size() == n - r)//后面的数是(n-r)个
            break;
        if (!vis[i])
            hou.push_back(i), vis[i] = 1;
    }

    //输出
    for (int i = 0; i < qian.size(); i++)
        cout << qian[i] << " ";
    for (int i = 0; i < zhong.size(); i++)
        cout << zhong[i] << " ";
    for (int i = 0; i < hou.size(); i++)
        cout << hou[i] << " ";
    cout << endl;
}
int main()
{
    int cass;
    each_cass(cass)
    {
        solve();
    }
    return 0;
}
```
