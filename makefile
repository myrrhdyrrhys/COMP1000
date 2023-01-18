CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = program.o
EXEC = program

ifdef INDEX
CFLAGS += -D INDEX
INDEX : clean $(EXEC)
endif

$(EXEC) : $(OBJ) colors.o compare.o replace.o
	$(CC) $(OBJ) colors.o compare.o replace.o -o $(EXEC)

program.o : program.c colors.h compare.h replace.h macros.h
	$(CC) $(CFLAGS) program.c -c

colors.o : colors.c colors.h compare.h macros.h
	$(CC) $(CFLAGS) colors.c -c

compare.o : compare.c compare.h replace.h macros.h 
	$(CC) $(CFLAGS) compare.c -c

replace.o : replace.c replace.h
	$(CC) $(CFLAGS) replace.c -c

clean :
	rm -rf $(EXEC) $(OBJ) colors.o compare.o replace.o
