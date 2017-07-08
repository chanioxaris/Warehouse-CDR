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


### Heap


## Interface description

A user can perform the following operations:
- #### insert [CDR record]
Identifier of specific call.
- #### delete [caller number] [cdr ID]
The number that is making the call.
- #### find [caller number] [time1][year1] [time2][year2]
The number that is being called.
- #### lookup [callee number] [time1][year1] [time2][year2]
Date of call (DDMMYYYY where DD is the day, MM is the month and YYYY is the year).
- #### indist1 [caller number 1] [caller number 2]
Start time of call (HH:MM where HH is the hour and MM is the minute, in 24-hour time system).
- #### topdest [caller number]
Duration of call in minutes.
- #### top [percentage]
Type of call (SMS, voice, data, etc.).
- #### print hashtable[X]
Invoice of specific call.
- #### bye
Identifier of problem that might occured.


## Compile

`./makefile`

## Usage

`./werhauz -o [operations file] -h1 [caller hashtable entries] -h2 [callee hashtable entries] -s [bucket size (bytes)] -c [config file]`
