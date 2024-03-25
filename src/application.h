#ifndef APPLICATION_H
#define APPLICATION_H

#include "passwordmanager.h"

class Application
{

   public:
      void run();


   private:
      PasswordManager database;
      void printMenu() const noexcept;
      void clearInputStream() const;  
      void receiveUserInputMenu() const;

};


#endif
