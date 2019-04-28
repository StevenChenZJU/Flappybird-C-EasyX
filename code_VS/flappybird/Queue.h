
#ifndef _Queue_h_
#define _Queue_h_

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "flappybird.h"


struct QueueRecord
{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void Enqueue(ElementType X, Queue Q);
void MakeEmpty(Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);
static int Succ(int Value, Queue Q);


#endif _Queue_h_