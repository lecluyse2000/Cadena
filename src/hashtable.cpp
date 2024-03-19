//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.cpp
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure


#include <ranges>
#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>
#include "hashtable.h"
#include <algorithm>

#define PRIME_1 57649
#define PRIME_2 86969

HashTable::HashTable() : m_table(256) {}

HashTable::~HashTable()
{
   std::ranges::for_each(m_table, [](std::vector<login>& entry) {
      entry.clear();
   }); 
}

void HashTable::resize(const std::size_t size)
{
   m_table.resize(size);
}

constexpr bool HashTable::isEmpty() const noexcept 
{
   return m_table.empty();
}

constexpr std::size_t HashTable::hashFunction(std::string_view key) const noexcept
{
   size_t hashValue = 76963;
   std::ranges::for_each(key, [&hashValue](const char character) {
      hashValue = (hashValue * PRIME_1) ^ (character * PRIME_2);
   });

   return hashValue & (m_vectorSize - 1);
}

void HashTable::insertNode(const std::string& key, const std::string& username, const std::string& value)
{
   const std::size_t hashValue = hashFunction(key);
   m_table[hashValue].emplace_back(key, username, value);
   std::cout << "The password was added!\n";
}

void HashTable::removeNode(std::string_view key)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
         return entry.website == key;
   });

   if(itr != m_table[hashValue].end()) {
      m_table[hashValue].erase(itr);
      std::cout << "The given login was removed!\n";
   } else {
      std::cout << "Could not find the login!\n";
   }
}

login HashTable::searchTable(std::string_view key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;   
   });

   if(itr != m_table[hashValue].end()) {
      return *itr
   }
   std::cout << "The login could not be found!\n";
}

void HashTable::printTable() const noexcept
{
   //This is the first lambda function I have ever implemented
   std::ranges::for_each(m_table, [](const std::vector<login>& entry) {
      std::ranges::for_each(entry, [](const login& t_login) {
         std::cout << "Website: " << t_login.website << "\nUsername: " 
                   << t_login.username  << "\nPassword: " << t_login.password << '\n' 
                   << std::endl;
      });
   });
}

void HashTable::changePassword(std::string_view key, const std::string& newPassword)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   if(itr != m_table[hashValue].end()) {
      itr->password = newPassword;
      std::cout << "The password was changed!\n";
   } else {
      std::cout << "The password was unable to be found!\n";
   }
}
