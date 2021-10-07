# 🔗
<a href="https://codeforces.com/problemset/problem/1511/B"><img src="https://img-blog.csdnimg.cn/20210413081527267.png"></a>

# 💡
我们想控制gcd的长度为c，  
我们知道100和99的gcd为1，100和90的gcd为10，100和1000的gcd为100（100....0和9..90..0是我们可以方便控制gcd长度的数）  
  
所以构造只需分两种情况考虑：  
1.c=min(a,b)，代表c的长度等于其中一个，那么较大的数可以是较小的数的倍数，所以我们构造出来一个10 ^ a和10 ^ b就行  
2.c!=min(a,b)，那么我们控制c的长度时，可以将一个数设为99900..0，一个数设为1000...，含9的数所给出来的0的个数+1就是c的长度  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
void solve(){
    int a, b, c;
    cin >> a >> b >> c;
    if(c==min(a,b)){//两个10000....
        string rsa="1", rsb="1";
        for (int i = 1; i < a; i++)
            rsa += "0";
        for (int i = 1; i < b; i++)
            rsb += "0";
        cout << rsa << " " << rsb << endl;
    }
    else {
        string rsa="1", rsb="";
        for (int i = 1; i < a; i++)//a为1000....
            rsa += "0";
        for (int i = 0; i < b - c+1;i++)//b为99900....
            rsb += "9";
        for (int i = 0; i < c-1; i++)
            rsb += "0";
        cout << rsa << " " << rsb << endl;
    }
}
 
int main(){
    int cass;
    each_cass(cass){
        solve();
    }
    return 0;
}
```
