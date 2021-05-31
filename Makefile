# compilateur
CC=gcc

# chemin du main
DIRECTORY=src


$(DIRECTORY)/main.o : $(DIRECTORY)/main.c
	cd $(DIRECTORY) && $(CC) main.c -o main && ./main


clean :
	cd $(DIRECTORY) && rm -f main *.o *.out

run :
		cd $(DIRECTORY) && ./main
