/*
 * hddRead.c
 *
 *  Created on: Sep 25, 2017
 *      Author: bente
 */
#include "hddRead.h"
#include <stdlib.h>
#include<stdio.h>

hddRead* newHddRead(int time){
	hddRead* h = NULL;
	while(h == NULL)h = (hddRead*)malloc(sizeof(hddRead));
	h->time = time;
	return h;
}
hddReadQueue* newHddReadQueue(){
	hddReadQueue* q = NULL;
	while(q == NULL) q = (hddReadQueue*)malloc(sizeof(hddReadQueue));
	q->head = NULL;
	q->tail = NULL;
	q->size_t = 0;
	return q;
}
void enqueueHddReadQueue(hddReadQueue* q, int time){
	if(q != NULL){
		hddRead* h = newHddRead(time);
		h->next = q->tail;
		if(q->tail != NULL){
			q->tail->prev = h;
		}
		q->tail = h;
		if(q->size_t == 0){
			q->head = h;
		}
		q->size_t++;
	}
}
int dequeueHddReadQueue(hddReadQueue* q){
	if(q == NULL || q->size_t < 1){
		return 0;
	}else{
		hddRead* h = q->head;
		int t = h->time;
		q->head = h->prev;
		q->size_t--;
		if(q->head != NULL)q->head->next = NULL;
		free(h);
		return t;
	}
}
void printHddReads(hddReadQueue* q){
	printHddRead(q->head);
}

void printHddRead(hddRead* h){
	if(h != NULL){
		printf("%d ",h->time);
		printHddRead(h->prev);
	}
}


