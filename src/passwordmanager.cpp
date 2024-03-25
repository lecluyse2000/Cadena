#include <iostream>
#include <limits>
#include <string>
#include "passwordmanager.h"
#include "hashtable.h"

void PasswordManager::clearInputStream() const
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PasswordManager::receiveUserInput() const
{
   std::string returnString;
   while(!(std::cin >> returnString)) {
      clearInputStream();
      std::cerr << "Failed to recieve user input, try again! ";
   }
   clearInputStream();
   
   return returnString;
}

login PasswordManager::getLogin() const
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

void PasswordManager::printLogin(const login& entry) const
{
   if(entry.website == "NULL") {
      std::cerr << "The login for the given website could not be found!\n\n";
   } else {
      std::cout << "Website: " << entry.website << "\nUsername:  " << entry.username 
                << "\nPassword: " << entry.password << '\n' << std::endl;
   }
}

void PasswordManager::addLogin()
{
   std::cout << "What is the name of the website you want to add? ";
   const std::string website = receiveUserInput();

   std::cout << "\nWhat is the username you would like to add? ";
   const std::string username = receiveUserInput();

   std::cout << "\nWhat is the password you would like to add? ";
   const std::string password = receiveUserInput();

   manager.insertNode(website, username, password);
}

void PasswordManager::removeLogin()
{
   std::cout << "What is the name of the website you want to remove? ";
   const website = receiveUserInput();

   if(manager.removeNode(website)) {
      std::cout << "The website's login was successfully removed!\n\n";
   } else {
      std::cout << website << " could not be found!\n\n";
   }
}

void PasswordManager::printLogins() const noexcept
{
   manager.printTable();
}

void PasswordManager::changeLogin()
{
   char usernameFlag = 'n';
   std::cout << "What is the website of the login you wish to change? ";
   const website = receiveUserInput();

   std::cout << "Would  you like to change your username? (Y/N): ";
   while(!(std::cin >> usernameFlag) || toupper(usernameFlag) != 'N' || toupper(usernameFlag) != 'Y') {
      clearInputStream();
      std::cerr << "Failed to recieve input! Try again! ";
   }
   clearInputStream();

   if(toupper(usernameFlag) == 'Y') {
      std::cout << "What is the new username? ";
      const username = receiveUserInput();
      manager.changeUsername(website, username);
   }

   std::cout << "What is the new password? ";
   const password = receiveUserInput();
   manager.changePassword();
}
