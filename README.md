# SystemsProject

Tokenizer For Systems Programming
by Saif and Cal

This is a tokenizer written in C that can discern between words, hexadecimal, octal, floating point, and various things like brackets and other symbols. This is the first Systems Programming assignment in the class.

Steps to get it to run

Compile the source file and give the executable a name

Run the program from the command line with a command such as
./tokenizer "0x4356abdc 0777 [] "

or 

tokenizer.exe "0x4356abdc 0777 [] "

Please be sure to wrap the argument in using quotes "" otherwise the program will fail to run correctly.
Certain characters such as \ (backslash) will cause the program to fail. Backslashs are an escape character in C and in certain
shell environments, please avoid using it in your inputs.

Emojis, and characters that do not appear on a normal keyboard are not supported.


