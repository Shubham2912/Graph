class TSP:
    def __init__(self,matrix,S):
        self.m=matrix
        self.S=S
        self.N=len(matrix)
    def tsp(self):
        N=self.N
        m=self.m
        S=self.S
        memo=[[float('inf') for i in range(2**N)]for j in range(N)]
        self.setup(m,memo,S,N)
        self.solve(m,memo,S,N)
        minCost=self.findMinCost(m,memo,S,N)
        tour=self.optimalTour(m,memo,S,N)
        return (minCost,tour)

    def setup(self,m,memo,S,N):
        # here j is last node we visited for all 2 nodes pairs
        # in memo we are filling the dis of S to j in a single edge
        # (1<<S)|(1<<j) we are flipping jth and Sth bit both ON means S and j has been visited
        for j in range(N):
            if j==S:continue
            memo[j][(1<<S)|(1<<j)]=m[S][j]

    def notIn(self,i,subset):
        return (((1<<i) & subset)==0)

    def solve(self,m,memo,S,N):
        for r in range(3,N+1):
            for subset in self.combinations(r,N):
                if self.notIn(S,subset):continue
                for next in range(N):
                    if next==S or self.notIn(next,subset):continue
                    state=subset^(1<<next)
                    minDist=float('inf')
                    for e in range(N):
                        if e==S or e==next or self.notIn(e,subset):continue
                        newDist=memo[e][state]+m[e][next] # m[e][next] cost to reach from last node of current state(i.e. e) to the (next) node
                        if newDist<minDist:
                            minDist=newDist
                    memo[next][subset]=minDist

    def combinations(self,r,N):
        subset=[]
        self.combinations2(0,0,r,N,subset)
        return subset

    def combinations2(self,set,at,r,N,subset):
        if r==0:
            subset.append(set)
        else:
            for i in range(at,N):
                set =(set)|(1<<i)
                self.combinations2(set,i+1,r-1,N,subset)
                #backtrack and flip OFF the ith bit
                set =set&(~(1<<i))

    def findMinCost(self,m,memo,S,N):
        END_STATE=(1<<N)-1
        minTourCost=float('inf')
        for e in range(N):
            if e == S or m[e][S] == float("inf"): continue
            tourCost=memo[e][END_STATE]+m[e][S]
            minTourCost=min(minTourCost,tourCost)
        return minTourCost

    def optimalTour(self,m,memo,S,N):
        lastIndex=S
        state=(1<<N)-1  #END_STATE
        tour=[-1]*(N+1)
        for i in range(N-1,0,-1):
            index=-1
            for j in range(N):
                if j == S or self.notIn(j, state): continue
                if index == -1: index = j
                prevDist = float('inf')
                if memo[index][state] != float('inf') and m[index][lastIndex] != float('inf'):
                    prevDist = memo[index][state] + m[index][lastIndex]
                newDist = float('inf')
                if memo[j][state] != float('inf') and m[j][lastIndex] != float('inf'):
                    newDist = memo[j][state] + m[j][lastIndex]
                if newDist < prevDist:
                    index = j
            tour[i] = index
            state=state^(1<<index)
            lastIndex=index
        tour[0]=tour[N]=S
        return tour
V,E=map(int,input().split())
matrix=[[float('inf')for j in range(V)]for k in range(V)]
for i in range(E):
    u,v,w=map(int,input().split())
    matrix[u][v]=w
    matrix[v][u] = w
print(matrix)
minDis=float('inf')
tour=[]
for i in range(V):
    ob=TSP(matrix,i)
    l=ob.tsp()
    if l[0]<minDis:
        minDis=l[0]
        tour=l[1]
print(*tour,sep="-->")
print(minDis)
