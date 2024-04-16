// Author: Caden LeCluyse
// Date: 3/25/24
// Filename: application.h

#ifndef APPLICATION_H
#define APPLICATION_H

#include <cstdint>
#include <string>

#include "passwordmanager.h"

class Application
{
   public:
      void run();

   private:
      PasswordManager database;
      bool loopFlag{true};
      void printMenu() const noexcept;
      void clearInputStream() const;
      bool verifyUserInputMenu(std::string& input) const;
      std::uint8_t receiveUserInputMenu() const;
      void userInterface();
};

#endif
