//Author: Caden LeCluyse
//Date: 3/25/24
//Filename: passwordmanager.cpp 

#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include "passwordmanager.h"
#include "hashtable.h"

void PasswordManager::clearInputStream() const
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string PasswordManager::receiveUserInput() const
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
   std::cout << "\nWhat is the website of the login you want to get? ";
   std::string website = receiveUserInput();
   if(manager.verifyEntry(website)) {
      return manager.searchTable(website);
   }
   return {"NULL", "NULL", "NULL"};
}

void PasswordManager::printLogin(const login& entry) const
{
   const auto [website, username, password] = entry;
   if(website == "NULL") {
      std::cerr << "The login for the given website could not be found!\n\n";
   } else {
      std::cout << "\nWebsite: " << website << "\nUsername:  " << username
                << "\nPassword: " << password << '\n' << std::endl;
   }
}

void PasswordManager::addLogin()
{
   std::cout << "\nWhat is the name of the website you want to add? ";
   std::string website = receiveUserInput();

   std::cout << "What is the username you would like to add? ";
   std::string username = receiveUserInput();

   std::cout << "What is the password you would like to add? ";
   std::string password = receiveUserInput();

   manager.insertNode(website, username, password);
}

void PasswordManager::removeLogin()
{
   std::cout << "\nWhat is the name of the website you want to remove? ";
   const std::string website = receiveUserInput();

   if(manager.verifyEntry(website)) {
      manager.removeNode(website);
   } else {
      std::cerr << "The given login is not in the table!\n";
   }
}

void PasswordManager::printAllLogins() const noexcept
{
   if(manager.isEmpty()) {
      std::cout << "You don't have any passwords added!\n\n";
   } else {
      manager.printTable();
   }
}

void PasswordManager::changeUsername(std::string_view website)
{
   std::cout << "What is the new username? ";
   std::string username = receiveUserInput();
   manager.changeUsername(website, std::move(username));

}

void PasswordManager::changePassword(std::string_view website)
{
   std::cout << "What is the new password? ";
   std::string password = receiveUserInput();
   manager.changePassword(website, std::move(password));
}

void PasswordManager::changeLogin()
{
   char usernameFlag = 'n';
   std::cout << "What is the website of the login you wish to change? ";
   const std::string website = receiveUserInput();
   
   if(!manager.verifyEntry(website)) {
      std::cerr << "The given website could not be found!\n";
      return;
   }

   std::cout << "Would  you like to change your username? (Y/N): ";
   while(!(std::cin >> usernameFlag) || (toupper(usernameFlag) != 'N' && toupper(usernameFlag) != 'Y')) {
      clearInputStream();
      std::cerr << "Failed to recieve input! Try again! ";
   }
   clearInputStream();

   if(toupper(usernameFlag) == 'Y') {
      changeUsername(website);
   }
   changePassword(website);
}
