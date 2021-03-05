# Simple debugs for 42 students
This repo contains some simple but very helpful tools for debugging your code.
## Current debug functions
1. debug_str
2. debug_nbr
3. check_leaks
## How to use:
1. Run `make` to create a library of the debug functions
2. Now you can add the function prototypes to your functions
3. Check the test.c file for an easy example for a test main.c
4. Copy debug.a into your project folder to use it freely
5. Compile your test and run: gcc test.c debug.a && ./a.out
## Some helpful links to practice the fine art of RTFM
1. Ever wondered what the difference is between SEGFAULT and BUS error?
[SEGFAULT VS BUS](https://www.geeksforgeeks.org/segmentation-fault-sigsegv-vs-bus-error-sigbus/)
2. A descriptive wiki about memory management
[Memory Management](https://wiki.sei.cmu.edu/confluence/pages/viewpage.action?pageId=87152142)
### Halp I still don't know how to debug my code!
`man RTFM`
