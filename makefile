CC = clang
CFILES = amot.c posters.c net.c
LIBS = -lavutil -lavformat -lcurl -lsqlite3 -ljsmn
FLAGS = -Wall -std=c99 -g

all:
	$(CC) $(CFILES) -o amot $(LIBS) $(FLAGS)

debug:
	$(CC) $(CFILES) -o amot $(LIBS) $(FLAGS) 

clean:
	rm -rf *.dSYM *.a *.o amot
