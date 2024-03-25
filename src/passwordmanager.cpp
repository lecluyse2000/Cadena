#include <iostream>
#include <limits>
#include <string>
#include "passwordmanager.h"
#include "hashtable.h"

void clearInputStream()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void receiveUserInput()
{
   std::string returnString;
   while(!(std::cin >> returnString)) {
      clearInputStream();
      std::cerr << "Failed to recieve user input, try again! ";
   }
   clearInputStream();
   
   return returnString;
}

login getLogin(const HashTable& manager)
{
   std::string website = "";
   std::cout << "What is the website of the login you want to get? ";
   while(!(std::cin >> website)) {
      clearInputStream();
      std::cerr << "Failed to recieve user input, try again! ";
   }
   clearInputStream();
   return manager.searchTable(website);
}

void printLogin(const login& entry)
{
   if(entry.website == "NULL") {
      std::cout << "The login for the given website could not be found!\n\n";
   } else {
      std::cout << "Website: " << entry.website << "\nUsername:  " << entry.username 
                << "\nPassword: " << entry.password << '\n' << std::endl;
   }
}

void addLogin()
{
   std::cout << "What is the name of the website you want to add? ";
   const std::string website = receiveUserInput();

   std::cout << "\nWhat is the username you would like to add? ";
   const std::string username = receiveUserInput();

   std::cout << "What is the password you would like to add? ";
   const std::string password = receiveUserInput();

   manager.insertNode(website, username, password);
}
