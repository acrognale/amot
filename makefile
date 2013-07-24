all:
	$(CC) -Wall amot.c -o amot -lavutil -lavformat -std=c99

clean:
	rm -rf *.dSYM *.a *.o
