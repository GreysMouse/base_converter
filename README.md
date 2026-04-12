About: 

A program for converting a string representation of a number in a specified positional notation to a string representation of a number in another specified one. Length of input number in unlimited. The base of the number system is limited to the range from 2 to 62.

Usage:

    <program name> <input file> [<output file>]

If \<output file> not specified, the result will be written to the standard output stream.

Input file should contain valid text of the following format:

    <numeric chars> <source base> <target base>

where \<numeric chars> are consecutive characters representing the digits of a given number in accordance with the specified base:
- [0-9] - digits from 0 to 9;
- [a-z] - digits from 10 to 35;
- [A-Z] - digits from 36 to 61.

Source base and target base should be specified as decimals with a value between 2 and 62.

By default the program compiled with macro symbol

    SKIP_LEADING_ZEROS=1
    
which forces the program to skip insignificant leading zeros of result that can arise during convertation. To override this behavior use

    make CPPFLAGS=

for compilation.