#ifndef _SQSTACK_H_
#define _SQSTACK_H_
#define INIT_SIZE 100
#define INCREMENT 10
#define  ELEMTYPE int
#include <stdio.h>
#include <malloc.h>
enum STATUS{SUCCESS,ERROR};

typedef struct
{
	ELEMTYPE* base;
	ELEMTYPE* top;
	int stacksize;
}SqStack;

STATUS Init_SqStack(SqStack& s)
{
	s.base=(ELEMTYPE*)malloc(INIT_SIZE*sizeof(ELEMTYPE));
	if(!s.base) return ERROR;
	s.top=s.base;
	s.stacksize=INIT_SIZE;
	return SUCCESS;
}

STATUS Push(SqStack& s,ELEMTYPE e)
{
	if(s.top-s.base==s.stacksize)//full
	{
		s.base=(ELEMTYPE*)realloc(s.base,sizeof(ELEMTYPE)*(s.stacksize+INCREMENT));
		if(!s.base) return ERROR;
		s.top=s.base+s.stacksize;
		s.stacksize+=INCREMENT;
	}
	*(s.top++)=e;
	return SUCCESS;
}

STATUS Pop(SqStack& s,ELEMTYPE& e)
{
	if(s.base==s.top)
		return ERROR;
	e=*(--s.top);
	return SUCCESS;
}
STATUS GetTop(SqStack& s,ELEMTYPE& e)
{
	if(s.base==s.top)
		return ERROR;
	e=*(s.top-1);
	return SUCCESS;
}

#endif

