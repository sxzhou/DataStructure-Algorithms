#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#define LNKLISTELEMTYPE int
#include<malloc.h>
#include <stdio.h>
#include "status.h"

typedef struct linklistNode
{
	LNKLISTELEMTYPE elem;
	struct linklistNode* next;
}linklistNode,*linklist;

linklist NewLinkListNode(LNKLISTELEMTYPE myelem)
{
	linklist myLinkList=(linklist)malloc(sizeof(linklistNode));
	myLinkList->elem=myelem;
	myLinkList->next=NULL;
	return myLinkList;
}
linklist Init_Empty_List()
{
    linklist mylinklist=NewLinkListNode(0);
	return mylinklist;
}
STATUS InsertElem(linklist& mylinklist,LNKLISTELEMTYPE myelem,int pos)//包含头结点1<=pos<=length+1
{
	if(mylinklist==NULL)
		return ERROR;//uninitialized!
	int i=0;
	while (mylinklist!=NULL&&i<pos-1)
	{
		mylinklist=mylinklist->next;
		++i;
	}
	if(mylinklist==NULL||i>pos-1)
		return ERROR;//pos越界
	linklist newelem=NewLinkListNode(myelem);
	newelem->next=mylinklist->next;
	mylinklist->next=newelem;
	return SUCCESS;
}
STATUS DeleteElem(linklist& mylinklist,int pos)//1<=pos<=length
{
	if(mylinklist==NULL)
		return ERROR;//uninitialized!
	int i=0;
	while(mylinklist!=NULL&&i!=pos-1)
	{
		mylinklist=mylinklist->next;
		++i;
	}
	if(mylinklist==NULL||mylinklist->next==NULL||i>pos-1)
		return ERROR;//out of range!
	linklist destination=mylinklist->next;
	mylinklist->next=mylinklist->next->next;
	free(destination);
	return SUCCESS;
}
STATUS CreatList(linklist& mylist,int n)//头插法
{
	mylist=(linklist)malloc(sizeof(linklistNode));
	mylist->next=NULL;//head
	for(int i=0;i<n;++i)
	{
		linklist node=(linklist)malloc(sizeof(linklistNode));
		scanf("%d",&node->elem);
		node->next=mylist->next;
		mylist->next=node;
	}
}
STATUS MergeLinkList(linklist& La,linklist& Lb,linklist& Lc)//递增
{
	linklist pa=La->next;
	linklist pb=Lb->next;
	Lc=(linklist)malloc(sizeof(linklistNode));
    Lc->elem=0;
	Lc->next=NULL;
	linklist pc=Lc;
	while(pa&&pb)
	{
		if (pa->elem<=pb->elem)
		{
			pc->next=pa;
			pc=pa;
			pa=pa->next;
		}
		else
		{
			pc->next=pb;
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;
	free(La);
	free(Lb);
	return SUCCESS;
}

/*静态链表*/
typedef struct{
	LNKLISTELEMTYPE elem;
	int cur;
}component,SlinkList[1000];
//集合运算

/*循环链表circular linked list*/
/*约瑟夫环*/
linklist Init_JosephusCircle(int n)
{
	linklist first=(linklist)malloc(sizeof(linklistNode));
	first->elem=1;
	first->next=first;

}

#endif