#ifndef _SQLIST_H_
#define _SQLIST_H_

#include<malloc.h>
#define INIT_SIZE 100
#define INCRE_SIZE 10
#define SQLISTELEMTYPE int
#include "status.h"

typedef struct
{
	SQLISTELEMTYPE* base;
	int length;
	int size;
}SqList;

STATUS Init_myList(SqList& myList)
{
	myList.base=(SQLISTELEMTYPE*)malloc(INIT_SIZE*sizeof(SQLISTELEMTYPE));
	if(!myList.base)
		return ERROR;
	myList.length=0;
	myList.size=INIT_SIZE;
	return SUCCESS;
}

STATUS InsertElem(SqList& myList,SQLISTELEMTYPE myElem,int pos)
{
	if(pos<1||pos>myList.length+1)//插入位置错误
		return ERROR;
	if(myList.length==myList.size)//存储区已满
	{
		SQLISTELEMTYPE* newbase=(SQLISTELEMTYPE*)realloc(myList.base,(myList.length+100)*sizeof(SQLISTELEMTYPE));
		myList.base=newbase;
		myList.size+=INCRE_SIZE;
	}
	for(int i=myList.length-1;i>=pos-1;--i)
	{
		myList.base[i+1]=myList.base[i];
	}
	myList.base[pos-1]=myElem;
	myList.length++;
	return SUCCESS;
}

STATUS FreeList(SqList& mylist)
{
	free(mylist.base);
	mylist.base=NULL;
	mylist.length=0;
	mylist.size=0;
	return SUCCESS;
}
STATUS DelElem(SqList& mylist,int pos)
{
	if(pos<1||pos>mylist.length)
		return ERROR;
	for(int i=pos-1;i<mylist.length-1;++i)
	{
		mylist.base[i]=mylist.base[i+1];
	}
	mylist.length--;
	return SUCCESS;
}
STATUS GetElem(SqList& mylist,int pos,SQLISTELEMTYPE& elem)
{
	if(pos<1||pos>mylist.length)
		return ERROR;
	elem=mylist.base[pos-1];
	return SUCCESS;
}
int LocateElem(SqList& mylist,SQLISTELEMTYPE elem)
{
	int pos=0;
	while (pos!=mylist.length&&mylist.base[pos++]!=elem);
	if(pos<mylist.length)
	return pos;//返回pos从1开始
	else return 0;
}

STATUS MergeList(SqList a,SqList b,SqList& c)//a,b递增，结果存c
{
	SQLISTELEMTYPE* pa=a.base;
	SQLISTELEMTYPE* pb=b.base;
	SQLISTELEMTYPE* pa_end=a.base+a.length;
	SQLISTELEMTYPE* pb_end=b.base+b.length;
	if(Init_myList(c)!=SUCCESS)
		return ERROR;
	while (pa!=pa_end&&pb!=pb_end)
	{
		if(*pa<=*pb)
		{
			if(InsertElem(c,*pa,c.length+1)!=SUCCESS)
				return ERROR;
			pa++;
		}
		else
		{
		    if (InsertElem(c,*pb,c.length+1)!=SUCCESS)
		    return ERROR;
			pb++;
		}
	}
	while(pa!=pa_end)
	{
		if(InsertElem(c,*pa,c.length+1)!=SUCCESS)
			return ERROR;
		pa++;
	}
	while (pb!=pb_end)
	{
		if(InsertElem(c,*pb,c.length+1)!=SUCCESS)
			return ERROR;
		pb++;
	}
	return SUCCESS;

}

#endif