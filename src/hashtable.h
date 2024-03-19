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
   std::string userName;
   std::string password;

   login(const std::string& webpage, 
         const std::string& passphrase)
      : website(webpage),  password(passphrase) {}
};

class HashTable
{
   public: 
      HashTable();
      ~HashTable();
      void resize(const std::size_t size);
      bool isEmpty() const noexcept;
      void insertNode(const std::string& key, const std::string& value);
      void removeNode(std::string_view key);
      std::string searchTable(std::string_view key) const noexcept;
      void printTable() const noexcept;
      void changePassword(std::string_view key, const std::string& newPassword);
   
   private:
      std::size_t m_vectorSize{ 256 };
      std::vector<std::vector<login>> m_table;
      std::size_t hashFunction(std::string_view key) const noexcept;
};

#endif
