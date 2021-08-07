# 🔗


# 💡
可以看做是一类区间跳跃  
我们可以发现，数字编号最多到50  
也能发现因为每次我们都把数值固定位置最前的元素移动到整个数组最前面  
那么就能知道我们每次移动的就那最多50个数字  
暴力就行了，一个位置的数字代表整个同数字的元素，每次挑选出那个元素x后，从1到50判断一下哪个的位置小于x，都向后推1即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

using namespace std;

int n, q;
int id[51];

int main () {

        cin >> n >> q;
        for ( int i = 1, a; i <= n; i ++ ) {
                cin >> a;
                if ( !id[a] ) id[a] = i;
        }
        for ( int i = 1, t; i <= q; i ++ ) {
                cin >> t;
                cout << id[t] << " ";

                for ( int j = 1; j <= 50; j ++ ) if ( id[j] < id[t] ) id[j] ++;
                id[t] = 1;
        }

        return 0;
}



```
