# Clique cover

This is greedy clique cover algorithm.

- ```$ ./clique_cover [-r rep] [-s seed] [-o file.out] file.col```
    - __file.col__ - Input col file ([DIMACS graph format](http://lcs.ios.ac.cn/~caisw/Resource/about_DIMACS_graph_format.txt))  
    Edge number must be more than or equal to 1.
    - __rep__ - Repetition
    - __file.out__ - Output clique cover file
    - __seed_ - Seed value

- col file example
    ```:example.col
    c This is comment line

    p edge 6 10
    e 1 2
    e 1 3
    e 1 5
    e 2 4
    e 2 5
    e 2 6
    e 3 5
    e 3 6
    e 4 5
    e 5 6
    ```