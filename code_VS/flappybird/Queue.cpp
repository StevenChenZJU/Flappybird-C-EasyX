

#include "Queue.h"
#include "flappybird.h"
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

//extern global
//structure
extern struct bird Bird;
//image
extern IMAGE BirdPic[2];


//global


Queue CreateQueue(int MaxElements)
{
	Queue Q;
	Q=(Queue )malloc(sizeof(struct QueueRecord));
	Q->Array = (ElementType *)malloc(MaxElements * sizeof(ElementType));
	Q->Capacity = MAX_ELEMENTS_TUBE;
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
	return Q;
}
int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}
int IsFull(Queue Q)
{
	return Q->Size == MAX_ELEMENTS_TUBE;
}
//when Queue is empty , Rear = Front -1£¬crossing each other
//that is to say that capacity of Queue is the ArraySize - 1
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 1;
	Q ->Rear = 0;
}
//enter the queue

//circular array
static int Succ(int Value, Queue Q)
{
	if (++Value == Q->Capacity)
		Value = 0;
	return Value;
}

void Enqueue(ElementType X, Queue Q)
{
	if (IsFull(Q))
		system("error");
	else
	{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);
		Q->Array[Q->Rear] = X;
	}
}
ElementType Front(Queue Q)
{
	return Q->Array[Q->Front];
}
void Dequeue(Queue Q)
{
	Q->Size--;
	Q->Front=Succ(Q->Front,Q);
}
ElementType FrontAndDequeue(Queue Q)
{
	if (Q->Rear == Q->Front - 1)//Queue is Empty
		system("error");
	else
	{
		Q->Size--;
		return Q->Array[Q->Rear--];
	}

}
