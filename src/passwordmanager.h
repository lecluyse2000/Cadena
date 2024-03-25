#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include "hashtable.h"

class PasswordManager
{
   public:
      login getLogin() const;
      void printLogin(const login& entry) const; 
      void addLogin();
      void removePassword();
      void changeLogin();

   private:
      HashTable manager;
      void clearInputStream();
      void receiveUserInput();
};

#endif
