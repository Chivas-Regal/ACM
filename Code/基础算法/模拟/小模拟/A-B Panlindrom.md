# 🔗
<a href="https://codeforces.com/problemset/problem/1512/C"><img src="https://img-blog.csdnimg.cn/20210411072936231.png"></a>

# 💡
对于模拟题，考验的就是细心程度  
在字符串构造和判断中，我是先将字符串打造成易于我去操作的形式  
在本题中我先使得字符串是个回文串，如果在构造时发现有的地方确定不回文了，输出-1  
然后对已有的'0'和'1'计数，并在a和b中删去，如果a和b在计数的时候就有<0的了，就输出-1  
此时我们的'?'都是一对一对的或者中间有一个  
从[0~s.size()/2]进行修'?'，如果a和b有>=2的，就对这个位置设为'0'或'1'，并a-=2或b-=2，最后是对奇数长度的判断(奇数长度中心的'?'会没有被重载)，查看a和b是否有不为0的，并将该点设为'0'或'1'  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
void solve()
{
    int a, b;
    cin >> a >> b;
    string s;
    cin >> s;

    //使串回文
    for (int i = 0; i < s.size(); i++)
    {
        if (s[s.size() - 1 - i] != '?' && s[i] != '?' && s[s.size() - 1 - i] != s[i])//确定不回文的情况
        {
            cout << "-1" << endl;
            return;
        }
        if (s[s.size() - 1 - i] == '?')
            s[s.size() - 1 - i] = s[i];
    }

    //初步计数'0'和'1'
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '1')
            b--;
        else if (s[i] == '0')
            a--;
    }
    if(a<0||b<0){//计数不通过的情况
        cout << "-1" << endl;
        return;
    }

    //'?'的设置
    for (int i = 0; i < s.size() / 2; i++)
    {
        if(s[i]=='?')
        {
            if (a < 2 && b < 2)//没法设置的情况
            {
                cout << "-1" << endl;
                return;
            }
            if (a >= 2)
            {
                s[i] = s[s.size() - 1 - i] = '0';
                a -= 2;
            }
            else if (b >= 2)
            {
                s[i] = s[s.size() - 1 - i] = '1';
                b -= 2;
            }
        }
    }
    if(s.size()&1){
        if(a)
            s[s.size() / 2] = '0';
        else if(b)
            s[s.size() / 2] = '1';
    }
    cout << s << endl;
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
