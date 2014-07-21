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
//ͼ���ڽӾ����ʾ
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
	printf("���붥�����ͱ�����\n");
	fflush(stdin);
	scanf("%d,%d",&G->numVertexes,&G->numEdges);
	for (i=0;i<G->numVertexes;i++)
	{
		scanf("%c",&G->verxs[i]);//���붥������
	}
	for (i=0;i<G->numVertexes;i++)
		for(j=0;j<G->numVertexes;j++)
	{
		G->arc[i][j]=INFINITY;
	}
	for (k=0;k<G->numEdges;j++)
	{
		printf("����ߣ�vi��vj�����±�i��j��Ȩw��\n");
		fflush(stdin);
		scanf("%d,%d,%d",&i,&j,&w);
		G->arc[i][j]=G->arc[j][i]=w;
	}
}

/********************************************************************************************************************************/
//ͼ���ڽӱ��ʾ
/********************************************************************************************************************************/
typedef struct EdgeNode //�߽ڵ�
{
	int adjvex; //�ڽӵ��򣬴洢�����Ӧ�±�
	EdgeType weight; //��Ȩֵ
	struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode //����ڵ�
{
	VertexType data; //������
	EdgeNode* firstedge; //�ڽӱ�ͷ���
}VertexNode,*AdjList;

typedef struct
{
	AdjList adjlist;
	int numVertexes,numEdges;
}GraphAdjList;

void CreateAdjListGraph(GraphAdjList *G)//�����Ȩͼ
{
	int i,j,k,w;
	EdgeNode* e;
	printf("���붥�����ͱ�����\n");
	fflush(stdin);
	scanf("%d,%d",&G->numVertexes,&G->numEdges);
	G->adjlist=(AdjList)malloc(G->numVertexes*sizeof(VertexNode));
	if(!G->adjlist)
		return;
	for (i=0;i<G->numVertexes;i++)
	{
		printf("���붥�����ݣ�\n");
		fflush(stdin);
		scanf("%c",&(G->adjlist[i].data));
		G->adjlist[i].firstedge=0;
	}
	
	for (k=0;k<G->numEdges;k++)
	{
	    printf("�����(vi,vj)�Ķ������ݺ�Ȩֵ��i,j,w:\n");
		fflush(stdin);
		scanf("%d,%d,%d",&i,&j,&w);
		e=(EdgeNode*)malloc(sizeof(EdgeNode));
		if(!e)
			return;
		e->adjvex=j;
		e->weight=w;
		e->next=G->adjlist[i].firstedge;
		G->adjlist[i].firstedge=e;
		//����ͼ����ԳƱ�
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
//ͼ��ʮ������(Orthogonal List)��ʾ������������ͼ
/********************************************************************************************************************************/
#pragma region ͼ��ʮ������
#define MAX_VERTEX_NUM 20  
typedef struct ArcBox  
{  
	int tailvex,headvex; /* �û���β��ͷ�����λ�� */  
	struct ArcBox *hlink,*tlink; /* �ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ������� */  
	int weight; /* �û�Ȩ�� */  
}ArcBox; /* ����� */  

typedef struct  
{  
	VertexType data;  
	ArcBox *firstin,*firstout; /* �ֱ�ָ��ö����һ���뻡�ͳ��� */  
}VexNode; /* ������ */  

typedef struct  
{  
	VexNode xlist[MAX_VERTEX_NUM]; /* ��ͷ����(����) */  
	int vexnum,arcnum; /* ����ͼ�ĵ�ǰ�������ͻ��� */  
}OLGraph;  

int LocateVex(OLGraph G,VertexType u)  
{ /* ���ض���u������ͼG�е�λ��(���),�粻�����򷵻�-1 */  
	int i;  
	for(i=0;i<G.vexnum;++i) /* ��ѭ�����Ҹý�� */  
		if(G.xlist[i].data==u)  
			return i;  
	return -1;  
}  


bool CreateDG(OLGraph *G)  
{ /* ����ʮ������洢��ʾ,��������ͼG���㷨7.3 */  
	int i,j,k;  
	
	
	ArcBox *p;  
	VertexType v1,v2;  
	printf("����������ͼ�Ķ�����,����: ");  
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);  
	printf("������%d�������ֵ:\n",(*G).vexnum);  
	for(i=0;i<(*G).vexnum;++i)  
	{ /* �����ͷ���� */  
		scanf("%s",&(*G).xlist[i].data); /* ���붥��ֵ */  
		(*G).xlist[i].firstin=NULL; /* ��ʼ��ָ�� */  
		(*G).xlist[i].firstout=NULL;  
	}  
	printf("������%d�����Ļ�β�ͻ�ͷ(�ո�Ϊ���):\n",(*G).arcnum);  
	for(k=0;k<(*G).arcnum;++k)  
	{ /* �������������ʮ������ */  
		scanf("%c%c",&v1,&v2);  
		i=LocateVex(*G,v1); /* ȷ��v1��v2��G�е�λ�� */  
		j=LocateVex(*G,v2);  
		p=(ArcBox *)malloc(sizeof(ArcBox)); /* ���������(�ٶ����㹻�ռ�) */  
		p->tailvex=i; /* �Ի���㸳ֵ */  
		p->headvex=j;  
		//��μ��뻡������
		p->hlink=(*G).xlist[j].firstin; /* ������뻡�ͳ��������ͷ�Ĳ��� */  
		p->tlink=(*G).xlist[i].firstout;  
		(*G).xlist[j].firstin=(*G).xlist[i].firstout=p;  
		
		printf("������û���Ȩֵ: ");  
		scanf("%d",&(p->weight));  
	}  
	return true;  
}  

void DestroyGraph(OLGraph *G)  
{ /* ��ʼ����: ����ͼG���� */  
	/* �������: ��������ͼG */  
	int j;  
	ArcBox *p,*q;  
	for(j=0;j<(*G).vexnum;j++) /* �����ж��� */  
	{  
		p=(*G).xlist[j].firstout; /* ��������� */  
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
//�����������(�ڽӱ�)
/********************************************************************************************************************************/
void BFS(GraphAdjList* G)//��������״̬��ʾ������񣬡��㷨���ۡ���ʹ������״̬
{
	bool *isVisited=(bool*)malloc(G->numVertexes*sizeof(bool));//���ʱ��
	for(int i=0;i<G->numVertexes;i++)
		isVisited[i]=false;
	queue<int> VQ;//�洢ָ�򶥵��ָ��
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
//�����������
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
