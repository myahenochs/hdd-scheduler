# hdd-scheduler

Myah Enochs
CSCI 380: Operating Systems
Extra credit disk-scheduling assignment
Due May 10, 2021

Book: OPERATING SYSTEM CONCEPTS by ABRAHAM SILBERSCHATZ, PETER BAER GALVIN, & GREG GAGNE
Programming Problems 11.27:
      Write a program that implements the following disk-scheduling algorithms:
      a. FCFS
      b. SCAN
      c. C-SCAN
      Your program will service a disk with 5,000 cylinders numbered 0 to
      4,999. The program will generate a random series of 1,000 cylinder
      requests and service them according to each of the algorithms listed
      above. The program will be passed the initial position of the disk head
      (as a parameter on the command line) and report the total amount of
      head movement required by each algorithm.

The requirements of this assignment were altered by my professor.
Instead of randomly generating requests, we were to take them from a file.

There are many things I added that were way outside of the scope of this assignment. I had extra time to get this done and wanted the practice.

Usage: sched <starting position> <file containing requests> <flags>

-Starting position must be 0-4999
-File contents must be separated by end-lines with no whitespace after the final entry.

FLAGS:
        -u: Print usage. This may either be included in flags or used alone.
        -p <algorithm(s)>: Prints the address order of the specified algorithm. Recommended to pipe to a file if there are many requests.
                f: FCFS
                s: SCAN
                c: CSCAN

Example: bonus 100 input -pu fc


I've also included a small random number generator so I can get a long list of random numbers for the HDD scheduler. This is purely supplemental.

Usage: rand <count> <lower bound> <upper bound>
Bounds are optional, but recommended.
Redirect it into a file for use with the scheduler.

Note: The random number generator has basically no error and edge-case checking :)

To build:

    cd hdd-scheduler
    make

To build random number generator (optional):

    make random
