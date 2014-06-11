#ifndef _SQLIST_H_
#define _SQLIST_H_

#include<malloc.h>
#define INIT_SIZE 100
#define INCRE_SIZE 10
#define ELEMTYPE int
//typedef int ELEMTYPE;
enum STATUS{SUCCESS,ERROR};

typedef struct
{
	ELEMTYPE* base;
	int length;
	int size;
}SqList;

STATUS Init_myList(SqList& myList)
{
	myList.base=(ELEMTYPE*)malloc(INIT_SIZE*sizeof(ELEMTYPE));
	if(!myList.base)
		return ERROR;
	myList.length=0;
	myList.size=INIT_SIZE;
	return SUCCESS;
}

STATUS InsertElem(SqList& myList,ELEMTYPE myElem,int pos)
{
	if(pos<1||pos>myList.length+1)//����λ�ô���
		return ERROR;
	if(myList.length==myList.size)//�洢������
	{
		ELEMTYPE* newbase=(ELEMTYPE*)realloc(myList.base,(myList.length+100)*sizeof(ELEMTYPE));
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
STATUS GetElem(SqList& mylist,int pos,ELEMTYPE& elem)
{
	if(pos<1||pos>mylist.length)
		return ERROR;
	elem=mylist.base[pos-1];
	return SUCCESS;
}
int LocateElem(SqList& mylist,ELEMTYPE elem)
{
	int pos=0;
	while (pos!=mylist.length&&mylist.base[pos++]!=elem);
	if(pos<mylist.length)
	return pos;//����pos��1��ʼ
	else return 0;
}

STATUS MergeList(SqList a,SqList b,SqList& c)//a,b�����������c
{
	ELEMTYPE* pa=a.base;
	ELEMTYPE* pb=b.base;
	ELEMTYPE* pa_end=a.base+a.length;
	ELEMTYPE* pb_end=b.base+b.length;
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