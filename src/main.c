#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "functions.h"
#include "structs_heap.h"


int main(int argc, char* argv[])
	{
	int i, size_hash1, size_hash2, size_bucket;
	char file_input_name[20], file_config_name[20], input[100], tmp_input[100], date[5], time[5], originator_number[20], destination_number[20], cdr_uniq_id[15];	
	char *data;
	float new_amount;	
	FILE *input_file;
	
	//Parse arguments from command line
	if (argc == 11)									
		{
		for (i = 1 ; i < (argc-1) ; i++)
			{
			if (!strcmp(argv[i], "-o"))
				{
				stpcpy(file_input_name, argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-h1"))
				{
				size_hash1 = atoi(argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-h2"))
				{
				size_hash2 = atoi(argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-s"))
				{
				size_bucket = atoi(argv[++i]);
				continue;
				}
			if (!strcmp(argv[i], "-c"))
				{
				stpcpy(file_config_name, argv[++i]);
				continue;
				}	
			printf("Wrong input arguments! \n");
			return -1;
			}
		}
	else
		{
		printf("Wrong input arguments! \n");
		return -1;	
		}
		
	hash_table *hashtable1 = NULL;	
	hash_table *hashtable2 = NULL;
	heap *maxheap = NULL;

	
	if ((input_file = fopen(file_input_name, "r")) == NULL)
		{
        printf("Error! opening file\n");
        return -2;         
		}
		
	//Parse data from input file	
	while(fgets(input, sizeof(input), input_file) != NULL)   
		{
		stpcpy(tmp_input, input);
		data = strtok (input," ");		
		
		if (!strcmp(data, "insert"))
			{
			//Check if structures are already created or not	
			if (hashtable1 == NULL)
				{
				hashtable1 = hash_init(size_hash1, size_bucket);

				hashtable2 = hash_init(size_hash1, size_bucket);

				maxheap = heap_init();			
				}
										
			info_caller *new_infocaller1;
			new_infocaller1 = malloc(sizeof(info_caller));
					
			//cdr_uniq_id
			data = strtok(NULL,";");
			new_infocaller1->cdr_uniq_id = malloc(strlen(data) + 1);
			strcpy(new_infocaller1->cdr_uniq_id, data);
				
			//originator_number
			data = strtok(NULL,";");				
			strcpy(originator_number, data);			
	
			//destination_number
			data = strtok(NULL,";");				
			strcpy(new_infocaller1->info_number, data);
			strcpy(destination_number, data);
	
			//date			
			data = strtok(NULL,";");				
			
			strncpy(date, data, 2);
			date[2] = 0;
			new_infocaller1->date_day = atoi(date);
			
			strncpy(date, data + 2, 2);
			date[2] = 0;
			new_infocaller1->date_month = atoi(date);
			
			strncpy(date, data + 4, 4);
			date[4] = 0;
			new_infocaller1->date_year = atoi(date);
						
			//init_time
			data = strtok(NULL,";");
			
			strncpy(time, data, 2);
			time[2] = 0;
			new_infocaller1->init_time_hour = atoi(time);
	
			strncpy(time, data + 3, 2);
			time[2] = 0;
			new_infocaller1->init_time_minute = atoi(time);
	
			//duration
			data = strtok(NULL,";");							
			new_infocaller1->duration = atoi(data);

			//type
			data = strtok(NULL,";");							
			new_infocaller1->type = atoi(data);
			
			//tarrif
			data = strtok(NULL,";");							
			new_infocaller1->tarrif = atoi(data);
						
			//fault_condition
			data = strtok(NULL,";");							
			new_infocaller1->fault_condition = atoi(data);
	
			//Insert on hash table 1
			insert(hashtable1, new_infocaller1, originator_number);

			//Insert on hash table 2
			info_caller *new_infocaller2;
			new_infocaller2 = malloc(sizeof(info_caller));
			
			new_infocaller2->cdr_uniq_id = malloc(strlen(new_infocaller1->cdr_uniq_id));
			
			strcpy(new_infocaller2->cdr_uniq_id, new_infocaller1->cdr_uniq_id);							
			strcpy(new_infocaller2->info_number, originator_number);
			new_infocaller2->date_day = new_infocaller1->date_day;		
			new_infocaller2->date_month = new_infocaller1->date_month;			
			new_infocaller2->date_year = new_infocaller1->date_year;		
			new_infocaller2->init_time_hour = new_infocaller1->init_time_hour;		
			new_infocaller2->init_time_minute = new_infocaller1->init_time_minute;								
			new_infocaller2->duration = new_infocaller1->duration;						
			new_infocaller2->type = new_infocaller1->type;								
			new_infocaller2->tarrif = new_infocaller1->tarrif;							
			new_infocaller2->fault_condition = new_infocaller1->fault_condition;

			insert(hashtable2, new_infocaller2, destination_number);
			
			//Insert to binary max heap
			if (new_infocaller1->fault_condition >= 200 && new_infocaller1->fault_condition < 300)
				{
				new_amount = cost(new_infocaller1->type, new_infocaller1->tarrif, new_infocaller1->duration, file_config_name);

				insert_heap(maxheap, originator_number, new_amount);						
				}	
			continue;
			}
		else if (!strcmp(data, "delete"))
			{
			data = strtok (NULL," ");			
			strcpy(cdr_uniq_id, data);	
			data = strtok (NULL," ");			
			strcpy(originator_number, data);
			originator_number[14] = 0;
			
			delete(hashtable1, originator_number, cdr_uniq_id);	
			}
		else if (!strcmp(data, "find"))
			{
			int arguments = countWords(tmp_input);

			data = strtok (NULL," ");			
			strcpy(originator_number, data);
			originator_number[14] = 0;
			
			if (arguments == 2)
				{
				find(hashtable1, originator_number, " ", " ", " ", " ");			
				}
			else if (arguments == 4)
				{
				char time1[5], time2[5];
					
				data = strtok (NULL," ");
				strncpy(time1, data, 5);
				
				data = strtok (NULL," ");
				strncpy(time2, data, 5);
				
				find(hashtable1, originator_number, time1, time2, " ", " ");	
				}
			else if (arguments == 6)
				{
				char time1[5], time2[5], date1[10], date2[10];	
			
				data = strtok (NULL," ");
				strncpy(time1, data, 5);

				data = strtok (NULL," ");
				strncpy(date1, data, 8);

				data = strtok (NULL," ");
				strncpy(time2, data, 5);
								
				data = strtok (NULL," ");
				strncpy(date2, data, 8);
								
				find(hashtable1, originator_number, time1, time2, date1, date2);		
				}
			else
				{
				printf("INFO: Bad input arguments.\n");
				printf("INFO: Please try again..\n");	
				}
			}
		else if (!strcmp(data, "lookup"))
			{				
			int arguments = countWords(tmp_input);	
			
			data = strtok (NULL," ");
			strcpy(destination_number, data);
			destination_number[14] = 0;
						
			if (arguments == 2)
				{
				lookup(hashtable2, destination_number, " ", " ", " ", " ");				
				}
			else if (arguments == 4)
				{
				char time1[5], time2[5];
					
				data = strtok (NULL," ");
				strncpy(time1, data, 5);
				
				data = strtok (NULL," ");
				strncpy(time2, data, 5);
				
				lookup(hashtable2, destination_number, time1, time2, " ", " ");		
				}
			else if (arguments == 6)
				{
				char time1[5], time2[5], date1[10], date2[10];	
			
				data = strtok (NULL," ");
				strncpy(time1, data, 5);

				data = strtok (NULL," ");
				strncpy(date1, data, 8);
				date1[8] = 0;
				
				data = strtok (NULL," ");
				strncpy(time2, data, 5);
								
				data = strtok (NULL," ");
				strncpy(date2, data, 8);
				date2[8] = 0;
				
				lookup(hashtable2, destination_number, time1, time2, date1, date2);				
				}
			else
				{
				printf("INFO: Bad input arguments.\n");
				printf("INFO: Please try again..\n");
				}
			}
		else if (!strcmp(data, "indist"))
			{
			data = strtok (NULL," ");
			strcpy(originator_number, data);
			originator_number[14] = 0;	
			
			data = strtok (NULL," ");
			strcpy(destination_number, data);
			destination_number[14] = 0;	
								
			indist(hashtable1, hashtable2, originator_number, destination_number);
			}
		else if (!strcmp(data, "topdest"))
			{		
			data = strtok (NULL," ");			
			strcpy(originator_number, data);
			originator_number[14] = 0;

			topdest(hashtable1, originator_number);
			}
		else if (!strcmp(data, "top"))
			{
			float goal_amount; 
			int percentage = 5;
			
			data = strtok (NULL," ");
			percentage = atoi(data);
			
			goal_amount = maxheap->income * ( (float) percentage/ (float) 100);
		
			printf("Customers with top %d percent of company's income: ", percentage);
			
			top(maxheap, goal_amount);
			}
		else if (!strncmp(data, "bye", sizeof("bye")-1))
			{
			bye(hashtable1);
			
			bye(hashtable2);
	
			bye_heap(maxheap);
			}
		else if (!strcmp(data, "print"))
			{	
			data = strtok(NULL," ");
			
			if (!strncmp(data,"hashtable1", sizeof("hashtable1")-1))
				{
				printf("----------------- HashTable1 -----------------\n\n");
				print(hashtable1);
				}
			else if (!strncmp(data,"hashtable2", sizeof("hashtable2")-1))
				{
				printf("----------------- HashTable2 -----------------\n\n");
				print(hashtable2);
				}			
			}
		else   
			{
			printf("INFO: Bad input.\n");
			printf("INFO: Please try again..\n");
			}
		printf("\n");	
		}	

	fclose(input_file);	
	return 0;
	}