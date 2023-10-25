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