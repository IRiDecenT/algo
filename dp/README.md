## DP

### 1. [三步问题](https://leetcode.cn/problems/three-steps-problem-lcci/) 2023.10.25

1. 状态表示
    经验（以某个位置为结尾/以某个位置为开始） + 题目要求
    dp[i] ： 到达i位置时（第i个台阶），一共有多少种方法

2. 状态转移方程
    以i位置的状态，**最近的一步**，来划分问题
    - 从 i - 1 / i - 2 / i - 3 三种位置到 i 位置

    dp[i] = dp[i-1] + dp[i-2] + dp[i-3]

3. 初始化
    dp[1] = 1
    dp[2] = 2
    dp[3] = 4

4. 填表顺序
   从左往右

5. 返回值
   dp[n]


```cpp{.line-numbers}
class Solution {
public:
    int waysToStep(int n) {
        // 1. 创建dp表
        // 2. 初始化
        // 3. 填表
        // 4. 返回值

        const int MOD = 1e9 + 7;

        // 处理边界条件
        if(n == 1 || n == 2) return n;
        if(n == 4) return 4;

        vector<int> dp(n+1);
        dp[1] = 1, dp[2] = 2, dp[3] = 4;
        for(int i = 4; i <= n; ++i)
            dp[i] = ((dp[i - 1] + dp[i - 2]) % MOD + dp[i - 3]) % MOD;
        return dp[n];
    }
};
```


### 2. [使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/) 2023.10.26


#### 解法1:

1. 状态表示
    经验 + 题目要求
    以i位置为结尾，+ 具体题目要求
    dp[i]表示：到达i位置时的最小花费

2. 状态转移方程
    用之前或者之后的状态推导出dp[i]的值，经验告诉我们根据最近的一步来划分问题
    到达i位置有两种情况：从i-1或者i-2位置支付对应的钱到达i位置
    - 到达 i - 1 ，支付cost[i-1]，走一步
    - 到达 i - 2， 支付cost[i-2]，走两步

    dp[i] = min{ dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]}

3. 初始化
    保证填表的时候不越界，由几个易推导的初值滚动求解
    dp[0] = dp[1] = 1

4. 填表顺序
    保证求dp[i]的时候dp[i-1],dp[i-2]已经求出
    从左往右

5. 返回值
    dp[n]

```cpp{.line-numbers}
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1);
        dp[0] = dp[1] = 0;
        for(int i = 2; i <= n; i++)
            dp[i] = min((dp[i-1] + cost[i-1]),(dp[i-2] + cost[i-2]));
        return dp[n];
    }
};
```

#### 解法2:

1. 状态表示
    经验 + 题目要求
    以i位置为起点，+ 具体题目要求
    dp[i]表示：从i位置出发到达楼顶此时的最小花费

2. 状态转移方程

    dp[n] = 0
    dp[n-1] = cost[n-1]
    dp[n-2] = cost[n-2]

    支付cost[i]后走一步或者走两步（看哪一种的花费少）

    dp[i] = min{dp[i+1] + cost[i], dp[i+2] + cost[i]} = min{dp[i+1], dp[i+2]} + cost[i]

3. 初始化
    保证填表的时候不越界，由几个易推导的初值滚动求解
    dp[n] = 0
    dp[n-1] = cost[n-1]
    dp[n-2] = cost[n-2]

4. 填表顺序
    保证求dp[i]的时候dp[i+1],dp[i+2]已经求出
    从右往左

5. 返回值
    min{dp[0], dp[1]}

```cpp{.line-numbers}
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        // dp[i]表示：从i位置出发到达楼顶此时的最小花费
        // 按照这种状态表示，dp表只需要开和cost同等大小
        vector<int> dp(n);
        dp[n-1] = cost[n-1];
        dp[n-2] = cost[n-2];
        for(int i = n - 3; i >= 0; --i)
        {
            dp[i] = min(dp[i+1], dp[i+2]) + cost[i];
        }
        return min(dp[0], dp[1]);
    }
};
```


### 3. [解码方法](https://leetcode.cn/problems/decode-ways/) 2023.10.30

1. 状态表示

    根据经验 + 题目要求

    经验：以i位置为结尾/开始 巴拉巴拉

    dp[i] : 以i位置为结尾时，解码的方法总数

2. 状态转移方程

    经验：根据最近的一步划分问题

    情况1：单独考虑i位置的字符s[i]来解码 成功（'1' <= s[i] <= '9', dp[i-1]） or 失败 (0)

    情况2：s[i-1]与s[i]两者结合去解码 成功( 10 <= s[i-1]*10 + s[i-1] <= 26>, 不能有前导零，所以左边区间端点为10而不是1，dp[i-2]) or 失败(0)

    dp[i] = dp[i-1] + dp[i-2] (两者情况对应成功加对应的，否则加零)


3. 初始化

    保证填表的时候不越界

    dp[0] = 1（成功）or 0（失败）

    dp[1] = 2（都成功） or 1（两种成功其一） or 0（均失败）

4. 填表顺序

    从左往右

5. 返回值

    dp[n-1], n = 字符串长度

```cpp{.line-numbers}
class Solution {
public:
    int numDecodings(string s) {
        // 创建dp表
        // 初始化
        // 填表
        // 返回值
        int n = s.size();
        if(n == 0)  return 0;

        vector<int> dp(s.size(), 0);
        if(s[0] >= '1' && s[0] <= '9')
            dp[0] = 1;
        else
            dp[0] = 0;
        // 处理边界情况 需要考虑n = 1的情况
        if(n == 1) return dp[n-1];

        int two_digit = (s[0] - '0') * 10 + (s[1] - '0');
        if(two_digit >= 10 && two_digit <=26) dp[1] += 1;
        if(s[0] != '0' && s[1] != '0')  dp[1] += 1;

        for(int i = 2; i < n; ++i)
        {
            two_digit = (s[i-1] - '0') * 10 + (s[i] - '0');
            if(s[i] <= '9' && s[i] >= '1' )     dp[i] += dp[i-1];
            if(two_digit >= 10 && two_digit <= 26)      dp[i] += dp[i-2];
        }
        // for debug
        // for(auto e : dp)
        //     cout << e << " ";
        return dp[n-1];
    }
};
```

#### 复杂初始化过程的优化

发现上一段代码在初始化的时候比较复杂，一开始这个初始化的判断条件搞错，debug了好久orz 🤡

而且初始化的逻辑和我们在循环中填表的逻辑类似，我们可以将这个初始化的过程优化到循环里

具体的做法是在dp表前面加一个虚拟节点，原来的dp表为dp[0,n-1], 现在的dp表变为dp[0,n]，将原来的表中下标为0的位置映射到下标1的位置，1映射到2以此类推，新表中的下标0为虚拟节点

但是需要注意⚠️两点：

1. 虚拟节点放的初始值，要保证后面的填表是正确的
    对于很多问题，虚拟节点放的初始值位往往为0，但是❗️对于该问题，这个值为1！！！

    为什么？🧐

    循环填表的逻辑依据的是状态转移方程，即dp[i] = dp[i-1] + dp[i-2] (两者情况对应成功加对应的，否则加零)，此处影响的值为dp[2]

    即 dp[2] = dp[0] + dp[1] (两者情况对应成功加对应的，否则加零)

    加dp[1]: 说明该情况下s[1]不为‘0’

    加dp[0]: 说明s[0]与s[1]组合能成功译码，这个属于一种译码方式，都能成功译码了，总不能dp[0] = 0 加0呀，这个情况下要加1，故dp[0] = 1 (简单理解：就是什么时候用到dp[0]？是在能成功译码的时候用到，用到dp[0]代表其是一种合法译码方式，所以dp[0] = 1)

2. 下标的映射关系
    dp[i] 对应 s[i-1]

改进后的代码

```cpp{.line-numbers}
class Solution {
public:
    int numDecodings(string s) {
        // 创建dp表
        // 初始化
        // 填表
        // 返回值
        int n = s.size();
        if(n == 0)  return 0;
        // 多开一个空间增加虚拟节点
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        if(s[0] != '0') dp[1] = 1;
        // 处理边界情况 需要考虑n = 1的情况
        // 注意下标的映射关系
        if(n == 1) return dp[1];
        for(int i = 2; i <= n; ++i)
        {
            int two_digit = (s[i-2] - '0') * 10 + (s[i-1] - '0');
            if(s[i-1] <= '9' && s[i-1] >= '1' )     dp[i] += dp[i-1];
            if(two_digit >= 10 && two_digit <= 26)      dp[i] += dp[i-2];
        }
        // for debug
        // for(auto e : dp)
        //     cout << e << " ";
        return dp[n];
    }
};
```


### 4.[不同路径](https://leetcode.cn/problems/unique-paths/)

1. 状态表示

    经验 + 题目要求

    经验：以某一个位置为结尾/开始

    这里我们以[i,j]为结尾，dp[i][j]表示走到[i,j]位置的时候，一共有多少种方式

2. 状态转移方程

    经验：根据最近的一步，划分问题

    走到ij位置，最近的一步要么从上面来，要么从左边来

    dp[i][j] 要么从d[i-1][j]来，要么从dp[i][j-1]来

    dp[i][j] = dp[i-1][j] + dp[i][j-1]

3. 初始化

    使得填表的时候不越界，增加虚拟节点，加上一列一行（左上边的半圈）

    注意⚠️

    - 虚拟节点中的值，保证后面填表的结果时正确的，在该问题中虚拟节点中的值为0即可（但是对于dp[1][1]中的上面一个或者左边一个两者其一设置为1即可）
    - 下标的映射关系

4. 填表顺序

    从上往下填每一行

    每一行从左往右

5. 返回值

    dp[m][n]

```cpp{.line-numbers}
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        dp[0][1] = 1;
        for(int i = 1; i <= m; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m][n];
    }
};
```