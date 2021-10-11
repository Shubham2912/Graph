#include<bits/stdc++.h>
using namespace std;
class Solution
{
	public:
	//Prim's MST
	//Function to find sum of weights of edges of the Minimum Spanning Tree.

    struct myComp{
        bool operator()(vector<int>a,vector<int>b){
            return a[0]>b[0];
        }
    };


    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        //set<vector<int>>setds;//can also be done by priority queue
        priority_queue<vector<int>,vector<vector<int>>,myComp>q;
        bool visited[V]={0};
        vector<int>p={0,0,-1};
        //setds.insert(p);
        q.push(p);
        int ans=0;
        // if using set use setds.empty
        int parent[V]={-1};
        while(!q.empty()){

            //vector<int> t=*(setds.begin());
            //setds.erase(setds.begin());
             vector<int> t=q.top();
             q.pop();

            if (visited[t[1]])continue;
            else{


                visited[t[1]]=1;

                ans+=t[0];
                for(int x=0;x<adj[t[1]].size();x++){
                    int v=adj[t[1]][x][0];
                    int w=adj[t[1]][x][1];
                    if(!visited[v]){
                        parent[v]=t[1];
                        p={w,v,t[1]};
                        q.push(p);
                        //setds.insert(p);
                    }
                }
            }
        }
        /*for(int i=0;i<V;i++){
            cout<<parent[i]<<' ';
        }
        cout<<endl;*/
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
