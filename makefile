CC=gcc
route=

all: go_thread_handler.o thread_handler.o  word_search_creator.o util.o
	@$(CC) go_thread_handler.o thread_handler.o word_search_creator.o util.o -o laboratorio2 -Wall -lpthread -lm -I.
	@rm go_thread_handler.o thread_handler.o word_search_creator.o util.o
	@echo "Compilación terminada"

go_thread_handler.o: $(route)go_thread_handler.c
	@$(CC) -c $(route)go_thread_handler.c

thread_handler.o: $(route)thread_handler.c
	@$(CC) -c $(route)thread_handler.c

word_search_creator.o: $(route)word_search_creator.c
	@$(CC) -c $(route)word_search_creator.c

util.o:	$(route)util.c
	@$(CC) -c $(route)util.c