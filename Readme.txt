#compile command
clang++ -Wall -O0 -ggdb -g3 -std=c++17 -g -o gauss gauss.cpp
# pre-requisites for plotting : install python3, install plotly via pip
# plotting
./gauss | ./plot_xy.py
[optional]
#source code formatting command
clang-format -style=LLVM -i gauss.cpp

