#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <queue>
typedef char VertexType;
typedef int EdgeType;
#define MAXVERTEX 100
#define INFINITY 65535
using namespace std;

/********************************************************************************************************************************/
//图的邻接矩阵表示
/********************************************************************************************************************************/
typedef struct  
{
	VertexType verxs[MAXVERTEX];
	EdgeType arc[MAXVERTEX][MAXVERTEX];
	int numVertexes,numEdges;
}MGraph;

void CreateMGraph(MGraph* G)
{
	int i,j,k,w;
	printf("输入顶点数和边数：\n");
	fflush(stdin);
	scanf("%d,%d",&G->numVertexes,&G->numEdges);
	for (i=0;i<G->numVertexes;i++)
	{
		scanf("%c",&G->verxs[i]);//输入顶点数组
	}
	for (i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
	{
		G->arc[i][j]=INFINITY;
	}
	for (k=0;k<G->numEdges;j++)
	{
		printf("输入边（vi，vj）的下标i，j，权w：\n");
		fflush(stdin);
		scanf("%d,%d,%d",&i,&j,&w);
		G->arc[i][j]=G->arc[j][i]=w;
	}
}

/********************************************************************************************************************************/
//图的邻接表表示
/********************************************************************************************************************************/
typedef struct EdgeNode //边节点
{
	int adjvex; //邻接点域，存储顶点对应下标
	EdgeType weight; //边权值
	struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode //顶点节点
{
	VertexType data; //顶点域
	EdgeNode* firstedge; //邻接边头结点
}VertexNode,*AdjList;

typedef struct
{
	AdjList adjlist;
	int numVertexes,numEdges;
}GraphAdjList;

void CreateAdjListGraph(GraphAdjList *G)//有向带权图
{
	int i,j,k,w;
	EdgeNode* e;
	printf("输入顶点数和边数：\n");
	fflush(stdin);
	scanf("%d,%d",&G->numVertexes,&G->numEdges);
	G->adjlist=(AdjList)malloc(G->numVertexes*sizeof(VertexNode));
	if(!G->adjlist)
		return;
	for (i=0;i<G->numVertexes;i++)
	{
		printf("输入顶点数据：\n");
		fflush(stdin);
		scanf("%c",&(G->adjlist[i].data));
		G->adjlist[i].firstedge=0;
	}
	
	for (k=0;k<G->numEdges;k++)
	{
	    printf("输入边(vi,vj)的顶点数据和权值，i,j,w:\n");
		fflush(stdin);
		scanf("%d,%d,%d",&i,&j,&w);
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			return;
		e->adjvex=j;
		e->weight=w;
		e->next=G->adjlist[i].firstedge;
		G->adjlist[i].firstedge=e;
		//无向图加入对称边
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			return;
		e->adjvex=i;
		e->weight=w;
		e->next=G->adjlist[j].firstedge;
		G->adjlist[j].firstedge=e;

	}
}

void DestroyAdjListGraph(GraphAdjList* G)
{
	for (int i=0;i<G->numVertexes;i++)
	{
		EdgeNode* p,*q;
		p=G->adjlist[i].firstedge;
		while(p)
		{
			q=p->next;
			free(p);
			p=q;
		}

	}
	free(G->adjlist);
}
/********************************************************************************************************************************/
//图的十字链表(Orthogonal List)表示，适用于有向图
/********************************************************************************************************************************/
#pragma region 图的十字链表
#define MAX_VERTEX_NUM 20  
typedef struct ArcBox  
{  
	int tailvex,headvex; /* 该弧的尾和头顶点的位置 */  
	struct ArcBox *hlink,*tlink; /* 分别为弧头相同和弧尾相同的弧的链域 */  
	int weight; /* 该弧权重 */  
}ArcBox; /* 弧结点 */  

typedef struct  
{  
	VertexType data;  
	ArcBox *firstin,*firstout; /* 分别指向该顶点第一条入弧和出弧 */  
}VexNode; /* 顶点结点 */  

typedef struct  
{  
	VexNode xlist[MAX_VERTEX_NUM]; /* 表头向量(数组) */  
	int vexnum,arcnum; /* 有向图的当前顶点数和弧数 */  
}OLGraph;  

int LocateVex(OLGraph G,VertexType u)  
{ /* 返回顶点u在有向图G中的位置(序号),如不存在则返回-1 */  
	int i;  
	for(i=0;i<G.vexnum;++i) /* 用循环查找该结点 */  
		if(G.xlist[i].data==u)  
			return i;  
	return -1;  
}  


bool CreateDG(OLGraph *G)  
{ /* 采用十字链表存储表示,构造有向图G。算法7.3 */  
	int i,j,k;  
	
	
	ArcBox *p;  
	VertexType v1,v2;  
	printf("请输入有向图的顶点数,弧数: ");  
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);  
	printf("请输入%d个顶点的值:\n",(*G).vexnum);  
	for(i=0;i<(*G).vexnum;++i)  
	{ /* 构造表头向量 */  
		scanf("%s",&(*G).xlist[i].data); /* 输入顶点值 */  
		(*G).xlist[i].firstin=NULL; /* 初始化指针 */  
		(*G).xlist[i].firstout=NULL;  
	}  
	printf("请输入%d条弧的弧尾和弧头(空格为间隔):\n",(*G).arcnum);  
	for(k=0;k<(*G).arcnum;++k)  
	{ /* 输入各弧并构造十字链表 */  
		scanf("%c%c",&v1,&v2);  
		i=LocateVex(*G,v1); /* 确定v1和v2在G中的位置 */  
		j=LocateVex(*G,v2);  
		p=(ArcBox *)malloc(sizeof(ArcBox)); /* 产生弧结点(假定有足够空间) */  
		p->tailvex=i; /* 对弧结点赋值 */  
		p->headvex=j;  
		//如何加入弧？！！
		p->hlink=(*G).xlist[j].firstin; /* 完成在入弧和出弧链表表头的插入 */  
		p->tlink=(*G).xlist[i].firstout;  
		(*G).xlist[j].firstin=(*G).xlist[i].firstout=p;  
		
		printf("请输入该弧的权值: ");  
		scanf("%d",&(p->weight));  
	}  
	return true;  
}  

void DestroyGraph(OLGraph *G)  
{ /* 初始条件: 有向图G存在 */  
	/* 操作结果: 销毁有向图G */  
	int j;  
	ArcBox *p,*q;  
	for(j=0;j<(*G).vexnum;j++) /* 对所有顶点 */  
	{  
		p=(*G).xlist[j].firstout; /* 仅处理出弧 */  
		while(p)  
		{  
			q=p;  
			p=p->tlink;  
			free(q);  
		}  
	}  
	(*G).arcnum=0;  
	(*G).vexnum=0;
}  
//http://wu-yudong.iteye.com/blog/1986705
#pragma endregion

/********************************************************************************************************************************/
//广度优先搜索(邻接表)
/********************************************************************************************************************************/
void BFS(GraphAdjList* G)//采用两种状态表示访问与否，《算法导论》中使用三种状态
{
	bool *isVisited=(bool*)malloc(G->numVertexes*sizeof(bool));//访问标记
	for(int i=0;i<G->numVertexes;i++)
		isVisited[i]=false;
	queue<int> VQ;//存储指向顶点的指针
	for(int k=0;k<G->numVertexes;k++)
	{
		if(isVisited[k]) break;
		VQ.push(k);
		while(!VQ.empty())
		{
			int p=VQ.front();
			VQ.pop();
			printf("%c\n",G->adjlist[p].data);
			isVisited[p]=true;
			EdgeNode* pNext=G->adjlist[p].firstedge;
			while(pNext)
			{
				if (!isVisited[pNext->adjvex])
				{
					VQ.push(pNext->adjvex);
					isVisited[pNext->adjvex]=true;
				}
				pNext=pNext->next;
			}
		}
	}
	
	free(isVisited);
}
//深度优先搜索
void DFS(GraphAdjList* G,int i,bool* isVisited)
{
	printf("%c",G->adjlist[i].data);
	isVisited[i]=true;
	EdgeNode* pNext=G->adjlist[i].firstedge;
	while (pNext)
	{
		if(!isVisited[pNext->adjvex])
			DFS(G,pNext->adjvex,isVisited);
		pNext=pNext->next;
	}
}
void DFSTraverse(GraphAdjList* G)
{
	bool* isVisited=(bool*)malloc(G->numVertexes*sizeof(bool));
	for (int i=0;i<G->numVertexes;i++)
		isVisited[i]=false;
	for (int k=0;k<G->numVertexes;k++)
	{
		if(!isVisited[k])
			DFS(G,k,isVisited);
	}
	free(isVisited);
}



#endif
