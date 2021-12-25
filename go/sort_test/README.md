This directory is fork of https://github.com/golang/go/tree/master/src/sort.

Go `Sort` implementation uses ShellSort for slices <= 12.
I changed this threshold and gaps for ShellSort and run `BenchmarkSortInt64K`, which benchmark sorts Int slices of 64000 length.

Please note that `gaps=1` is equal to InsertionSort.

|  Threshold to use ShellSort  | Gaps | Result(ns/op)   | note |
| ---- | ---- | ---- | ---- |
|  0  | - | 9090035   | Not use ShellSort |
|  6  | 1 |   8730842 |  |
|  12 | 6,1 |  8419891  | Currently `Sort` use this |
|  12 |1  |  8472024  |  |
|  18 | 6,1|  8394926  |  |
|  18  |1 |  8547184  |   |
|  24  |9,6,1 | 8668785  | |
|  24  | 6,1| 8426417  |  |
|  24  |1 | 8663981  |   |
|  48  |9,6,1 | 8684211  | |
|  48  |6,1 | 9130984   | |
|  48  |1 | 10201709   |  |
|  96  |9,6,1 | 8880709 | |
|  96  |6,1 | 9127415 | |
|  96  | 1| 14034377   | |
|  192  |9,6,1| 10204530  | |
|  192  |6,1|  10211346 | |
|  192  |1|  22057045   | |
