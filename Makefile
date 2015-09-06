CC = gcc
EXE = bullcow
all:
	@echo "Compiling..."
	@$(CC) bullcow.c playgame.c util.c BCscoring.c -o $(EXE)
	@echo "Compilation Done!"
install:
	@echo "Installing..."
	cp bullcow /usr/share/bin
	@echo "Installation Done!"
clean:
	rm -rf *.o
	rm bullcow
