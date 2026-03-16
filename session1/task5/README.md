# Task 5: Profiling

The `task5` directory contains a slightly different version of the matrix
multiplication example from Task 1.

1. Compile the application by entering `make`. Look at the compiler commands
   echoed in the terminal. Notice how `-pg` is used when compiling the
   source files to object code _and_ when linking them into an executable.

2. Run the program:

       ./multiply

   After a short delay, the program should terminate. There should now be
   a file named `gmon.out` in this directory.

3. Run Gprof like so:

       gprof multiply gmon.out

   Examine the report that is displayed in the terminal.
