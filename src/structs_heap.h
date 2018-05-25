#ifndef _STRUCTS_HEAP_
#define _STRUCTS_HEAP_


//Binary Max Heap
typedef struct _heap_
	{
	int position;
	int entries;
	float income;
	struct _info_heap_ **node;
	}heap;


typedef struct _info_heap_
	{
	char info_heap_number[15];
	float amount;
	}info_heap;


heap *heap_init();

void insert_heap(heap *, char *, float);

void heapify(heap *, int);

int find_index(heap *, char *);

int top(heap *, float);

float cost(int, int, int, char *);

void bye_heap(heap *maxheap);

void display(heap *);

#endif
