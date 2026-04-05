gcc -Wall -ggdb main.c src/stream.c src/converter.c -o main
gdb --args main input.txt