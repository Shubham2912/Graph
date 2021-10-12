#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
#define ll long long
ll dp[17][1<<17];
ll solve(ll st,ll cur,ll N,ll mask,vector<vector<ll>>&graph)
{
    if(mask==0){
        if(graph[cur][st]!=-1)
        return graph[cur][st];
        else return INT_MAX;
    }
    if(dp[cur][mask]!=-1)return dp[cur][mask];
    ll ans=INT_MAX;
    for(int j =0;j<N;j++){
        if((mask&(1<<j))&&graph[cur][j]!=-1){
            ll newAns=graph[cur][j]+solve(st,j,N,((mask)^(1<<j)),graph);
            ans=min(ans,newAns);
        }
    }
    dp[cur][mask]=ans;
    return dp[cur][mask];
}
int main()
{
    ll n,e,u,v,w;
    cin>>n>>e;
    vector<vector<ll>>graph(n,vector<ll>(n,-1));
    for(ll i=0;i<e;i++){
        cin>>u>>v>>w;
        graph[u][v]=w;
        graph[v][u]=w;

    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
                cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
    ll minDist=INT_MAX;
    for(int i=0;i<n;i++){
        ll initial_mask=((1<<n)-1)^(1<<i);
        memset(dp,-1,sizeof dp);
        ll newminDist= solve(i,i,n,initial_mask,graph);
        minDist=min(minDist,newminDist);
    }

    cout<<minDist;
}
