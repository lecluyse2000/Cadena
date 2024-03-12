PasswordManager: main.o hashtable.o
	g++ -std=c++20 -g -Wall main.o hashtable.o -o PasswordManager -lsodium

main.o: main.cpp
	g++ -std=c++20 -g -Wall -c main.cpp
		
hashtable.o: hashtable.h hashtable.cpp 
	g++ -std=c++20 -g -Wall -c hashtable.cpp 
	
clean:
	rm *.o PasswordManager 
