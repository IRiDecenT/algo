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