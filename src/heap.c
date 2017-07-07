#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs_heap.h"

heap *heap_init()
	{
	heap *maxheap;	
		
	if ((maxheap = malloc(sizeof(heap))) == NULL)
		{
		printf("Error allocating space for heap!\n");
		return NULL;
		}
	
	if ((maxheap->node = malloc(sizeof(info_heap*))) == NULL)
		{
		printf("Error allocating space for heap!\n");
		return NULL;
		}	
	
	maxheap->position = 0;
	maxheap->entries = 1;
	maxheap->income = 0;	
	
	return maxheap;
	}



void insert_heap(heap *maxheap, char *number, float new_amount)
	{
	int index;			
		
	maxheap->income += new_amount;	
		
	if (maxheap->position == 0)
		{		
		info_heap *new_info_heap;
		new_info_heap = malloc(sizeof(info_heap));
		
		new_info_heap->amount = new_amount;
		stpcpy(new_info_heap->info_heap_number, number);
		
		maxheap->node = realloc(maxheap->node, (maxheap->entries + 1) * sizeof(info_heap*));
		
		maxheap->node[1] = malloc(sizeof(info_heap));
		
		maxheap->node[1] = new_info_heap;
		
		maxheap->position = 2;
		(maxheap->entries)++;
		
		return;
		}
	
	//Search on heap if there is node of number
	if ((index = find_index(maxheap, number)) != 0)
		{
		maxheap->node[index]->amount += new_amount;	
	
		heapify(maxheap, index);	
		}
	else
		{
		info_heap *new_info_heap;
		new_info_heap = malloc(sizeof(info_heap));

		new_info_heap->amount = new_amount;
		stpcpy(new_info_heap->info_heap_number, number);
		
		maxheap->node = realloc(maxheap->node, (maxheap->entries + 1) * sizeof(info_heap*));
		
		maxheap->node[maxheap->position] = malloc(sizeof(info_heap));
		
		maxheap->node[maxheap->position] = new_info_heap;

		(maxheap->position)++;
		(maxheap->entries)++;
		
		heapify(maxheap, maxheap->position - 1);
		}
	return;	
	}

//Reform heap after insert	
void heapify(heap *maxheap, int cur_pos)
	{
	while (cur_pos > 1 && maxheap->node[cur_pos/2]->amount < maxheap->node[cur_pos]->amount)
		{
		info_heap *tmp_info_heap;
	
		tmp_info_heap = maxheap->node[cur_pos];
		maxheap->node[cur_pos] = maxheap->node[cur_pos/2];
		maxheap->node[cur_pos/2] = tmp_info_heap;

		cur_pos = cur_pos/2;
		}
	return;		
	}

//Search on heap if there is node of number
int find_index(heap *maxheap, char *number)
	{
	int i;
	
	for (i = 1 ; i < maxheap->position ; i++)
		{
		if (!strcmp(maxheap->node[i]->info_heap_number, number))			
			return i;
			
		}	
	return 0;
	}
		
//Return top customers numbers which have top percentage of income		
int top(heap *maxheap, float goal_amount)
	{
	int i, j, pos = 1, max_index, max_amount, index;		
	int *indexes;	

	if ((indexes = malloc(maxheap->entries * sizeof(int))) == NULL)
		{
		printf("Error allocating space for indexes!\n");
		return -2;
		}
	
	for (i = 0 ; i < maxheap->entries - 1 ; i++)		
		indexes[i] = 0;	
		

	for (i = 0 ; i < maxheap->entries - 1 ; i++)				//check limits
		{
		goal_amount -= maxheap->node[pos]->amount;

		if (goal_amount >= 0)			
			printf("%s  ", maxheap->node[pos]->info_heap_number);			
		else
			{
			free(indexes);	
			return 0;	
			}

		for (j = 0 ; j < maxheap->entries ; j++)
			{
			if (indexes[j] == 0)
				{
				if (2 * pos <= maxheap->position - 1)					
					indexes[j] = 2 * pos;
					
				break;
				}
			}
	
		for (j = 0 ; j < maxheap->entries ; j++)
			{
			if (indexes[j] == 0)
				{
				if (2 * pos + 1 <= maxheap->position - 1)					
					indexes[j] = 2 * pos + 1;
					
				break;
				}
			}	

		max_index = -1;
		max_amount = -1;

		for (j = 0 ; j < maxheap->entries ; j++)
			{
			index = indexes[j];
						
			if (indexes[j] != 0 && maxheap->node[index]->amount >= max_amount)
				{
				max_amount = maxheap->node[index]->amount;
				max_index = index;
				}
			}
				
		indexes[max_index] = 0;
		pos = max_index;
		}
		
	free(indexes);	
	return 0;	
	}

//Calculate the new amount of customer after insert	
float cost(int type, int tarrif, int duration, char *file_config_name)
	{
	float price;
	char input[100];
	char *data1, *data2, *data3;
	FILE *config_file;

	if ((config_file = fopen(file_config_name, "r")) == NULL)
		{
		printf("Error! opening file");
		return -2;         
		}
	
	//Parse data from config file
	fgets(input, sizeof(input), config_file);
	
	while(fgets(input, sizeof(input), config_file) != NULL) 
		{	
		data1 = strtok(input,";");
		data2 = strtok(NULL,";");		
		data3 = strtok(NULL,";");
		
		if (strtof(data1, NULL) == type && strtof(data2, NULL) == tarrif && type == 0)
			{
			price = strtof(data3, NULL);	
				
			fclose(config_file);
			return price;	
			}
		else if (atoi(data1) == type && atoi(data2) == tarrif && type != 0)
			{
			price = strtof(data3, NULL) * duration;	
				
			fclose(config_file);
			return price;	
			}
		}		
	return -1;
	}
		
//Free memory of heap
void bye_heap(heap *maxheap)
	{
	int i;

	for (i = 0 ; i < maxheap->entries ; i++)		
		free(maxheap->node[i]);	
		
	free(maxheap);

	printf("Succsefully heap memory release\n");	
	
	maxheap = NULL;
	return;	
	}
		
//Print heap's elements	
void display(heap *maxheap) 
	{
	int i;
	
	for(i = 1; i < maxheap->entries ; i++) 
		{
		printf("| %s | %.2f |", maxheap->node[i]->info_heap_number, maxheap->node[i]->amount);
		printf("\n");
		}
	return;
	}