import sys

def dijkstra(start,graph):
    n = len(graph)
    MAX = sys.maxsize
    
    dist = [MAX for _ in range(n)] #特殊路径长度
    s = [False for _ in range(n)]
    pre = [-1 for _ in range(n)]
    
    dist[start] = 0
    #        0   1    2    3    4   5    6
    #dist    6   0    5    10   15  10   8
    #s       1   1    1    1    1   1    1
    #pre     2  -1    1    1    5   0    0
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
    