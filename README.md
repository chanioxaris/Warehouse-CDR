## Overview

A warehouse that stores [Call Detail Records](https://en.wikipedia.org/wiki/Call_detail_record) using hashtables, a heap and two layers of buckets.
<br />

Each CDR record contains the following fields separated by ";" delimiter:
- **cdr-uniq-id**: Identifier number of specific call.
- **originator-number**: Calling number (first 3 digits for country code followed by a 10 digits number e.g 357-2127272314).
- **destination-number**: Called number (first 3 digits for country code followed by a 10 digits number e.g 357-2127272314).
- **date**: Date of call (DDMMYYYY where DD is the day, MM is the month and YYYY is the year).
- **init-time**: Start time of call (HH:MM where HH is the hour and MM is the minute, in 24-hour time system).
- **duration**: Duration of call in minutes.
- **type**: Type of call (SMS, voice, data, etc).
- **tarrif**: Invoice of specific call.
- **fault-condition**: Identifier number of problem that might occured.



## Structure composition

### Hashtables

Two hash tables are used from the program, where in the first caller number (originator-number) is used as a key and in the second one callee number (destination-number) is used as a key. For each hash table two bucket layers are used. The first layer (blue and ligth blue buckets) includes the caller or callee number after hashing function and the second layer (pink and light pink buckets) contains the CDR record. Each distinct number on the warehouse owns it's own second layer structure. If a bucket become full, another one is dynamically created using the implementation of [linked lists](https://en.wikipedia.org/wiki/Linked_list).

The below image describes the hash tables structure.


![Hashtables](https://github.com/chanioxaris/Warehouse-CDR/blob/master/img/structure.png)

### Heap

A binary max heap is used from the program which each node, one for each number included in warehouse, contains the total spend money of the customer. 

The below image describes the heap structure.

![Heap](https://github.com/chanioxaris/Warehouse-CDR/blob/master/img/heap.png)

## Interface description

A user can perform the following operations:
- #### insert [CDR record]
Insert a CDR record into the warehouse.
- #### delete [caller number] [CDR ID]
Delete the record with CDR ID made from caller number.
- #### find [caller number] [time1][year1] [time2][year2]
Find all records from caller number made between this specific time and year.
- #### lookup [callee number] [time1][year1] [time2][year2]
Find all records to callee number made between this specific time and year.
- #### indist1 [caller number 1] [caller number 2]
Find all customers that call both caller number 1 and caller number 2.
- #### topdest [caller number]
Find the top country code, called from caller number.
- #### top [k]
Print all callers number that created the top-k% of company's total income.
- #### print hashtable[X]
Print the content of hashtableX (e.g print hashtable1, print hashtable2).
- #### bye
Destroy everything and free the memory of structures.


## Compile

`./makefile`

## Usage

`./werhauz -o [operations file] -h1 [caller hashtable entries] -h2 [callee hashtable entries] -s [bucket size (bytes)] -c [config file]`
