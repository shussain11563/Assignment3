wcat: wcat.c
	gcc -o wcat wcat.c

test: ww file1 file2 file3
	cat file1 file2 file3 | ./ww 80

run: wcat ww file1 file2 file3
	./wcat 80 file1 file2

test1: wcat dir
	./wcat 20 dir file1 file2