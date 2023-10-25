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