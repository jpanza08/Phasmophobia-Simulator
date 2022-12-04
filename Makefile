final: main.o evidence.o building.o ghost.o hunter.o room.o defs.h
	gcc -pthread -o final main.c evidence.c building.c ghost.c hunter.c room.c defs.h

main.o: main.c defs.h
	gcc -c main.c

building.o: building.c defs.h
	gcc -c building.c

evidence.o: evidence.c defs.h
	gcc -c evidence.c

ghost.o: ghost.c defs.h
	gcc -c ghost.c

hunter.o: hunter.c defs.h 
	gcc -c hunter.c

room.o: room.c defs.h
	gcc -c room.c

clean: 
	rm -f main.o building.o evidence.o ghost.o hunter.o room.o final