CC = gcc
CFLAGS = -g -c -Wall
LDFLAGS = -lm -lgmp
CSRC = *.c
HSRC = *.h
OBJS = main.o algos.o
EX=crypto

N=6421
K=100


.PHONY:run

interactive: compile
	./$(EX)

run: compile 
	./$(EX) $(N) $(K)

valgrind:compile
	valgrind --leak-check=full --show-leak-kinds=all ./$(EX) $(N) $(K)

compile:$(OBJS)
	$(CC) -g -o $(EX) $^ $(LDFLAGS)

%.o:%.c %.h
	$(CC) $(CFLAGS) $<

%.o:%.c
	$(CC) $(CFLAGS) $<



DOSSIER = DJEBLAHI_Ahmed_EJJED_Zakaria
FILES = Makefile
.PHONY: zip
zip:
	rm -rf $(DOSSIER)
	rm -f $(DOSSIER).zip
	mkdir $(DOSSIER)
	cp *.c *.h $(FILES) $(DOSSIER)
	zip -r $(DOSSIER).zip $(DOSSIER)
	rm -rf $(DOSSIER)
	ls -l

.PHONY:clean

clean:
	rm -r *.o
	rm -r $(EX)
	ls -l
