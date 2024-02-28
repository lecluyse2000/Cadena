PasswordManager: main.o hashtable.o
	g++ -g -Wall main.o hashtable.o -o PasswordManager -lsodium

main.o: main.cpp
	g++ -g -Wall -c main.cpp
		
hashtable.o: hashtable.h hashtable.cpp 
	g++ -g -Wall -c hashtable.cpp 
	
clean:
	rm *.o PasswordManager 
