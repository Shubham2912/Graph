import atexit
import sys
import io

class Solution:
    def find(self, a, parent):
        if parent[a] < 0:
            return a
        x = self.find(parent[a], parent)
        parent[a] = x
        return x
    def merge(self, a, b,parent):
        a = self.find(a, parent)
        b = self.find(b, parent)
        if a == b:
            return
        else:
            parent[a] += parent[b]
            parent[b] = a
    # Function to find sum of weights of edges of the Minimum Spanning Tree.
    def spanningTree(self, V, adj):
        # code here
        parent = [-1] * V
        edges = []
        for i in range(V):
            for x in adj[i]:
                edges.append([x[1], x[0], i])
        edges.sort()
        ans = 0
        for i in range(len(edges)):
            a = edges[i][2]
            b = edges[i][1]
            if self.find(a,parent) == self.find(b,parent):
                continue
            else:
                ans += edges[i][0]
                self.merge(a, b,parent)
        return ans


t=int(input())
for  i in range(t):
    V,E=map(int,input().strip().split())
    adj=[[]for k in range(V)]
    for j in range(E):
        u,v,w=map(int,input().split())
        adj[u].append([v,w])
        adj[v].append([u,w])
    obj=Solution()
    print(obj.spanningTree(V,adj))