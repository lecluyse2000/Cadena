// Author: Caden LeCluyse
// Date: 2/19/24
// File: hashtable.h
// Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

struct login {
   std::string website;
   std::string username;
   std::string password;

   login(std::string&& webpage, std::string&& loginID, std::string&& passphrase)
         : website(webpage), username(loginID), password(passphrase) {}
};

class HashTable
{
   public:
      HashTable() : m_table(256) {}
      ~HashTable();
      [[nodiscard]] bool isEmpty() const noexcept;
      [[nodiscard]] bool verifyEntry(std::string_view key) const noexcept;
      void insertNode(std::string& key, std::string& username, std::string& password);
      void removeNode(std::string_view key);
      [[nodiscard]] login searchTable(std::string_view key) const noexcept;
      void printTable() const noexcept;
      void changeUsername(std::string_view key, std::string&& newUsername);
      void changePassword(std::string_view key, std::string&& newPassword);

   private:
      std::uint16_t m_numberLogins{ 0 };
      std::vector<std::vector<login>> m_table;
      [[nodiscard]] constexpr std::size_t hashFunction(std::string_view key) const noexcept;
      void resize();
};

#endif
