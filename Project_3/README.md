# Project 3: Producers and Consumers 
Daniel Lounsbury
## Building

Command line:

* `make` to build. An file called `pc` will be produced.
* `make clean` to clean up all build products.

## Files

* `pc.c`: The main project code 
* `eventbuf.c`: allows for the setup of an event buffer that holds events, and contains functions for the manipulation of the event buffer
* `eventbuf.h`function prototypes for eventbuffer.h

## Data

This project uses a linked list to store integers in an "event_buffer", and the rest of the project makes use of integers for storing various pieces of relevant/required data.


## Functions

* `main()` main function for the project; parses the command line, sets up the producers and consumers, semaphores, and breaks everything back down at the end 
* `sem_open_temp()` opens and closes semaphores
* `producer()` adds events to the event buffer according to the number of events per producer specified
* `consumer()` consumes events from the event buffer
* `eventbuf_free`frees the event buffer structure from memory
* `eventbuf_add` adds an event to the event buffer
* `eventbuf_get` removes an event from the event buffer
* `eventbuf_empty` returns whether or not the event buffer is empty

