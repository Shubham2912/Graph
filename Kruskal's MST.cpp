#include<bits/stdc++.h>
using namespace std;
 // } Driver Code Ends
class Solution

{
	public:
	//Kruskal's MST using Disjoint Set
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int find(int a,vector<int>&parent){
        if (parent[a]<0)return a;
        int x=find(parent[a],parent);
        parent[a]=x;
        return x;
    }
    void merge(int a,int b,vector<int>&parent){
        a=find(a,parent);
        b=find(b,parent);
        if(a==b)return;
        else{
            parent[a]+=parent[b];
            parent[b]=a;
        }
    }



    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        vector<int> parent(1001,-1);
        vector<vector<int>>edges;
        for(int i=0;i<V;i++){

            for(int j=0;j<adj[i].size();j++){

                int v=adj[i][j][0];
                int w=adj[i][j][1];

                vector<int>t={w,i,v};
                edges.push_back(t);
            }
        }

        sort(edges.begin(),edges.end());
        int ans=0;
        for(int i=0;i<edges.size();i+=1){

            int u=edges[i][1];
            int v=edges[i][2];
            if (find(u,parent)==find(v,parent))continue;

            merge(u,v,parent);

            ans =ans + edges[i][0];

        }

        return ans;


    }
};
int main()
{
    int t;// t is no of test cases
    cin>>t;
    while(t--){
        int V,E; // V is no. of vertices and E is no. of edges
        cin>>V>>E;
        vector<vector<int>>adj[V];
        int i=0;
        while(i++<E){
            int u,v,w;
            cin>>u>>v>>w;
            vector<int>t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        Solution obj;
        cout<<obj.spanningTree(V,adj)<<"\n";
    }
    return 0;
}
//Here adj[i] contains a list of lists containing two integers where the first integer a[i][0] denotes that there is an edge between i and adj[i][0]
//and second integer adj[i][1] denotes that the distance between edge i and adj[i][0] is adj[i][1].
