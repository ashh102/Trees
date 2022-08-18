CC = cc

P0:	main.o tree.o helper_funcs.o
	gcc -o P0 main.o tree.o helper_funcs.o

main.o:	main.c
	gcc -c main.c

tree.o: tree.c
	gcc -c tree.c
	
helper_funcs.o: helper_funcs.c
	gcc -c helper_funcs.c
	
clean:
	rm *.o
