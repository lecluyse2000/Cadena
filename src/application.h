//Author: Caden LeCluyse
//Date: 3/25/24
//Filename: application.h

#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <limits>
#include "passwordmanager.h"
#include "hashtable.h"

class Application
{

   public:
      void run();


   private:
      PasswordManager database;
      bool keepGoing{ true };
      void printMenu() const noexcept;
      void clearInputStream() const;  
      void verifyUserInputMenu(std::string& input) const;
      uint8_t receiveUserInputMenu() const;
      void userInterface();
};


#endif
