main.out:main.c bigint.o
	gcc -o main.exe main.c bigint.o
bigint.o:bigint.c
	gcc -c bigint.c

test:
	./bigint_test.sh
clean:
	rm -f bigint.o main.exe