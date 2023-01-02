
CC = gcc -g -fsanitize=address
C_Files = main.c start.c functions.c exit.c

program: $(C_Files)
	$(CC) $(C_Files) -o program 

