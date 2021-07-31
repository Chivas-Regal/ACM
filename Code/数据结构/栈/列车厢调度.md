# 🔗
https://pintia.cn/problem-sets/1378951666713001984/problems/1378951732962107393

# 💡
用STL库函数以及一个期望变量对我们想要插入的元素选择合适的插入时间以及顺序


# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >  

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<string>path;
int main()
{
    string a;
    string b;
    cin>>a>>b;
    string c;
    int id=0;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]==b[id])
        {
            path.push_back("1->2");
            id++;
        }
        else c+=a[i],path.push_back("1->3");
        while(c.size()&&c[c.size()-1]==b[id]) c.erase(c.end()-1,c.end()),id++,path.push_back("3->2");
    }
    if(c.size())
    {
        printf("Are you kidding me?\n");
        return 0;
    }
    for(int i=0;i<path.size();i++) cout<<path[i]<<endl;
}
```
