#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_
#include <iostream>
#include<malloc.h>
#define KeyType int
using namespace std;

typedef struct BSTNode
{
	KeyType key;
	struct BSTNode* lchild;
	struct BSTNode* rchild;
	struct BSTNode* parent;
}BSTNode,*P_BSTNode;

void inorder_traverse(P_BSTNode root)//�������BST
{
	if (root)
	{
		inorder_traverse(root->lchild);
		cout<<root->key<<endl;
		inorder_traverse(root->rchild);
	}
}

P_BSTNode search(P_BSTNode p,KeyType key)//�ݹ����
{
	if (p->key==key||p==NULL)
	{
		return p;
	}
	if (key>p->key)
	{
		return search(p->rchild,key);
	}
	else
	{
		return search(p->lchild,key);
	}
}

P_BSTNode iterative_search(P_BSTNode p,KeyType key)//��������
{
	while(p&&p->key!=key)
	{
		if(p->key>key)
			p=p->lchild;
		else
			p=p->rchild;
	}
	return p;
}

P_BSTNode bst_min(P_BSTNode p)//��Сֵ
{
	if(!p)
		return p;
	while(p->lchild)//ע������
		p=p->lchild;
	return p;
}
P_BSTNode bst_max(P_BSTNode p)//���ֵ
{
	if(!p)
		return p;
	while(p->rchild)
		p=p->rchild;
	return p;
}

P_BSTNode successor(P_BSTNode p)//���
{
	if(!p)
		return p;
	if(p->rchild)//���Ϊ��������Сֵ
		return bst_min(p->rchild);
	else
	{
		P_BSTNode parent=p->parent;
		while(parent&&p==parent->rchild)//����һֱ�ҵ�һ�������Ϸ���parent
		{
			p=parent;
			parent=parent->parent;
		}
		return parent;
	}
}

P_BSTNode predecessor(P_BSTNode p)//ǰ��
{
	if(!p)
		return NULL;
	if(p->lchild)//ǰ��Ϊ���������ֵ
		return bst_max(p->lchild);
	else
	{
		P_BSTNode parent=p->parent;
		while(parent&&p==parent->lchild)//����һֱ�ҵ�һ�������Ϸ���parent
		{
			p=parent;
			parent=parent->parent;
		}
		return parent;
	}
}

void bst_insert(P_BSTNode *root,KeyType key)//����ڵ�key����ͬ,rootΪ���ڵ�ָ�룬��Ϊroot���ܻ�ı�
{
	//��ʼ���ڵ�
	P_BSTNode node=(P_BSTNode)malloc(sizeof(BSTNode));
	node->key=key;
	node->lchild=node->rchild=node->parent=NULL;
	 P_BSTNode parent=NULL;
	 P_BSTNode p=*root;
	 while(p)
	 {
		 parent=p;
		 if(key>p->key)
			 p=p->rchild;
		 else
			 p=p->lchild;
	 }
	 node->parent=parent;
	 if(!parent)//����
		 root=&node;
	 else if (parent->key>key)
	 {
		 parent->lchild=node;
	 }
	 else
		 parent->rchild=node;

}
void replace(P_BSTNode *root,P_BSTNode u,P_BSTNode v)//��v�滻u
{
	if(u->parent==NULL)//uΪ��
		root=&v;
	if (u->parent->lchild==u)//uΪ������
	{
		u->parent->lchild=v;
	}
	else
		u->parent->rchild=v;
	if(v)
		v->parent=u->parent;
}

void bst_delete(P_BSTNode* root,P_BSTNode p)
{
	if(p->lchild==NULL)
		replace(root,p,p->rchild);
	else if(p->rchild==NULL)
		replace(root,p,p->lchild);
	else
	{
		P_BSTNode t=bst_min(p->rchild);
		if (t->parent!=p)
		{
			replace(root,t,t->rchild);
			t->rchild=p->rchild;
			t->rchild->parent=t;
		}
		replace(root,p,t);
		t->lchild=p->lchild;
		t->lchild.parent=t;
	}
}
#endif