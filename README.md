# Still under progress
# ds-and-algos
Lightweight, efficient and generalized C++ header-only template library for data structures and algorithms .

This library is dedicated towards data structures and algorithms that are useful in competitive programming . 

## Table of Contents 
- [Usage](#usage)
- [Library](#library)
  - [Number Theory](#number-theory)
  - [Data Structures](#data-structures)
  - [Tree](#tree)
  - [Algos](#algos)
- [License](#license)

### Usage
- Clone the repository (and star it if you like it)
- include header files of the data structures and algorithms you need to use in your code using `#include "path/to/required/header/files"`
- path of header file in _include "header_file"_ should be relative to _path/to/cloned/ds-and-algos/repo/include
- Include `-Ipath/to/cloned/ds-and-algos/repo/include` flag while compiling files, for instance, `g++ hello-world.cpp -Ipath/to/cloned/ds-and-algos/repo/include`
- That's it .
### Library

#### Number Theory
| name                                                                                        | examples                                                                      | good resources to study                                                                                                                                                  |
|---------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [Sieve](include/dragon/number-theory/sieve.hpp)                                             | [example-1](examples/number-theory/sieve/example-1.cpp)                       | [cp-algorithms](https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html) [brilliant](https://brilliant.org/wiki/sieve-of-eratosthenes/)                             |
| [Mod inverse](include/dragon/number-theory/mod-inverse.hpp)                                 | [example-1](examples/number-theory/mod-inverse/example-1.cpp)                 | [cp-algorithms](https://cp-algorithms.com/algebra/module-inverse.html) [gfg](https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/)                       |
| [Extended euclid gcd](include/dragon/number-theory/extended-euclid-gcd.hpp)                 | [example-1](examples/number-theory/extended-euclid-gcd/example-1.cpp)         | [cp-algorithms](https://cp-algorithms.com/algebra/extended-euclid-algorithm.html) [brilliant](https://brilliant.org/wiki/extended-euclidean-algorithm/)                  |
| [Chinese remainder theorem](include/dragon/number-theory/chinese-remainder-theorem.hpp)     | [example-1](examples/number-theory/chinese-remainder-theorem/example-1.cpp)   | [brilliant](https://brilliant.org/wiki/chinese-remainder-theorem/) [AOPS](https://artofproblemsolving.com/wiki/index.php/Chinese_Remainder_Theorem)                      |
| [Euler totient](include/dragon/number-theory/euler-totient.hpp)                             | [example-1](examples/number-theory/euler-totient/example-1.cpp)               | [cp-algorithms](https://cp-algorithms.com/algebra/phi-function.html) [brilliant](https://brilliant.org/wiki/eulers-totient-function/)                                    |
| [Linear diophantine equation](include/dragon/number-theory/linear-diophantine-equation.hpp) | [example-1](examples/number-theory/linear-diophantine-equation/example-1.cpp) | [cp-algorithms](https://cp-algorithms.com/algebra/linear-diophantine-equation.html) [brilliant](https://brilliant.org/wiki/linear-diophantine-equations-one-equation/)   |
| [Binary exponentiation](include/dragon/number-theory/binary-exponentiation.hpp)             | [example-1](examples/number-theory/binary-exponentiation/example-1.cpp)       | [cp-algorithms](https://cp-algorithms.com/algebra/binary-exp.html) [random-site-1](https://eli.thegreenplace.net/2009/03/21/efficient-integer-exponentiation-algorithms) |

#### Data Structures
| name                                                                     | examples                                                                                                                      | good resources to study                                                                                                                                                                                                                                                                                                                                                  |
|--------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [Sparse table idempotent](include/dragon/ds/sparse-table-idempotent.hpp) | [example-1](examples/ds/sparse-table-idempotent/example-1.cpp) [example-2](examples/ds/sparse-table-idempotent/example-2.cpp) |                                                                                                                                                                                                                                                                                                                                                                          |
| [Segment tree](include/dragon/ds/segment-tree.hpp)                       | [example-1](examples/ds/segment-tree/example-1.cpp) [example-2](examples/ds/segment-tree/example-2.cpp)                       | [cp-algorithms](https://cp-algorithms.com/data_structures/segment_tree.html) [hackerearth](https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/tutorial/) [cf-blog-1](https://codeforces.com/blog/entry/18051) [cf-blog-2](https://codeforces.com/blog/entry/22616) [practice-problems](https://codeforces.com/blog/entry/22616) |
| [Sparse table](include/dragon/ds/sparse-table.hpp)                       | [example-1](examples/ds/sparse-table/example-1.cpp) [example-2](examples/ds/sparse-table/example-2.cpp)                       | [cp-algorithms](https://cp-algorithms.com/data_structures/sparse-table.html) [gfg](https://www.geeksforgeeks.org/sparse-table/) [practice-problems](https://codeforces.com/blog/entry/23005)                                                                                                                                                                             |
| [Sqrt decomposition](include/dragon/ds/sqrt-decomposition.hpp)           | [example-1](examples/ds/sqrt-decomposition/example-1.cpp)                                                                     | [cp-algorithms](https://cp-algorithms.com/data_structures/sqrt_decomposition.html) [practice-problems](https://codeforces.com/blog/entry/23005)                                                                                                                                                                                                                          |

#### Tree
| name                                                                     | examples                                                                                    | good resources to study                                                                                                   |
|--------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| [Euler tour](include/dragon/tree/euler-tour.hpp)                         | [example-1](examples/tree/euler-tour/example-1.cpp)                                         | [gfg](https://www.geeksforgeeks.org/euler-tour-tree/) [cf-blog](https://codeforces.com/blog/entry/63020)                  |
| [Tree](include/dragon/tree/tree.hpp)                                     | [example-1](examples/tree/tree/example-1.cpp) [example-2](examples/tree/tree/example-2.cpp) | [gfg](https://www.geeksforgeeks.org/generic-treesn-array-trees/)                                                          |
| [Lowest common ancestor](include/dragon/tree/lowest-common-ancestor.hpp) | [example-1](examples/tree/lowest-common-ancestor/example-1.cpp)                             | [gfg](https://www.geeksforgeeks.org/lca-n-ary-tree-constant-query-o1/) [cf-blog](https://codeforces.com/blog/entry/53738) |

#### Algos
| name                                                                                      | examples                                                                                                                                          | good resources to study                                                                                                                                                                  |
|-------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [Longest increasing subsequence](include/dragon/algos/longest-increasing-subsequence.hpp) | [example-1](examples/algos/longest-increasing-subsequence/example-1.cpp) [example-2](examples/algos/longest-increasing-subsequence/example-2.cpp) | [gfg](https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/) [cp-algorithms](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html) |




### License
This project is licensed under the MIT License. See the license [here](LICENSE)
