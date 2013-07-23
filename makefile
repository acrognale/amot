all:
	$(CC) -Wall amot.c -o amot

clean:
	rm -rf *.dSYM *.a *.o
