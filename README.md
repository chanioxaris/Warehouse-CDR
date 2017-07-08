## Overview

A warehouse that stores [Call Detail Records](https://en.wikipedia.org/wiki/Call_detail_record) using hashtables, a heap and two layers of buckets
<br />

Each CDR record contains the following fields separated by ";" delimiter:
- **cdr-uniq-id**: Identifier of specific call.
- **originator-number**: The number that is making the call.
- **destination-number**: The number that is being called.
- **date**: Date of call (DDMMYYYY where DD is the day, MM is the month and YYYY is the year).
- **init-time**: Start time of call (HH:MM where HH is the hour and MM is the minute, in 24-hour time system).
- **duration**: Duration of call in minutes.
- **type**: Type of call (SMS, voice, data, etc.).
- **tarrif**: Invoice of specific call.
- **fault-condition**: Identifier of problem that might occured.



## Structure composition

### Hashtables


### Heap




## Compile

`./makefile`

## Usage

`./werhauz -o [operations file] -h1 [caller hashtable entries] -h2 [callee hashtable entries] -s [bucket size (bytes)] -c [config file]`
