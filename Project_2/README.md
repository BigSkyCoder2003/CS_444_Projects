# Project 2: Mutexes 
Daniel Lounsbury
## Building

Command line:

* `make` to build. An executable called `hellothread` will be produced.
* `make clean` to clean up all build products.

## Files

* `reservations.c`: The main project code 


## Data

This project uses integers to store reservation status of virtual seats that are reserved and freed by brokers(threads). 


## Functions

* `reserve_seat()` reserves a seat
* `free_seat()` frees a seat
* `is_free()` checks if a seat is free
* `verify_seat_count()` verifies that the brokers seat count matches the global seat count
* `seat_broker() ` initializes new seat brokers
* `main()` main function for project

