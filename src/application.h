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
      void printMenu() const noexcept;
      void clearInputStream() const;  
      void verifyUserInputMenu(std::string& input) const;
      int receiveUserInputMenu() const;

};


#endif
