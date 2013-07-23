all:
	$(CC) -Wall amot.c -o amot -lavutil -lavformat

clean:
	rm -rf *.dSYM *.a *.o
