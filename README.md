# Sorting Visualizer
## About
This is a C++ sorting visualizer application, capable of using selection sort, bubble sort, merge sort, and quick sort algorithms.
![example 1](https://github.com/JaydenNikifork/SortingVisualizer/blob/master/Screenshot1.png?raw=true)
## How to Run
Download the repository, run the following command to compile `g++ main.cpp -I ./SDL2/include -L ./SDL2/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o main`, and run `./main` to run the application. Adding an argument to the run command will specify which sorting algorithm to use (`selection`, `bubble`, `merge`, `quick`). Selection sort will run when no argument is supplied.