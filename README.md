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

Exc 2.
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
