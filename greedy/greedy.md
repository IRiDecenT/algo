[TOC]

## 贪心算法


### 基本要素

1. 最优子结构性质
2. 贪心选择性质

### 1. 活动安排问题

#### 1.1 问题描述

> $n$个活动的集合$C=\left\{1,2,3···,n\right\}$，其中每一个活动都要占用一个资源（如会议室）而**在同一个时间内只能有一个活动使用该资源**，每一个活动都有使用资源的开始时间 $s_i$ 和结束时间 $f_i$ 且 $\left(s_i \le f_i \right)$。 如果选择了活动 $i$ 使用会议室，在半开区间$\left[s_i,f_i \right)$内占用该资源。如果 $[s_i,f_i)$ 与 $[s_j,f_j)$ 不相交，即一个活动的结束时间早于另一个活动的开始时间，活动 $i$ 与 $j$ 是相容的。目标是选出在所给的活动集合 $C$ 中选出**最大的相容活动子集**，即**尽可能选择更多的活动来使用该资源**

#### 1.2 问题分析

1. $n$ 个活动的集合$C=\{(s_0,f_0),(s_1,f_1),···,(s_{n-1},f_{n-1})\}$
2. 活动 $i$ 的资源使用时间 $f_i-s_i$
3. 活动 $i$ 与活动 $j$ 相容使用资源的条件：$s_i \ge f_j$ 或者 $f_i \le s_j$ (即 $j$ 在前或者 $i$ 在前)
4. 满足相容条件的活动的子集都是活动安排问题的解，目标是找到集合 $C$ 的最大相容子集（最优解）

我们有以下几种选择的策略：
1. 开始时间早的活动优先安排
2. 结束时间早的活动优先安排
3. 使用时间短的活动优先安排

###### 引例：四个班级活动争用教室A

<div class="center">


| 班级  | 开始时间——结束时间 |   活动   |
| :---: | :----------------: | :------: |
|  1班  |     8:00-12:00     |   上课   |
|  2班  |     8:30-10:30     |   讲座   |
|  3班  |    11:00-11:30     |   开会   |
|  4班  |    10:40-11:20     | 竞选活动 |

</div>

1. 按照第一种贪心策略——优先选择开始时间早的：
   - 只能选择1班来使用教室A，即解的集合为： $\left\{1\right \}$
2. 按照第二种贪心策略——优先选择结束时间早的：
   - 可以安排2、4班使用教室A，即解的集合为： $\left\{2，4\right \}$
3. 按照第三种贪心策略——优先选择所花费时间短的：
   - 可以安排3班使用教室A，即解的集合为： $\left\{3\right \}$  

我们可以发现在这个简单的例子中第二种贪心策略是最佳的。该如何理解这个最佳的策略呢？“结束时间 = 开始时间 + 使用时间” 我们可以做出这样的一个推断：“开始时间越早，使用时间越短，则结束时间越早”，结束时间早的优先安排的策略是最好的贪心策略

**最优贪心策略：优先选择结束时间早的活动**

#### python实现

```python {.line-numbers}
def meetingGreedySelect(meetings):
    result = [False for i in range(len(meetings))]
    #lambda表达式，meeting列表元素的第三个值(结束时间为键值排序)
    meetings.sort(key=lambda x:x[2])
    #按结束时间升序排列后第一个活动为贪心选择
    prev=meetings[0][0]-1
    result[prev] = True
    for cur in range(1,len(meetings)):
        # 前一个被选择的结束时间早于当前cur任务的开始时间，即meetings[cur][0]号活动可选
        if meetings[prev][2] <= meetings[cur][1]:
            #注意我们活动下表从0开始，而解向量的下表从0开始
            result[meetings[cur][0]-1] = True
            prev = cur
    return result

if __name__ == '__main__':
    meetings = [(1,3,6),(2,1,4),(3,5,7),(4,2,5),(5,5,9),
                (6,3,8),(7,8,11),(8,6,10),(9,8,12),(10,12,14)]  
    result = meetingGreedySelect(meetings)
    print("最优解为：")
    for i in range(len(result)):
        if result[i]:
            print("活动",i+1,end=" ")
    print("\n最优解选择活动的总数为:",result.count(True))     
```

#### c++实现

```cpp {.line-numbers}
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct task
{
    task(int id=0, int s=0, int e=0)
        :_id(id),_start(s),_end(e)
    {}
    bool operator<(const task& t)const { return _end < t._end;}
    //重载operator<,以支持仿函数greater<>()
    //来创建以结束时间为比较值的优先级队列即小根堆
    bool operator>(const task& t)const { return _end > t._end;}
    int _id;
    int _start;
    int _end;
};

vector<bool> meetingGreedySelect(const vector<task>& meetings)
{
    vector<bool> result;
    result.resize(meetings.size(),false);
    //创建优先级队列（小根堆），每次pop()出来的是结束时间早的活动
    priority_queue<task,vector<task>,greater<task> > bq(meetings.begin(),meetings.end());
    task prev = bq.top();
    bq.pop();
    //注意我们活动下标从0开始，而解向量的下标从0开始
    result[prev._id-1]=true;
    while(!bq.empty())
    {
        //pop结束时间早的活动
        task cur = bq.top();
        bq.pop();
        //判断当前活动和上一个贪心选择的活动是否相容
        if(cur._start >= prev._end)
        {
            result[cur._id-1]=true;
            prev=cur;
        }
    }
    return result;
}
int main()
{
    vector<task> meetings = {{1, 3, 6}, {2, 1, 4}, {3, 5, 7}, {4, 2, 5}, {5, 5, 9},
                            {6, 3, 8}, {7, 8, 11}, {8, 6, 10}, {9, 8, 12}, {10, 12, 14}};
    //贪心选择返回一个解向量
    vector<bool> result = meetingGreedySelect(meetings);
    cout<<"最优解为:"<<endl;
    int cnt=0;
    for(int i =0;i<result.size();i++)
        if(result[i])
        {
            cout<<"活动"<<i+1<<" ";
            cnt++;
        }
    cout<<endl<<"选择活动总数为:"<<cnt<<endl;
    return 0;
}
```


### 2.单源最短路问题

#### 2.1 问题描述

> 单源最短路问题：给定的一个有方向带权图 $G=(V,E)$  其中每条边的权值非负实数。另外给定$V$中的一个顶点（源点）。现在要计算源点到其他各个顶点的最短路径长度。

#### 2.2 Dijkstra算法

相关概念：

> 1. 源点：算法首先从图中选定一个点，相当于出发点
> 2. $S$集合，已经确定到源点最短路径的点构成的集合
> 3. $V-S$集合：尚未确定最短路径的集合
> 4. 特殊路径：从源点出发，只经过$S$中的点，到达$V-S$中的点的路径

==**贪心策略：选择特殊路径长度最短的，将相连的$V-S$中的顶点加入到集合$S$中，检查新增加的特殊路径是否优于原来找到的特殊路径，若新的特殊路径最优，则优化。**==

#### 2.3 引例

#### 2.4 python实现

```python {.line-numbers}
import sys

def dijkstra(start,graph):
    n = len(graph)
    MAX = sys.maxsize
    
    dist = [MAX for _ in range(n)]
    s = [False for _ in range(n)]
    pre = [-1 for _ in range(n)]
    
    dist[start] = 0
    #        0   1    2    3    4   5   6
    #dist    8   0    5    10   M   M   9
    #s       0   1    1    0    0   0   0
    #pre     1  -1    1    1   -1  -1   1
    for i in range(n):
        mindist = MAX
        minVex = -1
        # find the vex(not in s) with the min len
        for j in range(n):
            if not s[j] and dist[j]<mindist:
                minVex = j
                mindist = dist[j]
        s[minVex] = True
        for edge in graph[minVex]:
            if not s[edge[0]] and mindist + edge[1] < dist[edge[0]]:
                dist[edge[0]] = mindist + edge[1]
                pre[edge[0]] = minVex
    return dist,pre
            
if __name__ == "__main__":
    data = [[1,0,8],[1,2,5],[1,3,10],[1,6,9],[2,0,1],[0,6,2],[3,6,5],[3,4,8],[0,5,4],
            [5,6,7],[5,3,8],[5,4,5]]
    n = 7
    graph = [[] for _ in range(n)]
    # 邻接表graph 每一个graph里元素：[ [相邻接的顶点，权值], ...]
    for edge in data:
        graph[edge[0]].append([edge[1],edge[2]])
        graph[edge[1]].append([edge[0],edge[2]])
    for e in graph:
        print(e)
    dist,pre = dijkstra(1, graph) # type: ignore
    print("dist=",dist)
    print("pre=",pre)
    
```

#### 2.5 c++实现

```cpp {.line-numbers}
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e9;
typedef pair<int,int> edge;
typedef vector<vector<edge> > Graph;

void dijkstra(int start,const Graph& graph,vector<int>& dist,vector<int>& pre)
{
    size_t vexNum = graph.size();
    bool* s = new bool[vexNum];
    memset(s,0,sizeof(bool)*vexNum);
    dist[start] = 0;
    for(int i=0;i<vexNum;++i)
    {
        int minVex = -1;
        int minDist = MAX;
        for(int j=0;j<vexNum;++j)
            if(!s[j] && dist[j]<minDist)
            {
                minDist = dist[j];
                minVex = j;
            }
        s[minVex] = true;
        for(auto e:graph[minVex])
            if(!s[e.first] && minDist + e.second < dist[e.first])
            {
                dist[e.first] = minDist+e.second;
                pre[e.first] = minVex;
            }
    }
}

int main()
{
    int vexNum=7;
    //{vex1,vex2,weight}
    vector<vector<int> > data = {{1,0,8},{1,2,5},{1,3,10},{1,6,9},{2,0,1},
                                {0,6,2},{3,6,5},{3,4,8},{0,5,4},{5,6,7},{5,3,8},{5,4,5}};
    //graph {{(vex,weight)...}...}
    Graph graph(vexNum);
    for(auto edge : data)
    {
        graph[edge[0]].push_back({edge[1],edge[2]});
        graph[edge[1]].push_back({edge[0],edge[2]});
    }

    vector<int> dist(vexNum,MAX);
    vector<int> pre(vexNum,-1);
    
    dijkstra(1,graph,dist,pre);

    cout<<"dist:"<<endl;
    for(auto e:dist)
        cout<<e<<" ";
    cout<<endl<<"pre:"<<endl;
    for(auto e:pre)
        cout<<e<<" ";
    cout<<endl;
}
```












