# pragma once
# include <stdlib.h>
# define MinSizeOfStack 30
# define EmptyTOS -1
# define ElementType char
typedef struct stack
{
	int Capacity;
	int TopOfStack;
	ElementType * Array;
}*Stack;
int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxCapaicty);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyTOS;
}
int IsFull(Stack S)
{
	return S->Capacity == S->TopOfStack - 1;
}
Stack CreateStack(int MaxCapacity)
{
	if (MaxCapacity < MinSizeOfStack)
		perror("Stack size is too small!");
	Stack S = (Stack)malloc(sizeof(struct stack));
	S->Array = (ElementType *)malloc(sizeof(ElementType)*MaxCapacity);
	if (S == NULL || S->Array == NULL)
		perror("Memory alloc failed!");
	S->Capacity = MaxCapacity;
	MakeEmpty(S);
	return S;
}
void DisposeStack(Stack S)
{
	if (S != NULL)
	{
		free(S->Array);
		free(S);
	}
}
void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyTOS;
}
void Push(ElementType X, Stack S)
{
	if (IsFull(S))
		perror("Stack is full!");
	else
		S->Array[++S->TopOfStack] = X;
}
ElementType Top(Stack S)
{
	if (IsEmpty(S))
	{
		perror("Stack is empty!");
		return 0;
	}
	return S->Array[S->TopOfStack];
}
void Pop(Stack S)
{
	if (IsEmpty(S))
		perror("Stack is empty!");
	else
		S->TopOfStack--;
}
ElementType TopAndPop(Stack S)
{
	if (IsEmpty(S))
	{
		perror("Stack is empty!");
		return 0;
	}
	return S->Array[S->TopOfStack-- + 1];
}
