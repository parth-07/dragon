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
| name                                                                                        | examples                                                                      |
|---------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| [Sieve](include/dragon/number-theory/sieve.hpp)                                             | [example-1](examples/number-theory/sieve/example-1.cpp)                       |
| [Mod inverse](include/dragon/number-theory/mod-inverse.hpp)                                 | [example-1](examples/number-theory/mod-inverse/example-1.cpp)                 |
| [Extended euclid gcd](include/dragon/number-theory/extended-euclid-gcd.hpp)                 | [example-1](examples/number-theory/extended-euclid-gcd/example-1.cpp)         |
| [Chinese remainder theorem](include/dragon/number-theory/chinese-remainder-theorem.hpp)     | [example-1](examples/number-theory/chinese-remainder-theorem/example-1.cpp)   |
| [Euler totient](include/dragon/number-theory/euler-totient.hpp)                             | [example-1](examples/number-theory/euler-totient/example-1.cpp)               |
| [Linear diophantine equation](include/dragon/number-theory/linear-diophantine-equation.hpp) | [example-1](examples/number-theory/linear-diophantine-equation/example-1.cpp) |
| [Binary exponentiation](include/dragon/number-theory/binary-exponentiation.hpp)             | [example-1](examples/number-theory/binary-exponentiation/example-1.cpp)       |

#### Data Structures
| name                                                                     | examples                                                                                                                      |
|--------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------|
| [Sparse table idempotent](include/dragon/ds/sparse-table-idempotent.hpp) | [example-1](examples/ds/sparse-table-idempotent/example-1.cpp) [example-2](examples/ds/sparse-table-idempotent/example-2.cpp) |
| [Segment tree](include/dragon/ds/segment-tree.hpp)                       | [example-1](examples/ds/segment-tree/example-1.cpp) [example-2](examples/ds/segment-tree/example-2.cpp)                       |
| [Sparse table](include/dragon/ds/sparse-table.hpp)                       | [example-1](examples/ds/sparse-table/example-1.cpp) [example-2](examples/ds/sparse-table/example-2.cpp)                       |
| [Sqrt decomposition](include/dragon/ds/sqrt-decomposition.hpp)           | [example-1](examples/ds/sqrt-decomposition/example-1.cpp)                                                                     |

#### Tree
| name                                                                     | examples                                                                                    |
|--------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|
| [Euler tour](include/dragon/tree/euler-tour.hpp)                         | [example-1](examples/tree/euler-tour/example-1.cpp)                                         |
| [Tree](include/dragon/tree/tree.hpp)                                     | [example-1](examples/tree/tree/example-1.cpp) [example-2](examples/tree/tree/example-2.cpp) |
| [Lowest common ancestor](include/dragon/tree/lowest-common-ancestor.hpp) | [example-1](examples/tree/lowest-common-ancestor/example-1.cpp)                             |

#### Algos
| name                                                                                      | examples                                                                                                                                          |
|-------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------|
| [Longest increasing subsequence](include/dragon/algos/longest-increasing-subsequence.hpp) | [example-1](examples/algos/longest-increasing-subsequence/example-1.cpp) [example-2](examples/algos/longest-increasing-subsequence/example-2.cpp) |





### License
This project is licensed under the MIT License. See the license [here](LICENSE)
