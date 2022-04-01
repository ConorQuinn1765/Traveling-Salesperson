CC = g++
CFLAGS = -Wall
SFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = main.o tsp.o point.o
EXE = run

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(SFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(SFLAGS) -c main.cpp
tsp.o: tsp.cpp tsp.h
	$(CC) $(CFLAGS) -c tsp.cpp
point.o: point.cpp point.h
	$(CC) $(CFLAGS) $(SFLAGS) -c point.cpp
clean:
	rm $(OBJS) $(EXE)