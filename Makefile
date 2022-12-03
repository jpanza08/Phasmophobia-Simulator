final: main.o room.o ghost.o hunter.o building.o evidence.o defs.h
	gcc -g main.o room.o ghost.o hunter.o building.o evidence.o defs.h -o final
ghost: main.o room.o ghost.o building.o evidence.o
	gcc -g main.o room.o ghost.o building.o evidence.o defs.h -o final