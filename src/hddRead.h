/*
 * hddRead.h
 *
 *  Created on: Sep 25, 2017
 *      Author: bente
 */

#ifndef HDDREAD_H_
#define HDDREAD_H_

typedef struct shddRead{
	struct shddRead* next;
	struct shddRead* prev;
	int time;
} hddRead;

typedef struct hddReadQueue{
	hddRead* head;
	hddRead* tail;
	int size_t;
} hddReadQueue;
void printHddRead(hddRead* h);
hddRead* newHddRead(int time);
hddReadQueue* newHddReadQueue();
void enqueueHddReadQueue(hddReadQueue* q, int time);
int dequeueHddReadQueue(hddReadQueue* q);
void printHddReads(hddReadQueue*);

#endif /* HDDREAD_H_ */
