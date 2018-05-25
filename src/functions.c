#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

//Hash function for hash table
int hash_function(char *K, int size) {
	int h = 0, a = 127;

	for (; *K!='\0' ; K++)
		h=(a*h + *K) % size;

	return h;
}

//Return number of words in string
int countWords(char *str) {
	int state = 1, count = 0;

	//Scan string character by character
	while (*str) {
		//If next character is a separator, set the state as OUT
		if (*str == ' ' || *str == '\n' || *str == '\t')
			state = 1;
		else if (state) {
			state = 0;
			count++;
		}
		++str;
	}
	return count;
}


hash_table *hash_init(int size_hash, int size_bucket) {
	int i;
	hash_table *hashtable;

	if ((hashtable = malloc(sizeof(hash_table))) == NULL) {
		printf("Error allocating space for hash table!\n");
		return NULL;
	}

	if ((hashtable->table = malloc(size_hash * sizeof(bucket_caller*))) == NULL) {
		printf("Error allocating space for hash table!\n");
		return NULL;
	}

	for (i = 1 ; i < size_hash ; i++)
		hashtable->table[i] = NULL;

	hashtable->size = size_hash;
	hashtable->size_bucket = size_bucket;

	return hashtable;
}

//Insert new record on hash table
void insert(hash_table *hashtable1, info_caller *new_infocaller, char *number) {
	int i, j, index;

	bucket_caller *tmp_bucketcaller;

	if (hashtable1 == NULL) {
		printf("IError\n");
		return;
	}

	index = hash_function(number, hashtable1->size);

	tmp_bucketcaller = hashtable1->table[index];

	if (tmp_bucketcaller == NULL) {
		bucket_info_caller *new_bucketinfocaller;
		new_bucketinfocaller = malloc(sizeof(bucket_info_caller));

		new_bucketinfocaller->entries_max = (hashtable1->size_bucket / sizeof(info_caller*));
		new_bucketinfocaller->entries_current = 1;
		new_bucketinfocaller->next = NULL;

		new_bucketinfocaller->info = malloc((new_bucketinfocaller->entries_max) * sizeof(info_caller*));

		for (j = 0 ; j < new_bucketinfocaller->entries_max ; j++)
			new_bucketinfocaller->info[j] = NULL;

		new_bucketinfocaller->info[0] = new_infocaller;

		caller *new_caller;
		new_caller = malloc(sizeof(caller));

		stpcpy(new_caller->number, number);
		new_caller->bucket = new_bucketinfocaller;


		bucket_caller *new_bucketcaller;
		new_bucketcaller = malloc(sizeof(bucket_caller));

		new_bucketcaller->entries_max = (hashtable1->size_bucket / sizeof(caller*));
		new_bucketcaller->entries_current = 1;
		new_bucketcaller->next = NULL;

		new_bucketcaller->caller = malloc((new_bucketcaller->entries_max) * sizeof(caller*));

		for (j = 0 ; j < new_bucketcaller->entries_max ; j++)
			new_bucketcaller->caller[j] = NULL;

		new_bucketcaller->caller[0] = new_caller;

		hashtable1->table[index] = new_bucketcaller;

		return;
	}
	else {
		caller *tmp_caller;

		while (1) {
			for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
				tmp_caller = tmp_bucketcaller->caller[i];

				if (tmp_caller != NULL) {
					if (!strcmp(tmp_caller->number, number)) {
						bucket_info_caller *tmp_bucketinfocaller;

						tmp_bucketinfocaller = tmp_caller->bucket;

						while (tmp_bucketinfocaller->entries_max == tmp_bucketinfocaller->entries_current) {
							tmp_bucketinfocaller = tmp_bucketinfocaller->next;

							if (tmp_bucketinfocaller == NULL) {
								bucket_info_caller *new_bucketinfocaller;
								new_bucketinfocaller = malloc(sizeof(bucket_info_caller));

								new_bucketinfocaller->entries_max = (hashtable1->size_bucket / sizeof(info_caller*));
								new_bucketinfocaller->entries_current = 1;
								new_bucketinfocaller->next = NULL;

								new_bucketinfocaller->info = malloc((new_bucketinfocaller->entries_max) * sizeof(info_caller*));

								for (j = 0 ; j < new_bucketinfocaller->entries_max ; j++)
									new_bucketinfocaller->info[j] = NULL;

								new_bucketinfocaller->info[0] = new_infocaller;

								return;
							}
						}
						for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
							if (tmp_bucketinfocaller->info[j] == NULL) {
								tmp_bucketinfocaller->info[j] = new_infocaller;
								(tmp_bucketinfocaller->entries_current)++;

								return;
							}
						}
					}
				}
			}
			if (tmp_bucketcaller->next == NULL && tmp_bucketcaller->entries_max == tmp_bucketcaller->entries_current) {
				bucket_info_caller *new_bucketinfocaller;
				new_bucketinfocaller = malloc(sizeof(bucket_info_caller));

				new_bucketinfocaller->entries_max = (hashtable1->size_bucket / sizeof(info_caller*));
				new_bucketinfocaller->entries_current = 1;
				new_bucketinfocaller->next = NULL;

				new_bucketinfocaller->info = malloc((new_bucketinfocaller->entries_max) * sizeof(info_caller*));

				for (j = 0 ; j < new_bucketinfocaller->entries_max ; j++)
					new_bucketinfocaller->info[j] = NULL;

				new_bucketinfocaller->info[0] = new_infocaller;

				caller *new_caller;
				new_caller = malloc(sizeof(caller));

				stpcpy(new_caller->number, number);
				new_caller->bucket = new_bucketinfocaller;

				bucket_caller *new_bucketcaller;
				new_bucketcaller = malloc(sizeof(bucket_caller));

				new_bucketcaller->entries_max = (hashtable1->size_bucket / sizeof(caller*));
				new_bucketcaller->entries_current = 1;
				new_bucketcaller->next = NULL;

				new_bucketcaller->caller = malloc((new_bucketcaller->entries_max) * sizeof(caller*));

				for (j = 0 ; j < new_bucketcaller->entries_max ; j++)
					new_bucketcaller->caller[j] = NULL;

				new_bucketcaller->caller[0] = new_caller;

				tmp_bucketcaller->next = new_bucketcaller;

				return;
			}
			else if (tmp_bucketcaller->next == NULL && tmp_bucketcaller->entries_max != tmp_bucketcaller->entries_current) {
				for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
					tmp_caller = tmp_bucketcaller->caller[i];

					if (tmp_caller == NULL) {
						bucket_info_caller *new_bucketinfocaller;
						new_bucketinfocaller = malloc(sizeof(bucket_info_caller));

						new_bucketinfocaller->entries_max = (hashtable1->size_bucket / sizeof(info_caller*));
						new_bucketinfocaller->entries_current = 1;
						new_bucketinfocaller->next = NULL;

						new_bucketinfocaller->info = malloc((new_bucketinfocaller->entries_max) * sizeof(info_caller*));

						for (j = 0 ; j < new_bucketinfocaller->entries_max ; j++)
							new_bucketinfocaller->info[j] = NULL;

						new_bucketinfocaller->info[0] = new_infocaller;

						caller *new_caller;
						new_caller = malloc(sizeof(caller));

						stpcpy(new_caller->number, number);
						new_caller->bucket = new_bucketinfocaller;
						tmp_bucketcaller->caller[i] = new_caller;

						(tmp_bucketcaller->entries_current)++;
						return;
					}
				}
			}
			tmp_bucketcaller = tmp_bucketcaller->next;
		}
	}
}

//Delete record with number and cdr_id
void delete(hash_table *hashtable1, char *number, char *cdr_id) {
	int i, j, k, index;

	bucket_caller *tmp_bucketcaller;

	if (hashtable1 == NULL) {
		printf("DError\n");
		return;
	}

	index = hash_function(number, hashtable1->size);

	tmp_bucketcaller = hashtable1->table[index];

	if (tmp_bucketcaller == NULL) {
		printf("DError");
		return;
	}

	caller *tmp_caller;

	while(1) {
		for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++){
			tmp_caller = tmp_bucketcaller->caller[i];

			if (tmp_caller != NULL) {
				if (!strncmp(tmp_caller->number, number, sizeof(number)-1)) {
					bucket_info_caller *tmp_bucketinfocaller;

					tmp_bucketinfocaller = tmp_caller->bucket;

					info_caller *tmp_infocaller;

					while(1) {
						for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
							tmp_infocaller = tmp_bucketinfocaller->info[j];

							if (tmp_infocaller != NULL) {
								if (!strncmp(tmp_infocaller->cdr_uniq_id, cdr_id, sizeof(cdr_id)-1)) {
									free(tmp_infocaller);
									tmp_bucketinfocaller->info[j] = NULL;
									tmp_bucketinfocaller->entries_current--;

									printf("Deleted %s \n", cdr_id);

									return;
								}
							}
						}
						if (tmp_bucketinfocaller->next == NULL) {
							printf("DError", number);
							return;
						}
						tmp_bucketinfocaller = tmp_bucketinfocaller->next;
					}
				}
			}
		}
		if (tmp_bucketcaller->next == NULL) {
				printf("DError", number);
				return;
			}
		tmp_bucketcaller = tmp_bucketcaller->next;
	}
}

//Find all records on hash table 1 of originator number with specific limits
void find(hash_table *hashtable1, char *originator_number, char *time1, char *time2, char *date1, char *date2) {
	int i, j, index, choice;

	int hour1, min1, hour2, min2, day1, month1, year1, day2, month2, year2;

	bucket_caller *tmp_bucketcaller;

	if (hashtable1 == NULL) {
		printf("No CDRs found\n");
		return;
	}

	index = hash_function(originator_number, hashtable1->size);

	tmp_bucketcaller = hashtable1->table[index];

	if (!strcmp(time1, " ") && !strcmp(date1, " "))
		choice = 1;
	else if(!strcmp(date1, " ")) {
		char time[5];

		strncpy(time, time1, 2);
		time[2] = 0;
		hour1 = atoi(time);

		strncpy(time, time1 + 3, 2);
		time[2] = 0;
		min1 = atoi(time);

		strncpy(time, time2, 2);
		time[2] = 0;
		hour2 = atoi(time);

		strncpy(time, time2 + 3, 2);
		time[2] = 0;
		min2 = atoi(time);

		choice = 2;
	}
	else {
		char time[5], date[5];

		strncpy(time, time1, 2);
		time[2] = 0;
		hour1 = atoi(time);

		strncpy(time, time1 + 3, 2);
		time[2] = 0;
		min1 = atoi(time);

		strncpy(time, time2, 2);
		time[2] = 0;
		hour2 = atoi(time);

		strncpy(time, time2 + 3, 2);
		time[2] = 0;
		min2 = atoi(time);


		strncpy(date, date1, 2);
		date[2] = 0;
		day1 = atoi(date);

		strncpy(date, date1 + 2, 2);
		date[2] = 0;
		month1 = atoi(date);

		strncpy(date, date1 + 4, 4);
		date[4] = 0;
		year1 = atoi(date);


		strncpy(date, date2, 2);
		date[2] = 0;
		day2 = atoi(date);

		strncpy(date, date2 + 2, 2);
		date[2] = 0;
		month2 = atoi(date);

		strncpy(date, date2 + 4, 4);
		date[4] = 0;
		year2 = atoi(date);

		choice = 3;
	}

	if (tmp_bucketcaller == NULL) {
		printf("No CDRs found\n");
		return;
	}

	caller *tmp_caller;

	while(1) {
		for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
			tmp_caller = tmp_bucketcaller->caller[i];

			if (!strncmp(tmp_caller->number, originator_number, sizeof(originator_number)-1)) {
				bucket_info_caller *tmp_bucketinfocaller;

				tmp_bucketinfocaller = tmp_caller->bucket;

				info_caller *tmp_infocaller;

				while(1) {
					printf("--------- Records for %s caller ---------\n", originator_number);

					for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
						tmp_infocaller = tmp_bucketinfocaller->info[j];

						if (tmp_infocaller != NULL) {
							if (choice == 1) {
								printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
								printf("Destination: %s\n", tmp_infocaller->info_number);
								printf("Day: %d\n", tmp_infocaller->date_day);
								printf("Month: %d\n", tmp_infocaller->date_month);
								printf("Year: %d\n", tmp_infocaller->date_year);
								printf("Hour: %d\n", tmp_infocaller->init_time_hour);
								printf("Minute: %d\n", tmp_infocaller->init_time_minute);
								printf("Duration: %d\n", tmp_infocaller->duration);
								printf("Type: %d\n", tmp_infocaller->type);
								printf("Tarrif: %d\n", tmp_infocaller->tarrif);
								printf("Fault: %d\n", tmp_infocaller->fault_condition);

								printf("\n");
							}
							else if (choice == 2) {
								int hour = tmp_infocaller->init_time_hour;
								int minute = tmp_infocaller->init_time_minute;

								if (time(hour, hour1, hour2, minute, min1, min2)) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Destination: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
							}
							else if (choice == 3) {
								int hour = tmp_infocaller->init_time_hour;
								int minute = tmp_infocaller->init_time_minute;
								int day = tmp_infocaller->date_day;
								int month = tmp_infocaller->date_month;
								int year = tmp_infocaller->date_year;

								if (date(day, day1, day2, month, month1, month2, year, year1, year2) == 1) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Destination: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
								else if ((date(day, day1, day2, month, month1, month2, year, year1, year2) == 2) && time(hour, hour1, hour2, minute, min1, min2)) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Destination: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
							}
						}
					}
					if (tmp_bucketinfocaller->next == NULL)
						return;

					tmp_bucketinfocaller = tmp_bucketinfocaller->next;
				}
			}
		}

		if(tmp_bucketcaller->next == NULL){
			printf("No CDRs found\n");
			return;
		}

		tmp_bucketcaller = tmp_bucketcaller->next;
	}
}

//Find all records on hash table 2 of destination number with specific limits
void lookup(hash_table *hashtable2, char *destination_number, char *time1, char *time2, char *date1, char *date2) {
	int i, j, index, choice, hour1, min1, hour2, min2, day1, month1, year1, day2, month2, year2;

	bucket_caller *tmp_bucketcaller;

	if (hashtable2 == NULL) {
		printf("No CDRs found\n");
		return;
	}

	index = hash_function(destination_number, hashtable2->size);

	tmp_bucketcaller = hashtable2->table[index];

	if (!strcmp(time1, " ") && !strcmp(date1, " "))
		choice = 1;
	else if(!strcmp(date1, " ")) {
		char time[5];

		strncpy(time, time1, 2);
		time[2] = 0;
		hour1 = atoi(time);

		strncpy(time, time1 + 3, 2);
		time[2] = 0;
		min1 = atoi(time);

		strncpy(time, time2, 2);
		time[2] = 0;
		hour2 = atoi(time);

		strncpy(time, time2 + 3, 2);
		time[2] = 0;
		min2 = atoi(time);

		choice = 2;
	}
	else {
		char time[5], date[5];

		strncpy(time, time1, 2);
		time[2] = 0;
		hour1 = atoi(time);

		strncpy(time, time1 + 3, 2);
		time[2] = 0;
		min1 = atoi(time);

		strncpy(time, time2, 2);
		time[2] = 0;
		hour2 = atoi(time);

		strncpy(time, time2 + 3, 2);
		time[2] = 0;
		min2 = atoi(time);


		strncpy(date, date1, 2);
		date[2] = 0;
		day1 = atoi(date);

		strncpy(date, date1 + 2, 2);
		date[2] = 0;
		month1 = atoi(date);

		strncpy(date, date1 + 4, 4);
		date[4] = 0;
		year1 = atoi(date);


		strncpy(date, date2, 2);
		date[2] = 0;
		day2 = atoi(date);

		strncpy(date, date2 + 2, 2);
		date[2] = 0;
		month2 = atoi(date);

		strncpy(date, date2 + 4, 4);
		date[4] = 0;
		year2 = atoi(date);

		choice = 3;
	}

	if (tmp_bucketcaller == NULL) {
		printf("No CDRs found\n");
		return;
	}

	caller *tmp_caller;

	while(1) {
		for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
			tmp_caller = tmp_bucketcaller->caller[i];

			if (!strncmp(tmp_caller->number, destination_number, sizeof(destination_number)-1)) {
				bucket_info_caller *tmp_bucketinfocaller;

				tmp_bucketinfocaller = tmp_caller->bucket;

				info_caller *tmp_infocaller;

				while(1) {
					printf("--------- Records for %s callee ---------\n", destination_number);

					for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
						tmp_infocaller = tmp_bucketinfocaller->info[j];

						if (tmp_infocaller != NULL) {
							if (choice == 1) {
								printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
								printf("Originator: %s\n", tmp_infocaller->info_number);
								printf("Day: %d\n", tmp_infocaller->date_day);
								printf("Month: %d\n", tmp_infocaller->date_month);
								printf("Year: %d\n", tmp_infocaller->date_year);
								printf("Hour: %d\n", tmp_infocaller->init_time_hour);
								printf("Minute: %d\n", tmp_infocaller->init_time_minute);
								printf("Duration: %d\n", tmp_infocaller->duration);
								printf("Type: %d\n", tmp_infocaller->type);
								printf("Tarrif: %d\n", tmp_infocaller->tarrif);
								printf("Fault: %d\n", tmp_infocaller->fault_condition);

								printf("\n");
							}
							else if (choice == 2) {
								int hour = tmp_infocaller->init_time_hour;
								int minute = tmp_infocaller->init_time_minute;

								if (time(hour, hour1, hour2, minute, min1, min2)) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Originator: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
							}
							else if (choice == 3) {
								int hour = tmp_infocaller->init_time_hour;
								int minute = tmp_infocaller->init_time_minute;
								int day = tmp_infocaller->date_day;
								int month = tmp_infocaller->date_month;
								int year = tmp_infocaller->date_year;

								if (date(day, day1, day2, month, month1, month2, year, year1, year2) == 1) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Originator: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
								else if ((date(day, day1, day2, month, month1, month2, year, year1, year2) == 2) && time(hour, hour1, hour2, minute, min1, min2)) {
									printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
									printf("Originator: %s\n", tmp_infocaller->info_number);
									printf("Day: %d\n", tmp_infocaller->date_day);
									printf("Month: %d\n", tmp_infocaller->date_month);
									printf("Year: %d\n", tmp_infocaller->date_year);
									printf("Hour: %d\n", tmp_infocaller->init_time_hour);
									printf("Minute: %d\n", tmp_infocaller->init_time_minute);
									printf("Duration: %d\n", tmp_infocaller->duration);
									printf("Type: %d\n", tmp_infocaller->type);
									printf("Tarrif: %d\n", tmp_infocaller->tarrif);
									printf("Fault: %d\n", tmp_infocaller->fault_condition);

									printf("\n");
								}
							}
						}
					}

					if (tmp_bucketinfocaller->next == NULL)
						return;

					tmp_bucketinfocaller = tmp_bucketinfocaller->next;
				}
			}
		}

		if(tmp_bucketcaller->next == NULL) {
			printf("No CDRs found\n");
			return;
		}

		tmp_bucketcaller = tmp_bucketcaller->next;
	}
}

//Print all records on hash table
void print(hash_table *hashtable) {
	int i, j, k;

	bucket_caller *tmp_bucketcaller;

	caller *tmp_caller;

	bucket_info_caller *tmp_bucketinfocaller;

	info_caller *tmp_infocaller;

	if (hashtable == NULL) {
		printf("There is no hashtable!\n");
		return;
	}

	for (i = 0 ; i < hashtable->size ; i++) {
		tmp_bucketcaller = hashtable->table[i];

		if (tmp_bucketcaller == NULL)
			printf(" --------- There is no record for hash index %d --------- \n", i);
		else {
			printf(" --------- Record(s) for hash index %d ---------\n", i);

			while(1) {
				for (j = 0 ; j < tmp_bucketcaller->entries_max ; j++) {
					tmp_caller = tmp_bucketcaller->caller[j];

					if (tmp_caller != NULL) {
						printf("Data for caller number %s :\n", tmp_caller->number);

						tmp_bucketinfocaller = tmp_caller->bucket;

						if (tmp_bucketinfocaller != NULL) {
							while(1) {
								for (k = 0 ; k < tmp_bucketinfocaller->entries_max ; k++) {
									tmp_infocaller = tmp_bucketinfocaller->info[k];

									if (tmp_infocaller != NULL) {
										printf("ID: %s\n", tmp_infocaller->cdr_uniq_id);
										printf("Destination: %s\n", tmp_infocaller->info_number);
										printf("Day: %d\n", tmp_infocaller->date_day);
										printf("Month: %d\n", tmp_infocaller->date_month);
										printf("Year: %d\n", tmp_infocaller->date_year);
										printf("Hour: %d\n", tmp_infocaller->init_time_hour);
										printf("Minute: %d\n", tmp_infocaller->init_time_minute);
										printf("Duration: %d\n", tmp_infocaller->duration);
										printf("Type: %d\n", tmp_infocaller->type);
										printf("Tarrif: %d\n", tmp_infocaller->tarrif);
										printf("Fault: %d\n", tmp_infocaller->fault_condition);

										printf("\n");
									}
								}
								if (tmp_bucketinfocaller->next == NULL)
									break;

								tmp_bucketinfocaller = tmp_bucketinfocaller->next;
							}
						}
					}
				}
				if (tmp_bucketcaller->next == NULL)
					break;

				tmp_bucketcaller = tmp_bucketcaller->next;
			}
		}
	}
	return;
}


//Find top destination code alongside of records of originator number
void topdest(hash_table *hashtable1, char *originator_number) {
	int i, j, index, found , top_sum = -1;
	char code[5];

	dest_node *head = NULL;

	if (hashtable1 == NULL) {
		printf("No calls found\n");
		return;
	}

	bucket_caller *tmp_bucketcaller;

	index = hash_function(originator_number, hashtable1->size);

	tmp_bucketcaller = hashtable1->table[index];

	if (tmp_bucketcaller == NULL) {
		printf("No calls found\n");
		return;
	}

	caller *tmp_caller;

	while(1) {
		for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
			tmp_caller = tmp_bucketcaller->caller[i];

			if (tmp_caller != NULL) {
				if (!strcmp(tmp_caller->number, originator_number)) {
					bucket_info_caller *tmp_bucketinfocaller;

					tmp_bucketinfocaller = tmp_caller->bucket;

					info_caller *tmp_infocaller;

					while(1) {
						for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
							tmp_infocaller = tmp_bucketinfocaller->info[j];
							found = -1;

							if (tmp_infocaller != NULL) {
								strncpy(code, tmp_infocaller->info_number, 3);

								if (head == NULL) {
									dest_node *new_node;
									new_node = malloc(sizeof(dest_node));

									strcpy(new_node->code, code);
									new_node->count = 1;
									new_node->next = NULL;
									found = 0;

									head = new_node;
								}
								else {
									dest_node *cur_node;
									cur_node = head;

									while(cur_node != NULL) {
										if (!strcmp(cur_node->code, code)) {
											(cur_node->count)++;
											found = 0;
											break;
										}
										cur_node = cur_node->next;
									}
								}

								//If there is no node with current code create new one and linked it to the list
								if (found != 0) {
									dest_node *new_node;
									new_node = malloc(sizeof(dest_node));

									strcpy(new_node->code, code);
									new_node->count = 1;
									new_node->next = head;
									head = new_node;
								}
							}
						}
						if (tmp_bucketinfocaller->next == NULL)
							break;

						tmp_bucketinfocaller = tmp_bucketinfocaller->next;
					}

					//Check every node and find most popular code
					dest_node *cur_node;
					cur_node = head;

					while(cur_node != NULL) {
						if (cur_node->count > top_sum)
							top_sum = cur_node->count;

						cur_node = cur_node->next;
					}

					//Go through the list and print every code with same ammount of calls as the most popular one
					cur_node = head;

					while(cur_node != NULL) {
						if (cur_node->count == top_sum)
							printf("Country code: %s, Calls made: %d  ", cur_node->code, top_sum);

						cur_node = cur_node->next;
					}

					//Free linked list
					dest_node *tmp_node;
					cur_node = head;

					while(cur_node != NULL) {
						tmp_node = cur_node;
						cur_node = cur_node->next;
						free(tmp_node);
					}
					head = NULL;

					return;
				}
			}
		}

		if(tmp_bucketcaller->next == NULL) {
			printf("No calls found\n");
			return;
		}

		tmp_bucketcaller = tmp_bucketcaller->next;
	}
}

//Function that checks if caller1 and caller2 contacted each other either as caller either as callee
int relation(hash_table * hashtable2, char *caller1, char *caller2) {
	int i, j, k, index;

	bucket_caller *tmp_bucketcaller;

	if (hashtable2 == NULL) {
		printf("No calls found\n");
		return;
	}

	index = hash_function(caller1, hashtable2->size);

	tmp_bucketcaller = hashtable2->table[index];

	if (tmp_bucketcaller == NULL)
		return 1;

	caller *tmp_caller;

	while(1) {
		for (i = 0 ; i < tmp_bucketcaller->entries_max ; i++) {
			tmp_caller = tmp_bucketcaller->caller[i];

			if (tmp_caller != NULL) {
				if (!strncmp(tmp_caller->number, caller1, sizeof(caller1)-1)) {
					bucket_info_caller *tmp_bucketinfocaller;

					tmp_bucketinfocaller = tmp_caller->bucket;

					info_caller *tmp_infocaller;

					while(1) {
						for (j = 0 ; j < tmp_bucketinfocaller->entries_max ; j++) {
							tmp_infocaller = tmp_bucketinfocaller->info[j];

							if (tmp_infocaller != NULL)
								if (!strcmp(tmp_infocaller->info_number, caller2))
									return 0;
						}

						if (tmp_bucketinfocaller->next == NULL)
							return 1;

						tmp_bucketinfocaller = tmp_bucketinfocaller->next;
					}
				}
			}
		}
		if (tmp_bucketcaller->next == NULL)
				return 1;

		tmp_bucketcaller = tmp_bucketcaller->next;
	}
}

//Print all numbers that contacted both caller1 and caller2
void indist(hash_table * hashtable1, hash_table * hashtable2, char *caller1, char *caller2){
	if (hashtable1 == NULL) {
		printf("No indist found\n");
		return;
	}

	if (!(relation(hashtable2, caller1, caller2) && relation(hashtable2, caller2, caller1))) {
		printf("Error! User %s and user %s contacted each other\n", caller1, caller2);
		return;
	}

	int i, j, k;

	bucket_caller *tmp_bucketcaller;

	caller *tmp_caller;

	bucket_info_caller *tmp_bucketinfocaller;

	info_caller *tmp_infocaller;

	for (i = 0 ; i < hashtable1->size ; i++) {
		tmp_bucketcaller = hashtable1->table[i];

		if (tmp_bucketcaller != NULL) {
			while(1) {
				for (j = 0 ; j < tmp_bucketcaller->entries_max ; j++) {
					tmp_caller = tmp_bucketcaller->caller[j];

					if (tmp_caller != NULL)
						if (!(relation(hashtable2, caller1, tmp_caller->number) && relation(hashtable2, caller2, tmp_caller->number)));
							printf("User %s contacted both %s and %s\n", tmp_caller->number, caller1, caller2);
				}

				if (tmp_bucketcaller->next == NULL)
					break;

				tmp_bucketcaller = tmp_bucketcaller->next;
			}
		}
	}

	for (i = 0 ; i < hashtable2->size ; i++) {
		tmp_bucketcaller = hashtable2->table[i];

		if (tmp_bucketcaller != NULL) {
			while(1) {
				for (j = 0 ; j < tmp_bucketcaller->entries_max ; j++) {
					tmp_caller = tmp_bucketcaller->caller[j];

					if (tmp_caller != NULL)
						if (!(relation(hashtable2, caller1, tmp_caller->number) && relation(hashtable2, caller2, tmp_caller->number)))
							printf("%s\n", tmp_caller->number);
					}

				if (tmp_bucketcaller->next == NULL)
					break;

				tmp_bucketcaller = tmp_bucketcaller->next;
			}
		}
	}
	return;
}

//Free memory of hash table
void bye(hash_table *hashtable) {
	int i, j, k, l;
	int tmp_bucketcaller_entries_max = (hashtable->size_bucket / sizeof(caller*));;
	int tmp_bucketinfocaller_entries_max = (hashtable->size_bucket / sizeof(info_caller*));

	bucket_caller *tmp_bucketcaller;

	caller *tmp_caller;

	bucket_info_caller *tmp_bucketinfocaller;

	bucket_info_caller *cur_bucketinfocaller;

	info_caller *tmp_infocaller;

	for (i = 0 ; i < hashtable->size ; i++) {
		tmp_bucketcaller = hashtable->table[i];

		if (tmp_bucketcaller != NULL) {
			while(1) {
				for (j = 0 ; j < tmp_bucketcaller_entries_max ; j++) {
					tmp_caller = tmp_bucketcaller->caller[j];

					if (tmp_caller != NULL) {
						tmp_bucketinfocaller = tmp_caller->bucket;

						if (tmp_bucketinfocaller != NULL) {
							while(1) {
								for (k = 0 ; k < tmp_bucketinfocaller_entries_max ; k++) {
									tmp_infocaller = tmp_bucketinfocaller->info[k];

									if (tmp_infocaller != NULL) {
										free(tmp_infocaller->cdr_uniq_id);
										free(tmp_infocaller);
									}
								}

									cur_bucketinfocaller = tmp_bucketinfocaller;
									tmp_bucketinfocaller = tmp_bucketinfocaller->next;

									free(cur_bucketinfocaller);

								if (tmp_bucketinfocaller == NULL)
									break;
							}
						}
					}

					free(tmp_bucketcaller->caller[j]);
				}

				tmp_bucketcaller = tmp_bucketcaller->next;

				if (tmp_bucketcaller == NULL)
					break;
			}
		}
	}

	for (i = 0 ; i < hashtable->size ; i++)
		free(hashtable->table[i]);
	free(hashtable);

	hashtable = NULL;
	printf("Succsefully hash table memory release\n");

	return;
}


//Function that checks if date is between the other 2 dates
int date(int day, int day1, int day2, int month, int month1, int month2, int year, int year1, int year2) {
	int date = 10000 * year + 100 * month + day;
	int date1 = 10000 * year1 + 100 * month1 + day1;
	int date2 = 10000 * year2 + 100 * month2 + day2;

	if (date > date1 && date < date2)
		return 1;
	else if (date == date2 || date == date1)
		return 2;

	return 0;
}


//Function that checks if time is between the other 2 times
int time(int hour, int hour1, int hour2, int min, int min1, int min2) {
	int time = 100 * hour + min;
	int time1 = 100 * hour1 + min1;
	int time2 = 100 * hour2 + min2;

	if (time >= time1 && time <= time2)
		return 1;

	return 0;
}
