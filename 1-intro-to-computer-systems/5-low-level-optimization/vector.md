### Vector dot product
Here are my answers and notes regarding the `vec.c` and `dotproduct.c` programs and functions.

**Optimize the performance of this function**
- The first thing I can look for is code that is performed multiple times (e.g. in a loop). These types of optimizations are known as _code motion_.

Here are some optimizations from CS:APP chapter 5:
- 5.4 Eliminate loop inefficiencies.
- 5.5 Reduce procedure calls.
- 5.6 Eliminating unneeded memory references.
- 5.7 Understanding modern processors.
- 5.8 Loop unrolling.
