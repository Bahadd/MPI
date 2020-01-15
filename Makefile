proRecovering : proRecovering.o main.o
								gcc -o proRecovering proRecovering.o main.o

proRecovering.o : proRecovering.c
								gcc -o proRecovering.o -c proRecovering.c
