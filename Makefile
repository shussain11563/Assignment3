wcat: wcat.c
	gcc -o wcat wcat.c

test: ww file1 file2 file3
	cat file1 file2 file3 | ./ww 80

run: wcat ww file1 file2
	./wcat 80 file1 file2

test1: wcat dir
	./wcat 20 dir file1 file2

test2: wcat 
	./wcat 20 file4

empty: wcat ww file4 file5 file6
	./wcat 80 file4 file5 file6 file4 file5 file6

clean: 
	rm  wcat