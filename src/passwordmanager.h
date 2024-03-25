#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "hashtable.h"

class PasswordManager
{
   public:
      login getLogin() const;
      void printLogin(const login& entry) const; 
      void addLogin();
      void removeLogin();
      void printLogins() const;
      void changeLogin();

   private:
      HashTable manager;
      void clearInputStream() const;
      void receiveUserInput() const;
};

#endif
