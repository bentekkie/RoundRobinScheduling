/*
 * main.c
 *
 *  Created on: Sep 25, 2017
 *      Author: bente
 */
#define max_line 100
#define max_processes 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	int data;
	struct node* next;
	struct node* prev;
} Node;

typedef struct sprocess{
	int startTime;
	int id;
	int status;
	int serviceTime;
	int counter;
	Node* hddReqs;
	int hddReqs_count;
} process;


void pushData(Node**,int);
void popData(Node**);
process* newProcess(int id, int startTime, int serviceTime);

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	char line[max_line];
	process* processTable[max_processes];
	char * str;
	int time = 0;
	int id = 0;
	int serviceTime = 0;
	int globalTime = 0;
	int hddTime = 0;
	int quantum = 0;
	int pIndex = 0;
	while(gets(line) && line[0] != 0 && pIndex < max_processes){
		time = atoi(strtok(line," "));
		id = atoi(strtok(NULL," "));
		serviceTime = atoi(strtok(NULL," "));
		process* p = newProcess(id, time, serviceTime);
		str = strtok(NULL," ");
		while(str != NULL){
			hddTime = atoi(str);
			pushData(&p->hddReqs,hddTime);
			p->hddReqs_count++;
			str = strtok(NULL," ");
		}
		processTable[pIndex++]=p;
	}
	int i;
	process* idle = newProcess(0, 0, -1);
	processTable[pIndex++]=idle;
	Node* processReadyQueue = NULL;
	Node* hddQueue = NULL;
	pushData(&processReadyQueue,0);
	do {
		for(i = 0; i < pIndex; i++){
			if(processTable[i]->startTime == globalTime){
				pushData(&processReadyQueue,i);
			}
		}
		if(quantum == 500){
			quantum = 0;
			processReadyQueue = processReadyQueue->prev;
		}
		process* currProcess = processTable[processReadyQueue->data];
		currProcess->counter += 100;
		if(currProcess->counter == currProcess->serviceTime){
			popData(processReadyQueue);
		}
		globalTime += 100;
	} while (processReadyQueue != NULL);
	return 0;
}




void pushData(Node** headptr,int data){
	Node* n = NULL;
	Node* head = *headptr;
	while(n == NULL)n = (Node*)malloc(sizeof(Node*));
	n->data = data;
	if(head == NULL) {
		n->next = n;
		n->prev = n;
		*headptr = n;
	}else{
		n->next = head->next;
		n->prev = head;
		n->next->prev = n;
		head->next = n;
	}
}

void popData(Node** headptr){
	Node* head = *headptr;
	if(head == NULL) return;
	if(head->next == head){
		*headptr = NULL;
		free(head);
		return;
	}
	head->next->prev = head->prev;
	head->prev->next = head->next;
	*headptr = head->prev;
	free(head);
	return;
}

process* newProcess(int id,int startTime, int serviceTime){
	process* p = (process*)malloc(sizeof(process));
	p->hddReqs = NULL;
	p->hddReqs_count = 0;
	p->id = id;
	p->startTime = startTime;
	p->serviceTime = serviceTime;
	p->status = 0;
	p->counter = 0;
	return p;
}
