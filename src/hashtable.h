//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.h
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <utility>
#include <string>
#include <string_view>

struct login
{
   std::string website;
   std::string username;
   std::string password;

   login(std::string&& webpage, std::string&& loginID,
         std::string&& passphrase)
         : website(webpage), username(loginID), password(passphrase) {}
};

class HashTable
{
   public: 
      HashTable();
      ~HashTable();
      bool isEmpty() const noexcept;
      void insertNode(std::string& key, std::string& username, std::string& value);
      bool removeNode(std::string_view key);
      login searchTable(std::string_view key) const noexcept;
      void printTable() const noexcept;
      bool changeUsername(std::string_view key, std::string&& newUsername);
      bool changePassword(std::string_view key, std::string&& newPassword);
   
   private:
      std::size_t m_vectorSize{ 256 };
      unsigned int m_numberLogins{ 0 };
      std::vector<std::vector<login>> m_table;
      [[nodiscard]] constexpr std::size_t hashFunction(std::string_view key) const noexcept;
      void resize();
};

#endif
