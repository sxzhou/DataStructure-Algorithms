#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <malloc.h>
#define  QElemType void*
#include "status.h"

//链式队列
typedef struct QNode
{
	QElemType elem;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

STATUS InitQueue(LinkQueue& Q)
{
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		return ERROR;
	Q.front->next=0;
	return SUCCESS;
}

STATUS DestroyQueue(LinkQueue& Q)
{
	while(Q.front)
	{
		QueuePtr temp=Q.front->next;
		free(Q.front);
		Q.front=temp;
	}
	return SUCCESS;
}

STATUS EnQueue(LinkQueue& Q,QElemType e)
{
	QueuePtr newNode=(QueuePtr)malloc(sizeof(QNode));
	if(!newNode)
		return ERROR;
	newNode->elem=e;
	newNode->next=0;
	Q.rear->next=newNode;
	Q.rear=newNode;
	return SUCCESS;
}

STATUS DeQueue(LinkQueue& Q,QElemType& e)
{
	if(Q.front==Q.rear)
		return ERROR;
	e=Q.front->next->elem;
	QueuePtr temp=Q.front->next;
	Q.front->next=temp->next;
	if(Q.rear==temp)
		Q.front=Q.rear;
	free(temp);
	return SUCCESS;
}

bool QEmpty(LinkQueue Q)
{
    return Q.front==Q.rear;
}

//循环队列
#define MAXSIZE 1000
typedef struct
{
	QElemType* base;
	int front;
	int rear;
}CirQueue;

STATUS InitCirQueue(CirQueue& CQ)
{
	CQ.base=(QElemType*)malloc(MAXSIZE*sizeof(CirQueue));
	if(!CQ.base)
		return ERROR;
	CQ.front=CQ.rear=0;
	return SUCCESS;
}


int QueueLength(CirQueue& CQ)
{
	return (CQ.rear-CQ.front+MAXSIZE)%MAXSIZE;
}

STATUS EnCirQueue(CirQueue& CQ,QElemType e)
{
	if((CQ.rear+1)%MAXSIZE==CQ.front)//full
		return ERROR;
	CQ.base[CQ.rear]=e;
	CQ.rear=(CQ.rear+1)%MAXSIZE;
	return SUCCESS;
}

STATUS DeCirQueue(CirQueue& CQ,QElemType& e)
{
	if(CQ.front==CQ.rear)//empty
		return ERROR;
	e=CQ.base[CQ.front];
	CQ.front=(CQ.front+1)%MAXSIZE;
	return SUCCESS;
}
#endif
