//Author: Caden LeCluyse
//Date: 2/20/24
//File: main.cpp
//Note: I realize this could've been implemented (probably in a better way too) using std::unordered_map, I just wanted to better understand the data structure

#include <iostream>
#include <limits>
#include "hashtable.h"
//#include <sodium.h>
#include <string>


void printMenu()
{
   std::cout << "\n1) Print all passwords\n2) Print specific password\n3) Add a password\n"
             << "4) Remove a password\n5) Change a password\n6) Exit program\nYour choice: ";
}

void clearInputStream()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int recieveUserInputMenu() 
{
   std::string userInput = "";
   printMenu();

   while(!(std::cin >> userInput) || userInput.size() != 1 || !isdigit(userInput[0]) 
         || std::stoi(userInput) > 6 || std::stoi(userInput) < 1) {
      clearInputStream();
      std::cout << "\nIncorrect input! Try again.\nYour choice: "; 
   } 

   std::cout << std::endl;

   return std::stoi(userInput);
}


int main()
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
   
   HashTable passwordManager;
   bool keepGoing = true;
   std::string website = "";
   std::string username = "";
   std::string password = "";
   std::cout << "Welcome to Caden's Password Manager!\n";

   while(keepGoing) {
      website = "";
      username = "";
      password = "";

      switch(recieveUserInputMenu()) {
         case 1:
            passwordManager.printTable();
            break;
         case 2:
            printLogin(getLogin(passwordManager));
            break;
         case 3:
            addLogin(passwordManager);
            break;
         case 4:
            
            break;
         case 5:
            std::cout << "What is the name of the website you want to change? ";
            
            if(!(std::cin >> website)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }
            
            clearInputStream();
            std::cout << "\nWhat is the password you would like to add: ";
            
            if(!(std::cin >> password)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            clearInputStream();
            passwordManager.changePassword(website, std::move(password));
            break;
         case 6:
            keepGoing = false;
            std::cout << "Exiting...\n\n";
            break;
      }
   }

   return 0;
}
