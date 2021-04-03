wcat: wcat.c
	gcc -o -g -std=c99 -Wvla -Wall -fsanitize=address,undefined -o wcat wcat.c

wcat2: wcat.c
	gcc -o wcat wcat.c

valgrind:
	valgrind --track-fds=yes ./wcat 80 file1


test: ww file1 file2 file3
	cat file1 file2 file3 | ./ww 80


final: wcat ww file1 file2 file3
	./wcat 80 file1 file2 file3 file2 file6 file6 file6 file6 file1

run: wcat ww file1 file2
	./wcat 80 file1 file2

test1: wcat dir
	./wcat 20 dir file1 file2

test2: wcat 
	./wcat 20 file7 file1 file2

empty: wcat ww file4 file5 file6
	./wcat 80 file4 file5 file6 file4 file5 file6

clean: 
	rm wcat