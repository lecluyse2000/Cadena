#include <string>
#include <limits>
#include "application.h"
#include "passwordmanager.h"

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

int Application::recieveUserInputMenu() const
{
   std::string userInput; 

   while(!(std::cin >> userInput) || userInput.size() != 1 || !isdigit(userInput[0]) 
         || std::stoi(userInput) > 6 || std::stoi(userInput) < 1) {
      clearInputStream();
      std::cout << "\nIncorrect input! Try again.\nYour choice: "; 
   } 

   std::cout << std::endl;

   return std::stoi(userInput);
}

void run()
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
   
   bool keepGoing = true;
   std::cout << "Welcome to Caden's Password Manager!\n";

   while(keepGoing) {
      printMenu();
      switch(recieveUserInputMenu()) {
         case 1:
            database.printLogins();
            break;
         case 2:
            database.printLogin(database.getLogin());
            break;
         case 3:
            database.addlogin();
            break;
         case 4:
            database.removeLogin(); 
            break;
         case 5:
            database.changeLogin();
            break;
         case 6:
            keepGoing = false;
            std::cout << "Exiting...\n\n";
            break;
      }
   }
}
