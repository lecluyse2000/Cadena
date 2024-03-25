PasswordManager: main.o application.o passwordmanager.o hashtable.o
	g++ -std=c++20 -g -Wall main.o application.o passwordmanager.o hashtable.o -o PasswordManager 

main.o: main.cpp
	g++ -std=c++20 -g -Wall -c main.cpp

application.o: application.h application.cpp
	g++ -std=c++20 -g -Wall -c application.cpp

passwordmanager.o: passwordmanager.h passwordmanager.cpp
	g++ -std=c++20 -g -Wall -c passwordmanager.cpp

hashtable.o: hashtable.h hashtable.cpp 
	g++ -std=c++20 -g -Wall -c hashtable.cpp 
	
clean:
	rm *.o PasswordManager 
