//Author: Caden LeCluyse
//Date: 3/25/24
//Filename: passwordmanager.h

#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <iostream>
#include <limits>
#include <string>
#include "hashtable.h"

class PasswordManager
{
   public:
      login getLogin() const;
      void printLogin(const login& entry) const; 
      void addLogin();
      void removeLogin();
      void printAllLogins() const noexcept;
      void changeLogin();

   private:
      HashTable manager;
      void clearInputStream() const;
      std::string receiveUserInput() const;
};

#endif
