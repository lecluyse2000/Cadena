//Author: Caden LeCluyse
//Date: 2/20/24
//File: main.cpp
//Note: I realize this could've been implemented (probably in a better way too) using std::unordered_map, I just wanted to better understand the data structure

#include <iostream>
#include <limits>
#include "hashtable.h"
#include <sodium.h>
#include <stdexcept>

int printMenu() 
{
   std::string userInput = "";
   std::cout << "\n1) Print all passwords\n2) Print specific password\n3) Add a password\n"
             << "4) Remove a password\n5) Change a password\n6) Exit program\nYour choice: ";

   while(!(std::cin >> userInput) || userInput.size() != 1 || !isdigit(userInput[0]) || std::stoi(userInput) > 6 || std::stoi(userInput) < 1) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "\nIncorrect input! Try again.\nYour choice: "; 
   } 
   std::cout << std::endl;
   return std::stoi(userInput);
}

//Main driver code here
int main()
{
   //Initialize libsodium
   if (sodium_init() < 0) {
        std::cerr << "Failed to initialize Libsodium" << std::endl;
        return 1;
   } 
   
   HashTable passwordManager(128);
   bool keepGoing = true;
   std::string userInput = "";
   std::cout << "Welcome to Caden's Password Manager!\n";

   while(keepGoing) {
      userInput = "";
      switch(printMenu()) {
         case 1:
            passwordManager.printTable();
            break;
         case 2:
            std::cout << "What is the website of the password you want to get? ";
            std::cin >> userInput;
            std::cout << "Password of " << userInput << ": " << passwordManager.searchTable(userInput) << std::endl;
            break;
         case 3:
            std::cout << "What is the name of the website you want to add? ";
            break;
         case 4:

            break;
         case 5:

            break;
         case 6:
            keepGoing = false;
            std::cout << "Exiting...\n\n";
            break;
      }
   }
   return 0;
}
