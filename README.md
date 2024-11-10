# Scheduling Simulation in C

This project simulates CPU scheduling algorithms, including:

1. First Come First Serve (FCFS) - Provided as a base implementation.
2. Priority Scheduling  - Sorts processes by priority, then applies FCFS.
3. Shortest Job First (SJF) - Executes processes in order of shortest burst time.
4. Round Robin (RR) - Uses time slices (quantum) for each process in a cyclic order.

## Files

- `schedsim.c` - Main simulation code with scheduling algorithms.
- `process.h` - Structure definition for process attributes.
- `Makefile` - Compilation instructions.
- `schedsim_ref` - Reference executable for output comparison.

## Compilation & Execution

1. Compile the Code: Run `make` to compile or use:
   ```bash
   gcc -std=c99 schedsim.c -o schedsim
