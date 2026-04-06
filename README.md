gcc -Wall -ggdb main.c src/stream.c src/converter.c src/parser.c -o main
gdb --args main input.txt