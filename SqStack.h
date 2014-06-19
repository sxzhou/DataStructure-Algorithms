#ifndef _SQSTACK_H_
#define _SQSTACK_H_
#define INIT_SIZE 100
#define INCREMENT 10
#define  STACKELEMTYPE void*
#include <stdio.h>
#include <malloc.h>
#include "status.h"

typedef struct
{
	STACKELEMTYPE* base;
	STACKELEMTYPE* top;
	int stacksize;
}SqStack;

STATUS Init_SqStack(SqStack& s)
{
	s.base=(STACKELEMTYPE*)malloc(INIT_SIZE*sizeof(STACKELEMTYPE));
	if(!s.base) return ERROR;
	s.top=s.base;
	s.stacksize=INIT_SIZE;
	return SUCCESS;
}

STATUS Push(SqStack& s,STACKELEMTYPE e)
{
	if(s.top-s.base==s.stacksize)//full
	{
		s.base=(STACKELEMTYPE*)realloc(s.base,sizeof(STACKELEMTYPE)*(s.stacksize+INCREMENT));
		if(!s.base) return ERROR;
		s.top=s.base+s.stacksize;
		s.stacksize+=INCREMENT;
	}
	*(s.top++)=e;
	return SUCCESS;
}

STATUS Pop(SqStack& s,STACKELEMTYPE& e)
{
	if(s.base==s.top)
		return ERROR;
	e=*(--s.top);
	return SUCCESS;
}
STATUS GetTop(SqStack& s,STACKELEMTYPE& e)
{
	if(s.base==s.top)
		return ERROR;
	e=*(s.top-1);
	return SUCCESS;
}

bool StackEmpty(SqStack& s)
{
	return s.base==s.top;
}
#endif

