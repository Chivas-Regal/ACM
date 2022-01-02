# 🔗
<a href="https://codeforces.com/gym/102900/problem/I "><img src="https://s2.loli.net/2022/01/02/MSEyRar7n56QceI.png"></a>

# 💡
这些点的排布有规律，所以我们分析一下所有可能的点对距离  
  
同圈：看看走直线和走曲线哪个更近，由于是等分，所以这两个都很好求出  
异圈：外圈的先走到小圈，然后看看走直线和走曲线哪个更近  
  
易知道，同圈上一个点访问该圈所有的点求出之后设为  <img src="https://latex.codecogs.com/svg.image?\inline&space;cur" title="\inline cur" /> ，外圈上一个点访问这圈所有点在这圈上走的距离是  <img src="https://latex.codecogs.com/svg.image?\inline&space;dir\times2\times&space;m+cur" title="\inline dir\times2\times&space;m+cur" />   
所以这道题的关键就在于遍历每一圈，求出这圈上一个点访问所有点的距离，然后用外圈所有的点套这个距离就行了  
  
那么我们就可以把问题分为“圈上选择走法”和“直线走法”  
圈上选择走法：  
从内圈向外遍历圈数，第  <img src="https://latex.codecogs.com/svg.image?\inline&space;dp" title="\inline i" /> 圈求出  <img src="https://latex.codecogs.com/svg.image?\inline&space;cur" title="\inline cur" /> ，该圈互相访问需要  <img src="https://latex.codecogs.com/svg.image?\inline&space;cur\times&space;m" title="\inline \frac{cur}{2}" /> ，比这圈层数大的点的个数为  <img src="https://latex.codecogs.com/svg.image?\inline&space;2\times&space;m\times(n-dp)" title="\inline 2\times&space;m" /> ，去访问这所有点在圈上选择走法总距离为  <img src="https://latex.codecogs.com/svg.image?\inline&space;2\times&space;m\times(n-dp)\times&space;cur" title="\inline " />   
  
直线走法：  
每一次外圈要访问该圈所有点都要先走到这圈，那么每一个点到这个圈的距离为  <img src="https://latex.codecogs.com/svg.image?\inline&space;1,2,\dots,n-dp" title="\inline 1,2,\dots,n-dp" /> ，每个点访问这圈所有点要走  <img src="https://latex.codecogs.com/svg.image?\inline&space;2\times&space;m" title="\inline n" /> 次  
总距离就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;2\times&space;m\times\frac{(1+n-dp)(n-dp)}{2}\times2\times&space;m" title="\inline 2\times&space;m\times\frac{(1+n-dp)(n-dp)}{2}\times2\times&space;m" />   
  
注意，当分割线数量不为  <img src="https://latex.codecogs.com/svg.image?\inline&space;1" title="\inline 1" /> 时，还有个所有点到圆心的距离  
也就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;2\times&space;m\times\frac{(1+n)n}{2}" title="\inline 2\times&space;m\times\frac{(1+n)n}{2}" />   
  
>C++ 精度一直出问题，所以换成 Java 来做

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
public class Main{
        static BigDecimal  mysol(int n, int m) {
                BigDecimal res1 = BigDecimal.ZERO, res2 = BigDecimal.ZERO; // 圈上选择，直接直线
                for ( int dp = 1; dp <= n; dp ++ ) { // 枚举第几圈
                        BigDecimal line = BigDecimal.valueOf(dp).multiply(BigDecimal.valueOf(2)).multiply(BigDecimal.valueOf(m)); // 走直线的话需要的步数
                        BigDecimal one_arc = BigDecimal.valueOf(dp).multiply(BigDecimal.valueOf(Math.PI)); // 一个弧
                        
                        BigDecimal cur = BigDecimal.ZERO; // 圈上每个点到该圈所有点的距离和
                        for ( int i = 1; i < m; i ++ ) {
                                if ( line.compareTo(one_arc.multiply(BigDecimal.valueOf(i))) == 1 ) cur = cur.add(one_arc.multiply(BigDecimal.valueOf(i)));
                                else cur = cur.add(line);
                        }
                        cur = cur.multiply(BigDecimal.valueOf(2));
                        cur = cur.add(line);
        
                        res1 = res1.add(cur.multiply(BigDecimal.valueOf(n).subtract(BigDecimal.valueOf(dp))).multiply(BigDecimal.valueOf(2))).add(cur); // 外圈和该圈所有点在该圈上移动的距离和
                        res2 = res2.add(BigDecimal.valueOf(m).multiply(BigDecimal.valueOf(1 + n - dp)).multiply(BigDecimal.valueOf(n - dp)).multiply(BigDecimal.valueOf(2 * m))); // 外圈到该圈需要的距离和
                }
                if ( m != 1 ) res2 = res2.add(BigDecimal.valueOf(m * n * (n + 1))); // 有圆心，要加所有点到圆心的距离和
                return res1.add(res2);
        }
        public static void main(String[] args) {
                Scanner input = new Scanner(System.in);
                int n = input.nextInt(), m = input.nextInt();
                String res =  String.format("%.10f", mysol(n, m));
                System.out.println(res);
        }
}
```
