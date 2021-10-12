N,E=map(int,input().split())
completed_visited=2**N-1
INF=float('inf')
def solve(start,cur,mask,graph,dp):
    if mask==0:
        return graph[cur][start]
    if dp[cur][mask]!=-1:return dp[cur][mask]
    ans=INF
    for j in range(N):
        if ((mask)&(1<<j)):
                newAns=graph[cur][j]+solve(start,j,((mask)^(1<<j)),graph,dp)
                ans=min(ans,newAns)
    dp[cur][mask]=ans
    return dp[cur][mask]



graph=[[INF for p in range(N)]for k in range(N)]
for i in range(E):
    u,v,w=map(int,input().split())
    graph[u][v]=w
    graph[v][u]=w
minDis=INF

# 1<<N-1
starting_point= 0;
for i in range(N):
    initial_mask = ((2**N)-1)^(1<<i)
    dp = [[-1 for p in range(2 ** N)] for q in range(N)]
    newMinDis =  solve(i,i, initial_mask, graph, dp)
    if newMinDis<minDis:
        starting_point=i
        minDis=newMinDis
print(minDis)
