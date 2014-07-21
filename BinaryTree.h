#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>
#include "status.h"
#include "SqStack.h"
#include "Queue.h"
#define  BTElemType char

typedef struct BiTNode
{
	BTElemType elem;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef void (* VISIT)(BTElemType e);

//前序建立二叉树
STATUS CreateBiTree(BiTree& T)
{
	char ch;
	scanf("%c",&ch);
	/*if(ch==10)
		scanf("%c",&ch);*/
	if(ch=='#')
		T=NULL;
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
			return ERROR;
		T->elem=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return SUCCESS;
}

//Traverse binary tree recursion 递归实现
//1.preorder
void DLR(BiTree BT,VISIT visit)
{
	if(BT)
	{
		visit(BT->elem);
		DLR(BT->lchild,visit);
		DLR(BT->rchild,visit);
	}
}
//2.inorder
void LDR(BiTree BT,VISIT visit)
{
	if(BT)
	{
		LDR(BT->lchild,visit);
		visit(BT->elem);
		LDR(BT->rchild,visit);
	}
}
//3.lastorder
void LRD(BiTree BT,VISIT visit)
{
	if(BT)
	{
		LRD(BT->lchild,visit);
		LRD(BT->rchild,visit);
		visit(BT->elem);
	}
}

//Traverse binary tree iteration 通过辅助栈实现，时间O(n)，空间O(h)
//1.中序遍历
STATUS InOrderTraverse(BiTree T,VISIT visit)
{
	SqStack mystack;
	Init_SqStack(mystack);
	Push(mystack,T);
	void* p;
	while (!StackEmpty(mystack))
	{
		while(GetTop(mystack,p)==SUCCESS&&p)
		{
			Push(mystack,((BiTree)p)->lchild);
		}
		Pop(mystack,p);//弹出空指针
		if(!StackEmpty(mystack))
		{
			Pop(mystack,p);
			visit(((BiTree)p)->elem);
			Push(mystack,((BiTree)p)->rchild);
		}
	}

	//STL实现
	/*std::stack<BiTree> BitreeStack;
	BitreeStack.push(T);
	BiTree p;
	while(!BitreeStack.empty())
	{
		while((p=BitreeStack.top())&&p)
			BitreeStack.push(p->lchild);
		BitreeStack.pop();
		if (!BitreeStack.empty())
		{
			p=BitreeStack.top();
			BitreeStack.pop();
			visit(p->elem);
			BitreeStack.push(p->rchild);
		}
		
	}*/
	return SUCCESS;
}

STATUS InOrderTraverse2(BiTree T,VISIT visit)
{
	SqStack mystack;
	Init_SqStack(mystack);
	void* p=T;
	while(p||!StackEmpty(mystack))
	{
		if(p)
		{
			Push(mystack,p);
			p=((BiTree)p)->lchild;
		}
		else
		{
			Pop(mystack,p);
			visit(((BiTree)p)->elem);
			p=((BiTree)p)->rchild;
		}
	}
	return SUCCESS;
}

//2.前序遍历
STATUS PreOrderTraverse(BiTree T,VISIT visit)
{
	SqStack mystack;
	Init_SqStack(mystack);
	void* p=T;
	while(p||!StackEmpty(mystack))
	{
		if(p)
		{
			visit(((BiTree)p)->elem);
			Push(mystack,p);
			p=((BiTree)p)->lchild;
		}
		else
		{
			Pop(mystack,p);
			p=((BiTree)p)->rchild;
		}
	}
	return SUCCESS;
}
//3.后序遍历

void PostOrder(BiTree T,VISIT visit)  
{  
	SqStack S;
	Init_SqStack(S);  
	void *p, *r;  
	p = T;  
	r = NULL;  
	while(p || !StackEmpty(S))
	{  
		if(p) {  
			Push(S, p);  
			p = ((BiTree)p) -> lchild;  
		} 
		else 
		{  
			GetTop(S, p);  
            if(((BiTree)p)->rchild&&((BiTree)p)->rchild!=r)
			{  
				p = ((BiTree)p) -> rchild;  
				Push(S, p);  
				p = ((BiTree)p) -> lchild;  
			} 
			else 
			{  
				Pop(S, p);  
				visit(((BiTree)p)->elem);  
				r = p;  
				p = NULL;  
			}  
		}  
	}  
}  
//更多关于非递归前中后序遍历
//http://blog.csdn.net/kofsky/article/details/2886453
//http://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html
//http://www.cnblogs.com/ybwang/archive/2011/10/04/lastOrderTraverse.html

//层序遍历
void LevelOrder(BiTree T,VISIT visit)
{
	LinkQueue Q;
	InitQueue(Q);
	EnQueue(Q,T);
	void* p;
	while(!QEmpty(Q))
	{
		DeQueue(Q,p);
		visit(((BiTree)p)->elem);
		if (((BiTree)p)->lchild)
		{
			EnQueue(Q,((BiTree)p)->lchild);
		}
		if (((BiTree)p)->rchild)
		{
			EnQueue(Q,((BiTree)p)->rchild);
		}
	}
}

//层次遍历，如遇到第一个null，则检查剩下的如果出现一个非null，则非完全
bool IsCompleteBinaryTree(BiTree T)
{
	std::queue<BiTree> Q;
	Q.push(T);
	BiTree p;
	while(p=Q.front())
	{
		Q.pop();
		Q.push(p->lchild);
		Q.push(p->rchild);
	}
	while(!Q.empty())
	{
		p=Q.front();
		if(NULL!=p)
			return false;
		Q.pop();
	}
	return true;
}
//二叉树高度
int Height(BiTree T)
{
	if (!T)
	{
		return 0;
	}
	else
	{
		int heigh_l=Height(T->lchild);
		int heigh_r=Height(T->rchild);
		return 1+(heigh_l>heigh_r?heigh_l:heigh_r);
	}
}

//二叉树最大宽度
int Width(BiTree T)
{
	if(!T)
		return 0;
	BiTree Q[100];//元素为二叉树节点指针的队列 
	int front=1,rear=1;//队头、队尾指针
	int last=1;//同层最右节点在队列中的位置
	int temp=0,maxw=0;//当前层宽度和最大宽度 
	Q[rear]=T;
	BiTree p;
	while(front<=last)
	{
		p=Q[front++];
		temp++;//同层元素数加1,front用于出队 
		if(p->lchild)
			Q[++rear]=p->lchild;
		if(p->rchild)
			Q[++rear]=p->rchild;
		if(front>last)
		{
			last=rear;//last指向下一层最右元素
			if(temp>maxw)
				maxw=temp;
			temp=0;
		}
	}
	return maxw;
}

//二叉树第k层节点数
int GetNodeNumKthLevel(BiTree pRoot, int k)
{
	if (!pRoot || k < 1)
		return 0;

	if (k == 1)
		return 1;

	return (GetNodeNumKthLevel(pRoot->lchild, k-1)+GetNodeNumKthLevel(pRoot->rchild, k-1));
}
//是否平衡，节点最大距离，前序和中序重建
//http://blog.csdn.net/geekster/article/details/12176299
#endif