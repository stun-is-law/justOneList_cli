all: justOne.exe

justOne.exe: justOne.o
	 gcc -o justOne.exe justOne.o

justOne.o: justOne.c
	 gcc -c justOne.c
     
clean:
	 rm justOne.o justOne.exe