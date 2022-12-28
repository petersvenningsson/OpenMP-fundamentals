This repo contains solutions to Tim Mattson's workshop on OpenMP.

To build and run the exercises run

```
./docker-cmake-build.sh
``` 

# Introduction
Tim Mattson hosted a a great workshop on OpenMP at ATPESC 2019 - [link to video of workshop](https://www.youtube.com/watch?v=I2EaVMjZRRY).
The workshop covers the the fundamentals of OpenMP in a hands on learning experience.

# Exc. 1
Basic example of pragmas. Results show reduction of performance when
parallelizing trivial task.

```
Single-threaded runtime ...
Benchmark 1: ./hello
  Time (mean ± σ):       0.3 ms ±   0.4 ms    [User: 0.4 ms, System: 0.1 ms]
  Range (min … max):     0.1 ms …   7.9 ms    1679 runs
 
Multi-threaded runtime ...
Benchmark 1: ./hello
  Time (mean ± σ):       6.6 ms ±   8.7 ms    [User: 17.5 ms, System: 0.3 ms]
  Range (min … max):     0.5 ms …  27.8 ms    127 runs
```

# Exc 2.
Exercise consists of numerically calculating an intergral. Solution consists of
cyclic allocation of tasks to threads to calculate partial sums. The partial
sum is reduced to a the full integral in a critical section.

This type of naivly parallelizable problem can also be the parallelized by the
one line pragma `#pragma omp parallel for reduction (+:sum)`.

```
Single-threaded runtime ...
Benchmark 1: ./pi
  Time (mean ± σ):      1.303 s ±  0.007 s    [User: 1.302 s, System: 0.001 s]
  Range (min … max):    1.299 s …  1.318 s    10 runs
 
Multi-threaded runtime ...
Benchmark 1: ./pi
  Time (mean ± σ):     920.0 ms ± 292.4 ms    [User: 3639.9 ms, System: 2.1 ms]
  Range (min … max):   453.3 ms … 1172.5 ms    10 runs
```

# Exc 3. 
Memory model for OpenMP. The exercise involves finding bugs in a program which
uses OpenMP. The bugs are mainly related to private/shared variables.

openMp supports a shared memory model. All threads share and address space.
Each thread has its own cache. A common source for decreased performance is
that two threads frequently access and change memory on the same cache line.
The cache line then frequenctly have to be reloaded from the shared memory.

## Memory model of OpenMP - relaxed-consistancy
Views of variables (value in cache, buffer, registry, DRAM) may have different
values. The temoporary views are made consistent at certan points in the
program. The views are made consitant by flush operations (DRAM is read).

Flush can be called by `pragma omp flush(x)`. OpenMP applies flushes when
needed, entry/exit of parallel/critical/barrier regions. Good advice is to never
call omp flush(x).

```
Single-threaded runtime ...
Benchmark 1: ./mandel
  Time (mean ± σ):      1.909 s ±  0.005 s    [User: 1.908 s, System: 0.001 s]
  Range (min … max):    1.903 s …  1.919 s    10 runs
 
Multi-threaded runtime ...
Benchmark 1: ./mandel
  Time (mean ± σ):     893.7 ms ±  31.0 ms    [User: 2201.9 ms, System: 3.1 ms]
  Range (min … max):   875.7 ms … 974.8 ms    10 runs

```

# Exc 4.

## Irregular parallelism
Regular parallelism
- Spacially regular datastructures, e.g. array
- Regular in time - Compute needed for the blocks is similar

Irregular parallelism
- Number of time for task is unpredicably
- Datastucture may be linked list with elements all over the memory space

One example of a irregular problem is traversing a linked list and performing
operations on each element.

This type of problem is explored in Exc 4 which comprise calculating the
a fibonacci sequence for every element in a linked list. The problem was solved
by cyclic assignment of the nodes. A easier way to perform this type of problem
is using the task construct.

```
Single-threaded runtime ...
Benchmark 1: ./linked
  Time (mean ± σ):      8.524 s ±  0.024 s    [User: 8.523 s, System: 0.000 s]
  Range (min … max):    8.505 s …  8.583 s    10 runs
 
Multi-threaded runtime ...
Benchmark 1: ./linked
  Time (mean ± σ):      4.798 s ±  0.131 s    [User: 11.385 s, System: 0.002 s]
  Range (min … max):    4.590 s …  5.000 s    10 runs
```
