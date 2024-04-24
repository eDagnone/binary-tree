# README.MD

```bash
gcc -o main main.c layout.c
./main
```

Compiled on Linux Mint with GCC 11.4.0.
Formatted using clang-format, with the colunm limit disabled. No memory leaks in Valgrind.
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./main
```