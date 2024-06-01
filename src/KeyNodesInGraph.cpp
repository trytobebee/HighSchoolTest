#include<stdio.h>
#include<vector>
std::vector<int> to[2001];
int n,m,tot,vis[2001],ans[2001];

//从x到n做dfs,注意其中的y是用来排除y这个点的，也就是说to[x]中的y会被去掉。
bool dfs(int x,const int excludeNode)
{
    //到达n点，则成功
	if(x==n)return 1; 
	vis[x]=1;

    //针对所有x可以到达的对象遍历，去掉y点和已经经过的点（不走回头路）
	for(const auto&i:to[x])
		if(i!=excludeNode && !vis[i] && dfs(i,excludeNode))
			return 1;
    
    //没有满足条件的下游节点了，那么就返回失败
	return 0;
}

int SearchKeyNodesInGraph()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		int u,v;
		scanf("%d%d",&u,&v); 

        //站点之间联系是双向的，所以要加上双边
		to[u].push_back(v); //u的出边加上v
        to[v].push_back(u); //v的出边加上u
	}

    //除开点i，就不能连到n的话那么点i就是必经点
	for(int i=2;i<n;++i)
    {
		//清空经过历史记录
        for(int i=1;i<=n;++i)
            vis[i]=0; 
		
        //进行排除i之后的深度遍历，从1出发能到n
        if(!dfs(1,i))
            ans[tot++]=i; //如果遍历失败，那么i就是一个必经点，记录下来
	}

	printf("%d\n",tot);

	for(int i=0;i<tot;++i)
        printf("%d ",ans[i]);
	
    return 0;
}