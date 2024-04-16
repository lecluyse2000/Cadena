// Author: Caden LeCluyse
// Date: 3/25/24
// Filename: passwordmanager.h

#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H

#include <optional>
#include <string>
#include <string_view>

#include "hashtable.h"

class PasswordManager
{
  public:
   std::optional<login> getLogin() const;
   void printLogin(const std::optional<login>& entry) const;
   void addLogin();
   void removeLogin();
   void printAllLogins() const noexcept;
   void changeLogin();

  private:
   HashTable manager;
   void clearInputStream() const;
   std::string receiveUserInput() const;
   void changeUsername(std::string_view website);
   void changePassword(std::string_view website);
};

#endif
