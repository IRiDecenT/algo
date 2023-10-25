#include <iostream>
#include <vector>
#include <stack>
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

void printPath(int start,int end,const vector<int>& pre)
{
    stack<int> path;
    int cur = end;
    while(cur!=-1)
    {
        path.push(cur);
        cur=pre[cur];
    }
    int top = path.top();
    path.pop();
    cout<<top;
    while(!path.empty())
    {
        top = path.top();
        path.pop();
        cout<<"->"<<top;
    }
    cout<<endl;
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

    vector<int> dist(vexNum,MAX);//最短特殊路径长度
    vector<int> pre(vexNum,-1);
    
    dijkstra(1,graph,dist,pre);

    cout<<"dist:"<<endl;
    for(auto e:dist)
        cout<<e<<" ";
    cout<<endl<<"pre:"<<endl;
    for(auto e:pre)
        cout<<e<<" ";
    cout<<endl;

    printPath(1,5,pre);
}