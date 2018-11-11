
#!/bin/bash

## Compile our two program files

g++ -std=c++14 -c yinsh.cpp
g++ -std=c++14 -o main main.cpp yinsh.o
