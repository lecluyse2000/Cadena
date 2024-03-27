//Author: Caden LeCluyse
//Date: 3/25/24
//Filename: application.cpp


#include <iostream>
#include <string>
#include <limits>
#include "application.h"
#include "passwordmanager.h"
#include "hashtable.h"

void Application::printMenu() const noexcept
{
   std::cout << "\n1) Print all passwords\n2) Print specific password\n3) Add a password\n"
             << "4) Remove a password\n5) Change a password\n6) Exit program\nYour choice: ";
}

void Application::clearInputStream() const
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Application::verifyUserInputMenu(std::string& input) const
{
   while(std::cin.fail() || input.size() != 1 || !isdigit(input[0]) 
         || std::stoi(input) > 6 || std::stoi(input) < 1) {
      clearInputStream();
      std::cout << "\nIncorrect input! Try again.\nYour choice: "; 
      std::cin >> input;
   } 
   clearInputStream();
}

uint8_t Application::receiveUserInputMenu() const
{
   std::string userInput; 
   std::cin >> userInput;
   verifyUserInputMenu(userInput);

   return static_cast<uint8_t>(std::stoi(userInput));
}

void Application::userInterface() 
{
   printMenu();
   switch(receiveUserInputMenu()) {
      case 1:
         database.printAllLogins();
         break;
      case 2:
         database.printLogin(database.getLogin());
         break;
      case 3:
         database.addLogin();
         break;
      case 4:
         database.removeLogin(); 
         break;
      case 5:
         database.changeLogin();
         break;
      case 6:
         loopFlag = false;
         std::cout << "Exiting...\n\n";
         break;
   }
}

void Application::run()
{
   /*
   //Initialize libsodium
   if (sodium_init() < 0) {
      std::cerr << "Failed to initialize Libsodium" << std::endl;
      return 1;
   } else {
      std::cout << "Libsodium initialized successfully!\n\n";
   }
   */
   
   std::cout << "Welcome to Caden's Password Manager!\n";

   while(loopFlag) {
      userInterface();
   }
}
