#ifndef _STRUCTS_
#define _STRUCTS_

//Hash table
typedef struct _hash_table_ {
	int size;
	int size_bucket;
	struct _bucket_caller_ **table;
}hash_table;


//Topdest node
typedef struct _dest_node_ {
	char code[3];
	int count;
	struct _dest_node_ *next;
}dest_node;


//Info Bucket
typedef struct _info_caller_ {
	char *cdr_uniq_id;
	char info_number[15];
	int date_day;
	int date_month;
	int date_year;
	int init_time_hour;
	int init_time_minute;
	int duration;
	int type;
	int tarrif;
	int fault_condition;
}info_caller;


typedef struct _bucket_info_caller_ {
	int entries_max;
	int entries_current;

	struct _bucket_info_caller_ *next;
	info_caller **info;
}bucket_info_caller;


//Number Bucket
typedef struct _caller_ {
	char number[15];
	bucket_info_caller *bucket;
}caller;


typedef struct _bucket_caller_ {
	int entries_max;
	int entries_current;

	struct _bucket_caller_ *next;
	caller **caller;
}bucket_caller;
	
#endif
